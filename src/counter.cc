#include "counter.hh"
#include "debug.h"
#include "main.h"
#include <format.h>

using namespace Tools;

static FXImage* digits[10];
static FXBitmap* masks[10];
static int digit_width, digit_height;

static void setup_digits( MahjonggWindow *root )
{
  if (digits[0]) {
	  return;
  }

  for( unsigned i = 0; i < 10; i++ ) {
	  digits[i] = root->getImageByName( format( "%d", i ) );
	  masks[i] = root->getBitmapMaskByName( format( "%d", i ) );
  }
  digit_width = digits[0]->getWidth();
  digit_height = digits[0]->getHeight();
}


FancyCounter::FancyCounter(SwWindow *parent, int num_digits)
  : SwWidget(parent), _digits(num_digits), _value(0)
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
  for (int d = _digits - 1; d >= 0; d--) {
    int digit = v % 10;
    draw_image(digits[digit], masks[digit], digit_width,
	       digit_height, d * digit_width, 0);
    v /= 10;
    if (v == 0) break;
  }
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
