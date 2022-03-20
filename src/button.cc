#include "button.hh"
#include "main.h"
#include "debug.h"
#include "FXPixelBuffer.h"
#include <debug.h>
#include <format.h>

using namespace Tools;

Button::Button(SwWindow *window)
  : SwWidget(window),
    _normal(0),
    _lit(0),
    _obj(0),
	_name(),
    _state(0),
    _flash_alarm(this)
{
}


bool Button::set_normal( const char *name )
{
  _name = name;
  _normal = root()->getImageByName( name );
  set_size(_normal->getWidth(), _normal->getHeight());
  return 1;
}

bool Button::set_lit(const char *name)
{
  _lit =  root()->getImageByName( name );
  return 1;
}


void
Button::change_state(int new_state)
{
  int old_state = _state;
  _state = new_state;

  if ((old_state == 0) != (new_state == 0)) {
    draw();
  }
}

bool
Button::track( FXuint time )
{
  if( _state == 0 ) {
	 change_state(1);
  } else {
	 change_state(0);
	 return true;
  }

  return false;
}


void
Button::alarm()
{
  if (_state == 2)
    change_state(0);
}

void
Button::flash()
{
  if (_state != 1) {
    change_state(2);
    _flash_alarm.schedule(Moment::now() + Moment(0, 100000));
  }
}


void
Button::draw()
{
  FXImage *img = 0;

  if (_state > 0) {
	  img = _lit;
  } else {
	  img = _normal;
  }

  if( !_obj ) {
	  _obj = window()->setImage( img, x(), y(), 0, _name );
  } else {
	  _obj->setImage( img );
	  _obj->setX( x() );
	  _obj->setY( y() );
  }

  DEBUG( format( "%s: %s", __FUNCTION__, _name ) );
}

bool
Button::within(int xval, int yval) const
{
  return xval >= x() && yval >= y() && xval < x() + width()
    && yval < y() + height();
}
