#include "counter.hh"
#include "debug.h"
#include "main.h"
#include <format.h>
#include "FXPixelBuffer.h"
#include <format.h>
#include <string_utils.h>

using namespace Tools;

static FXImage* digits[10];
static int digit_width, digit_height;

static void setup_digits( MahjonggWindow *root )
{
  if (digits[0]) {
	  return;
  }

  for( unsigned i = 0; i < 10; i++ ) {
	  digits[i] = root->getImageByName( format( "%d", i ) );
  }
  digit_width = digits[0]->getWidth();
  digit_height = digits[0]->getHeight();
}


FancyCounter::FancyCounter(SwWindow *parent, int num_digits)
  : SwWidget(parent),
    _digits(num_digits),
    _value(0),
    _obj_digits()
{
  setup_digits(parent->root());

  set_size(digit_width * num_digits, digit_height);
}


void
FancyCounter::draw()
{
  DEBUG( "draw" );

  clear_area(0, 0, width(), height());
  int v = _value;

  std::string text = format( "%d", _value );

  // remove objects, not required anymore
  while( _obj_digits.size() > text.size() ) {
	  FXPixelBufferObject *obj =_obj_digits.front();
	  _obj_digits.pop_front();
	  window()->remove( obj );
  }

  // create objects, if required
  for( size_t i = 0; i < text.size(); i++ ) {
	  if( i >= _obj_digits.size() ) {
		  FXImage *img = digits[s2x<int>( format("%c",text[i])) ];

		  FXPixelBufferObject *obj = window()->setImage( img, x(), y(), 0, format( "%c", text[i] ) );
		  _obj_digits.push_back( obj );
	  }
  }

  std::vector<FXPixelBufferObject*> vObjects( _obj_digits.begin(), _obj_digits.end() );

  // create objects, if required
  for( size_t i = 0; i < text.size(); i++ ) {
	  FXImage *img = digits[s2x<int>( format("%c", text[i])) ];

	  vObjects[i]->setImage( img );
	  vObjects[i]->setX( x() + i * digit_width );
	  vObjects[i]->setY( y() );
  }
#if 0

  for (int d = _digits - 1, numbers = 0; d >= 0; d--, numbers++ ) {
    int digit = v % 10;
    v /= 10;
    if (v == 0) break;
  }

  if( _obj_digits.size() != numbers ) {

  }

  for (int d = _digits - 1; d >= 0; d--) {
    int digit = v % 10;
    draw_image(digits[digit], masks[digit], digit_width,
	       digit_height, d * digit_width, 0);
    v /= 10;
    if (v == 0) break;
  }
#endif
}



FancyTileCounter::FancyTileCounter(SwWindow *window)
  : FancyCounter(window, 3)
{
}

void
FancyTileCounter::start_hook(Game *g)
{
  set_value(g->nremaining());
}

void
FancyTileCounter::move_made_hook(Game *g)
{
  set_value(g->nremaining());
}
