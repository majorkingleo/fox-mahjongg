#include "board.hh"
#include "panel.hh"
#include "tileset.hh"
#include "tile.hh"
#include "hint.hh"
#include "debug.h"
#include "main.h"
#include <format.h>
#include "FXPixelBuffer.h"

using namespace Tools;

Board::Board(Panel *panel, Game *game, Tileset *tileset)
: SwWidget(panel),
  _panel(panel),
  _game(game),
  _tileset(0),
  _redraw_live(true),
  _layout_x(0),
  _layout_y(0),
  _topmost_tile(-1),
  _botmost_tile(-1),
  _leftmost_tile(-1),
  _rightmost_tile(-1),
  _tile_width(0),
  _tile_height(0),
  _tile_xborder(0),
  _tile_yborder(0),
  _tile_shadow(0),
  _tile_flags(),
  _selected(0),
  _hint(0),
  _display_order()
{
	set_tileset(tileset);
	_game->add_hook(this);

	_hint = new Hint(this);

	_y = 38;
}

Board::~Board()
{
	delete _hint;
}

void Board::set_tileset(Tileset *ts)
{
	_tileset = ts;

	_tile_width = ts->width();
	_tile_height = ts->height();
	_tile_xborder = ts->xborder();
	_tile_yborder = ts->yborder();
	_tile_shadow = ts->shadow();

	DEBUG(format("_tile_width: %dx%d border: %d shadow: %d", _tile_width, _tile_height, _tile_xborder, _tile_shadow));

}

void Board::set_background(FXImage *background)
{
	auto obj = window()->getObjectByName( "background" );
	if( obj ) {
		window()->remove( obj );
	}
	window()->setTiledBackgroundImage(background, -1, "background");
}

#define CHECK(dr, dc, dl)	do { u = g->grid(r+dr, c+dc, l+dl); \
			if (u->marked()) display_order_dfs(g, u); } while(0)

void Board::display_order_dfs(Game *g, Tile *t)
{
	t->unmark();

	int r = t->row();
	int c = t->col();
	int l = t->lev();

	Tile *u;

	// This loop is to be careful for hypothetical strange boards, where there
	// might be a bridge over a valley, for example: we have to check ALL
	// levels above.
	{
		int dc_lft = -1, dc_rt = 1, dr_top = 0, dr_bot = 2;
		for (int dl = 1; dl <= TILE_LEVS - 1 - l; dl++) {
			for (int dr = dr_top; dr <= dr_bot; dr++)
				for (int dc = dc_lft; dc <= dc_rt; dc++)
					if (r + dr >= 0 && r + dr < TILE_ROWS && c + dc >= 0 && c + dc < TILE_COLS)
						CHECK(dr, dc, dl);
			(_tile_shadow & 1 ? dc_rt++ : dc_lft--);
			(_tile_shadow & 2 ? dr_bot++ : dr_top--);
		}
	}

	if (_tile_shadow & 1) {
		CHECK(0, -1, 0);
		CHECK(1, -1, 0);
		CHECK(2, -1, 0);
		CHECK(2, 0, 0);
		CHECK(2, 1, 0);
	}
	else {
		CHECK(0, 2, 0);
		CHECK(1, 2, 0);
		CHECK(2, 2, 0);
		CHECK(2, 1, 0);
		CHECK(2, 0, 0);
	}

	_display_order.push_back(t);
}

#undef CHECK

void Board::layout_hook(Game *g)
{
	assert(g == _game);
	const Vector<Tile*> &tiles = g->tiles();
	int ntiles = tiles.size();

	_display_order.clear();
	if (ntiles == 0) {
		return;
	}

	// Create the display order.
	for (int i = 0; i < ntiles; i++) {
		tiles[i]->mark();
	}

	for (int i = 0; i < ntiles; i++) {
		if (tiles[i]->marked()) {
			display_order_dfs(g, tiles[i]);
		}
	}

	assert(_display_order.size() == ntiles);
	Vector<Tile*> d;
	for (int j = ntiles - 1; j >= 0; j--) {
		d.push_back(_display_order[j]);
	}
	_display_order = d;

	// Find the leftmost, topmost, rightmost, and bottommost tile positions.
	short top = 0x7FFF, left = 0x7FFF, right = -0x8000, bottom = -0x8000;
	for (int i = 0; i < ntiles; i++) {
		short x, y;
		position(tiles[i], &x, &y);
		x -= _layout_x;
		y -= _layout_y;

		if (x < left) {
			left = x;
			_leftmost_tile = i;
		}

		if (y < top) {
			top = y;
			_topmost_tile = i;
		}

		if (x + _tile_width > right) {
			right = x + _tile_width;
			_rightmost_tile = i;
		}

		if (y + _tile_height > bottom) {
			bottom = y + _tile_height;
			_botmost_tile = i;
		}
	}

	// Center the layout on the board.
	center_layout();
}

int Board::topmost_tile_y() const
{
	short x, y;
	position(_game->tile(_topmost_tile), &x, &y);
	return y;
}

void Board::tile_layout_size(int *width, int *height) const
{
	Tile *tleft = _game->tile(_leftmost_tile);
	Tile *tright = _game->tile(_rightmost_tile);
	Tile *ttop = _game->tile(_topmost_tile);
	Tile *tbot = _game->tile(_botmost_tile);

	short xx, yy, zz;
	position(tleft, &xx, &yy);
	position(tright, &zz, &yy);
	*width = zz - xx + _tile_width + _tile_xborder;
	position(ttop, &xx, &yy);
	position(tbot, &xx, &zz);
	*height = zz - yy + _tile_height + _tile_yborder;
}

void Board::center_layout()
{
	if (_game->ntiles() == 0) {
		return;
	}

	int layout_width, layout_height;
	tile_layout_size(&layout_width, &layout_height);

	short xx, yy;
	_layout_x = 0;
	position(_game->tile(_leftmost_tile), &xx, &yy);
	_layout_x = x() + (width() - layout_width) / 2 - xx;

	_layout_y = 0;
	position(_game->tile(_topmost_tile), &xx, &yy);
	_layout_y = y() + (height() - layout_height) / 2 - yy;
}

void Board::start_hook(Game *g)
{
	_tileset->erase(0, this);
	_tile_flags.assign(g->ntiles(), 0);
	if (_panel->visible()) {
		for (int i = 0; i < _display_order.size(); i++) {
			Tile *t = _display_order[i];
			if (t->real()) {
				draw(t);
			}
		}
	}
}

inline void Board::position(Tile *t, short *x, short *y) const
{
	int r = t->row(), c = t->col(), l = t->lev();
	*x = _layout_x + _tile_width * (c >> 1) + (c & 1 ? _tile_width >> 1 : 0)
	        + (_tile_shadow & 1 ? _tile_xborder * l : -_tile_xborder * l);
	*y = _layout_y + _tile_height * (r >> 1) + (r & 1 ? _tile_height >> 1 : 0)
	        + (_tile_shadow & 2 ? _tile_yborder * l : -_tile_yborder * l);
}

void Board::unposition(int x, int y, short *r, short *c) const
{
	*c = (x - _layout_x) * 2 / _tile_width;
	*r = (y - _layout_y) * 2 / _tile_height;
}

Tile*
Board::find_tile(short x, short y) const
{
	int rl_delta = (_tile_shadow & 2 ? 1 : 0);
	int cl_delta = (_tile_shadow & 1 ? 1 : 0);
	int ybord = (_tile_shadow & 2 ? _tile_yborder : -_tile_yborder);
	int xbord = (_tile_shadow & 1 ? _tile_xborder : -_tile_xborder);
	for (int l = TILE_LEVS - 1; l >= 0; l--) {
		int r = (y - _layout_y - ybord * (l + rl_delta)) * 2 / _tile_height;
		int c = (x - _layout_x - xbord * (l + cl_delta)) * 2 / _tile_width;
		if (r < 0 || r >= TILE_ROWS) {
			continue;
		}

		if (c < 0 || c >= TILE_COLS) {
			continue;
		}

		Tile *t = _game->grid(r, c, l);
		if (t->real()) {
			short xx, yy;
			position(t, &xx, &yy);
			if (x >= xx && y >= yy) {
				return t;
			}
		}
	}
	return 0;
}

void Board::move(int x, int y)
{
	invalidate(_layout_x, _layout_y, TILE_COLS * _tile_width / 2,
	TILE_ROWS * _tile_height / 2);
	_layout_x = x;
	_layout_y = y;
}

void Board::draw_subimage(FXImage *image, FXBitmap *mask, int src_x, int src_y, int w, int h, int x, int y)
{

}

void Board::draw(Tile *t)
{
	short x, y;
	position(t, &x, &y);

	if (!t->real()) {
		;
	} else if (t->obscured()) {
		_tileset->draw_obscured(t, this, x, y);
	} else if (lit(t)) {
		_tileset->draw_lit(t, this, x, y);
	} else {
		_tileset->draw_normal(t, this, x, y);
	}
}

void Board::draw_marked()
{
	for (int i = 0; i < _display_order.size(); i++) {
		Tile *t = _display_order[i];
		if (t->marked() && t->real()) {
			draw(t);
			t->unmark();
		}
	}
}

void Board::mark_around(Tile *t, bool up, bool down)
{
	if (up) {
		int colleft = t->col() - 1;
		int colright = t->col() + 2;
		int rowtop = t->row() - 1;
		int rowbot = t->row() + 2;

		for (int lev = t->lev(); lev < TILE_LEVS; lev++) {
			for (int col = colleft; col <= colright; col++) {
				for (int row = rowtop; row <= rowbot; row++) {
					if (col >= 0 && col < TILE_COLS && row >= 0 && row < TILE_ROWS) {
						_game->grid(row, col, lev)->mark();
					}
				}
			}
			(_tile_shadow & 1 ? colright++ : colleft--);
			(_tile_shadow & 2 ? rowbot++ : rowtop--);
		}
	}

	if (down) {
		int colleft = t->col() - 1;
		int colright = t->col() + 2;
		int rowtop = t->row() - 1;
		int rowbot = t->row() + 2;

		for (int lev = t->lev(); lev >= 0; lev--) {
			for (int col = colleft; col <= colright; col++) {
				for (int row = rowtop; row <= rowbot; row++) {
					if (col >= 0 && col < TILE_COLS && row >= 0 && row < TILE_ROWS) {
						_game->grid(row, col, lev)->mark();
					}
				}
			}
			(_tile_shadow & 1 ? colright++ : colleft--);
			(_tile_shadow & 2 ? rowbot++ : rowtop--);
		}
	}
}

void Board::draw_neighborhood(Tile *t, int erase)
{
	short x, y;
	position(t, &x, &y);

	switch (erase)
	{
		case 0:
		{ // drawing new tile
			DEBUG("drawing new tile");
			mark_around(t, true, false);
			draw_marked();
			break;
		}

		case 1:
		{ // erasing tile
			DEBUG("erasing tile");
			_tileset->erase(t, this);
			mark_around(t, true, true);
			draw_marked();
			break;
		}

		case 2:
		{ // highlighting/unhighlighting tile
			DEBUG("highlighting/unhighlighting tile");
			mark_around(t, true, false);
			draw_marked();
			// now have correct mask; use it
			// draw(t);
			break;
		}
	}
}

void Board::draw_area(short rowtop, short colleft, short rowbot, short colright)
{
	colleft = (colleft < 0 ? 0 : colleft);
	colright = (colright >= TILE_COLS ? TILE_COLS - 1 : colright);
	rowtop = (rowtop < 0 ? 0 : rowtop);
	rowbot = (rowbot >= TILE_ROWS ? TILE_ROWS - 1 : rowbot);
	for (int lev = 0; lev < TILE_LEVS; lev++) {
		for (int col = colleft; col <= colright; col++) {
			for (int row = rowtop; row <= rowbot; row++) {
				_game->grid(row, col, lev)->mark();
			}
		}
	}
	draw_marked();
}

void Board::set_lit(Tile *t, bool on)
{
	bool was_on = lit(t);
	set_tile_flag(t, fLit, on);
	if (on != was_on && t->real()) {
		draw_neighborhood(t, 2);
	}
}

void Board::select(Tile *t)
{
	if (_selected) {
		deselect();
	}

	light(t);
	set_tile_flag(t, fKeepLit, true);
	_selected = t;
}

void Board::deselect()
{
	if (_selected) {
		unlight(_selected);
		set_tile_flag(_selected, fKeepLit, false);
		_selected = 0;
	}
}

void Board::add_tile_hook(Game *g, Tile *t)
{
	assert(g == _game);
	if (_redraw_live) {
		draw_neighborhood(t, 0);
	}
}

void Board::remove_tile_hook(Game *g, Tile *t)
{
	assert(g == _game);
	if (_selected == t) {
		_selected = 0;
	}

	_tile_flags[t->number()] = 0;
	if (_redraw_live) {
		draw_neighborhood(t, 1);
	}
}

void Board::draw_background()
{

}

bool Board::tile_flag(Tile *t, TileFlag flag) const
{
	return _tile_flags[t->number()] & flag;
}

bool Board::lit(Tile *t) const
{
	return tile_flag(t, fLit);
}

void Board::set_tile_flag(Tile *t, TileFlag flag, bool on)
{
	if (on) {
		_tile_flags[t->number()] |= flag;
	} else {
		_tile_flags[t->number()] &= ~flag;
	}
}

