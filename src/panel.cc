#include "matches.hh"
#include "panel.hh"
#include "tile.hh"
#include "game.hh"
#include "button.hh"
#include "board.hh"
#include "hint.hh"
#include "solution.hh"
#include "traverse.hh"
#include "counter.hh"
#include "main.h"
#include "debug.h"
#include <format.h>

using namespace Tools;

Panel::Panel(FXApp *app, FXPixelBuffer *window, MahjonggWindow *root )
  : SwClippedWindow(app, window, root ),
    _visible(false),

    _window_width(-1),
    _window_height(-1),

    _board(0),
    _background(0),
    _tile_count(0),
    _match_count(0),
    _solution(0),
    _traversal(0),

    _scan_mark_x( 0 ),
    _scan_mark_y( 0 ),

    _redraw_left( 0 ),
    _redraw_top( 0 ),
    _redraw_right( 0 ),
    _redraw_bottom( 0 ),

    _need_redraw(false),

    new_but(0),
    undo_but(0),
    quit_but(0),
    hint_but(0),
    clean_but(0)
{
}

void Panel::scan_mark(int original_x, int original_y)
{
	_scan_mark_x = original_x;
	_scan_mark_y = original_y;
}

void Panel::scan_dragto(int x, int y)
{
	int dx = x - _scan_mark_x;
	int dy = y - _scan_mark_y;
	_board->move(_board->x() + dx, _board->y() + dy);
	_scan_mark_x = x;
	_scan_mark_y = y;
}

void Panel::set_board(Board *b)
{
	_board = b;
	_board->set_visible();
	if (_background) {
		_board->set_background(_background);
	}

	if (_traversal) {
		delete _traversal;
	}
	_traversal = new Traversal(_board);
}

void Panel::set_background(FXImage *background)
{
	_background = background;
	_board->set_background(_background);
}

void Panel::set_match_count(MatchCount *mc)
{
	_match_count = mc;
	_match_count->set_position(100, 12);
}

void Panel::set_tile_count(FancyCounter *tc)
{
	_tile_count = tc;
	_tile_count->set_position(10, 12);
}

void Panel::set_solution(SolutionDisplay *sol)
{
	if (_solution) {
		delete _solution;
	}
	_solution = sol;
}

void Panel::draw_controls()
{
	new_but->draw();
	undo_but->draw();
	quit_but->draw();
	hint_but->draw();
	clean_but->draw();
}

void Panel::resize(int x, int y)
{
	if (_window_width == x && _window_height == y) {
		return;
	}
	_window_width = x;
	_window_height = y;
	int quit_x = _window_width - quit_but->width() - 10;
	int new_x = quit_x - new_but->width() - 10;
	int undo_x = new_x - undo_but->width() - 10;
	int clean_x = undo_x - clean_but->width() - 10;
	int hint_x = clean_x - hint_but->width() - 10;
	quit_but->set_position(quit_x, 10);
	new_but->set_position(new_x, 10);
	undo_but->set_position(undo_x, 10);
	hint_but->set_position(hint_x, 10);
	clean_but->set_position(clean_x, 10);

	_board->set_size(_window_width, _window_height - _board->y_pos());
	_board->center_layout();

	// find topmost tile
	int topmost_tile_y = _board->topmost_tile_y();

	_match_count->set_position(_tile_count->x() + _tile_count->width() + 5, 12);
	_match_count->set_size(hint_x - 10 - _match_count->x(), topmost_tile_y - 12);
}

void Panel::invalidate(int x, int y, int width, int height)
{
	clear_area(x, y, width, height);
	if (!_need_redraw) {
		_redraw_left = x;
		_redraw_top = y;
		_redraw_right = x + width;
		_redraw_bottom = y + height;
	}
	else {
		if (x < _redraw_left) {
			_redraw_left = x;
		}
		if (y < _redraw_top) {
			_redraw_top = y;
		}
		if (x + width > _redraw_right) {
			_redraw_right = x + width;
		}
		if (y + height > _redraw_bottom) {
			_redraw_bottom = y + height;
		}
	}
	_need_redraw = true;
}

void Panel::redraw_all()
{
	_redraw_left = _redraw_top = 0;
	_redraw_right = _window_width;
	_redraw_bottom = _window_height;
	_need_redraw = true;
	redraw();
}

void Panel::redraw()
{
	if (!_need_redraw || !_visible) {
		DEBUG("no redraw required");
		return;
	}

	DEBUG("redraw");

	_redraw_left -= 2;
	_redraw_top -= 2;
	_redraw_right += 2;
	_redraw_bottom += 2;
	if (_redraw_left < 0)
		_redraw_left = 0;
	if (_redraw_top < 0)
		_redraw_top = 0;
	if (_redraw_right > _window_width)
		_redraw_right = _window_width;
	if (_redraw_bottom > _window_height)
		_redraw_bottom = _window_height;

	intersect_clip(_redraw_left, _redraw_top, _redraw_right - _redraw_left, _redraw_bottom - _redraw_top);

	_board->draw_background();

	_tile_count->draw();
	_match_count->draw();

	short row1, col1, row2, col2;
	_board->unposition(_redraw_left, _redraw_top, &row1, &col1);
	_board->unposition(_redraw_right, _redraw_bottom, &row2, &col2);
	row1 -= 2, col1 -= 2, row2++, col2++;
	if (col1 < 0) {
		col1 = 0;
	}
	if (row1 < 0) {
		row1 = 0;
	}
	if (col2 >= TILE_COLS - 1) {
		col2 = TILE_COLS - 2;
	}
	if (row2 >= TILE_ROWS - 1) {
		row2 = TILE_ROWS - 2;
	}
	_board->draw_area(row1, col1, row2, col2);

	draw_controls();

	unclip();
	_need_redraw = false;
}

int butler(Game *g)
{
	int nmatch = g->nmatches();
	int i;
	for (i = 0; i < nmatch; i++)
		if (g->left_count(i) > 0 && g->left_count(i) == g->free_count(i)) {
			Vector<Tile*> gg;
			const Vector<Tile*> &t = g->tiles();

			for (int j = 0; j < t.size(); j++) {
				if (t[j]->real() && t[j]->open() && t[j]->match() == i) {
					gg.push_back(t[j]);
				}
			}

			g->move(gg[0], gg[1], false);
			if (gg.size() > 2) {
				g->move(gg[2], gg[3], false);
			}
			return butler(g) + 1;
		}

	return 0;
}

void Panel::tile_command(Game *g, Tile *t)
{
	/* Turn off transients */
	if (_solution) {
		_solution->turn_off();
	}
	_board->hint()->turn_off();
	_traversal->turn_off();

	Tile *pend = _board->selected();

	if (!t->open()) {
		_board->bell();
		return;
	}

	if (!pend) {
		_board->select(t);
	}
	else if (pend == t) {
		_board->deselect();
	}
	else if (pend->match() == t->match()) {
		_board->deselect();
		g->move(pend, t);

	}
	else {
		_board->deselect();
		_board->select(t);
	}

	_traversal->set_cursor(t);
}

void Panel::command(Game *g, Command com, Button *button, bool keyboard, FXuint when)
{
	if (com != comHint) {
		_board->hint()->turn_off();
	}

	if (com != comSolve && com != comNone && _solution) {
		_solution->turn_off();
	}

	if (com != comNone && com != comHint) {
		_board->deselect();
	}
	_traversal->turn_off();

	if (keyboard) {
		if (button) {
			button->flash();
		}
	}
	else {
		if (button && !button->track(when)) {
			return;
		}
	}

	switch (com)
	{

		case comNew:
		{
			// randomize next board number by factoring in time between news
			// (don't want the next board after # K0 to always be # K1)
			int diff = (Moment::now() - root()->getLastNewBoard()).usec() / 100;
			root()->setLastNewBoard(Moment::now());
			for (int i = 0; i < diff % 16; i++)
				zrand();
			g->start(zrand(), root()->getSolveableBoards());
			break;
		}

		case comQuit:
			root()->onClose(0, 0, 0);
			break;

		case comHint:
			_board->hint()->next();
			break;

		case comClean:
			if (butler(g))
				g->mark_user_move();
			break;

		case comUndo:
			g->undo();
			break;

		case comRedo:
			g->redo();
			break;

		case comSolve:
			if (_solution) {
				if (_solution->on()) {
					_solution->change_speed(true);
				} else {
					_solution->turn_on(this);
				}
			}
			break;

		case comDeselect:
			// already deselected above
			break;

		case comCheckSolve:
		case comNone:
			// nothing to do
			break;

	}
}

void Panel::traversal_take_command(Game *g, bool take)
{
	Hint *hint = _board->hint();
	Tile *cursor = _traversal->cursor();
	Tile *selected = _board->selected();

	if (!cursor && !hint->on()) {
		bell();
	}
	else if (!cursor) {
		_traversal->with_hint(hint, take);
	}
	else if (!selected) {
		_board->select(cursor);
	}
	else if (selected == cursor) {
		_board->deselect();
	}
	else if (selected->match() == cursor->match()) {
		_board->deselect();
		g->move(selected, cursor);

	}
	else {
		_board->deselect();
		_board->select(cursor);
	}
}

void Panel::traversal_command(Game *g, TraversalCommand command)
{
	if (_solution) {
		_solution->turn_off();
	}

	switch (command)
	{

		case comTravLeft:
		case comTravRight:
			_board->hint()->turn_off();
			_traversal->next_horiz(command == comTravRight);
			break;

		case comTravUp:
		case comTravDown:
			_board->hint()->turn_off();
			_traversal->next_vert(command == comTravDown);
			break;

		case comTravTake:
		case comTravAnchor:
			traversal_take_command(g, command == comTravTake);
			break;

	}
}

void Panel::click(Game *g, int x, int y, FXint state, FXuint when, bool mouseUp)
{
	if (!mouseUp) {
		if (Tile *t = _board->find_tile(x, y)) {
			DEBUG(format("%s detected tile_command", __FUNCTION__));
			tile_command(g, t);
		}
	}

	if (hint_but->within(x, y)) {
		DEBUG(format("%s detected hint_command", __FUNCTION__));
		command(g, comHint, hint_but, false, when);

	}
	else if (undo_but->within(x, y)) {
		DEBUG(format("%s detected shift_command", __FUNCTION__));
		command(g, state & SHIFTMASK ? comRedo : comUndo, undo_but, false, when);

	}
	else if (new_but->within(x, y)) {
		DEBUG(format("%s detected new_command", __FUNCTION__));
		command(g, comNew, new_but, false, when);

	}
	else if (quit_but->within(x, y)) {
		DEBUG(format("%s detected quit_command", __FUNCTION__));
		command(g, comQuit, quit_but, false, when);

	}
	else if (clean_but->within(x, y)) {
		DEBUG(format("%s detected clean_command", __FUNCTION__));
		command(g, comClean, clean_but, false, when);

	}
	else {
		DEBUG(format("%s no command detected", __FUNCTION__));
		command(g, comNone, 0, false, when);

	}
}

void Panel::key_press(Game *g, FXint key, FXint state)
{
	if (key == KEY_Escape) {
		command(g, comDeselect, 0, true);
	}
	else if (key == KEY_H || key == KEY_h) {
		command(g, comHint, hint_but, true);
	}
	else if (key == KEY_R || key == KEY_r || ((key == KEY_U || key == KEY_u) && (state & SHIFTMASK))) {
		command(g, comRedo, undo_but, true);
	}
	else if (key == KEY_U || key == KEY_u) {
		command(g, comUndo, undo_but, true);
	}
	else if ((key == KEY_C || key == KEY_c) && !(state & CONTROLMASK)) {
		command(g, comClean, clean_but, true);
	}
	else if (key == KEY_Q || key == KEY_q) {
		command(g, comQuit, quit_but, true);
	}
	else if ((key == KEY_S || key == KEY_s) && !(state & CONTROLMASK)) {
		command(g, comSolve, 0, true);
	}
	else if (key == KEY_X || key == KEY_x) {
		command(g, comCheckSolve, 0, true);
	}
	else if (key == KEY_N || key == KEY_n) {
		command(g, comNew, new_but, true);
	}
	else if (key == KEY_Left) {
		traversal_command(g, comTravLeft);
	}
	else if (key == KEY_Right) {
		traversal_command(g, comTravRight);
	}
	else if (key == KEY_Up) {
		traversal_command(g, comTravUp);
	}
	else if (key == KEY_Down) {
		traversal_command(g, comTravDown);
	}
	else if (key == KEY_space) {
		traversal_command(g, comTravAnchor);
	}
	else if (key == KEY_Return || key == KEY_KP_Enter) {
		traversal_command(g, comTravTake);
	}
}

void Panel::bell() const
{
	window()->getApp()->beep();
}
