#include "matches.hh"
#include "main.h"
#include <debug.h>

using namespace Tools;

MatchCount::MatchCount(SwWindow *window, const char *name)
  : SwWidget(window),
    _game(0),
    _one_image(0),
    _objects(),
    _one_width(0),
    _one_height(0),
    _count(0)
{
	_one_image  = root()->getImageByName( name );
    _one_width  = _one_image->getWidth();
    _one_height = _one_image->getHeight();
}

void
MatchCount::set_game(Game *g)
{
  assert(!_game);
  _game = g;
  _game->add_hook(this);
}

void
MatchCount::draw(int new_count, bool fast_display)
{
	if (!fast_display) {
		_count = 0;
	}

	int side = width() / _one_width;
	if (side == 0) {
		side = 1;
	}

	int level = (_count ? (_count - 1) / side : 0);
	int new_level = (new_count ? (new_count - 1) / side : 0);


	if (level > new_level) {

		_count = (new_level + 1) * side;
		level = new_level;
	}


	if( new_count < _objects.size() ) {

		for( int idx = _objects.size() - 1; idx >= 0 && idx > new_count; idx-- ) {

			FXPixelBufferObject* & obj = _objects[idx];
			if( obj ) {
				window()->remove( obj );
				obj = 0;
			}
		}

		_objects.resize(new_count);
	}

	int pos = _count % side;
	int y = (_count / side) * _one_height;

	if( _objects.size() < new_count ) {
		_objects.resize(new_count);
	}

	for (int i = _count; i < new_count; i++) {

		int x = pos * _one_width;

		FXPixelBufferObject* & obj = _objects[i];

		if( !obj ) {
			obj = window()->setImage( _one_image, x + _x, y + _y, 0, format( "counter %d", i ) );
		} else {
			// obj->setImage( img ); // image type never changes
			obj->setX( x + _x );
			obj->setY( y + _y );
		}

		if (++pos >= side) {
			pos = 0;
			y += _one_height;
		}
	}

	_count = new_count;
}

void
MatchCount::start_hook(Game *g)
{
  change(g->possible_moves());
}

void
MatchCount::move_made_hook(Game *g)
{
  change(g->possible_moves());
}
