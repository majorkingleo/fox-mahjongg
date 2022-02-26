#include "button.hh"
#include "main.h"
#include "debug.h"

Button::Button(SwWindow *window)
  : SwWidget(window),
    _normal(0),
    _normal_mask(0),
    _lit(0),
    _lit_mask(0),

    _state(0),
    _flash_alarm(this)
{
}


bool Button::set_normal( const char *name )
{
  _normal = root()->getImageByName( name );
  _normal_mask = root()->getBitmapMaskByName( name );
  set_size(_normal->getWidth(), _normal->getHeight());
  return 1;
}

bool Button::set_lit(const char *name)
{
  _lit =  root()->getImageByName( name );
  _lit_mask = root()->getBitmapMaskByName( name );
  return 1;
}


void
Button::change_state(int new_state)
{
  int old_state = _state;
  _state = new_state;
  if ((old_state == 0) != (new_state == 0))
    draw();
}


bool
Button::handle_track_event(XEvent *e)
{
  switch (e->type) {
      
   case ButtonRelease:
    return (e->xbutton.button != 1);
      
   case MotionNotify:
     {
       int x1 = x(), x2 = x() + width(), y1 = y(), y2 = y() + height();
#warning TODOOO
       // while (XCheckTypedEvent(display(), MotionNotify, e))
	 /* nada */;
       int xm = e->xmotion.x;
       int ym = e->xmotion.y;
       bool should_light = xm >= x1 && ym >= y1 && xm < x2 && ym < y2;
       if (should_light != _state) {
	 _state = should_light;
	 draw();
       }
       return true;
     }

   default:
    return true;
    
  }
}

bool
Button::track(Time time)
{
#warning TODOOOO
#if 0
  if (XGrabPointer(display(), window(), False,
		   ButtonMotionMask | ButtonReleaseMask | OwnerGrabButtonMask,
		   GrabModeAsync, GrabModeSync, None, None, time)
	!= GrabSuccess)
    return 0;

  change_state(1);
  _flash_alarm.kill();
    
  XEvent e;
  bool more = true;
  while (more) {
    XNextEvent(display(), &e);
    more = handle_track_event(&e);
  }

  bool was_lit = _state == 1;
  change_state(0);
  
  XUngrabPointer(display(), CurrentTime);
  XFlush(display());
  while (XCheckMaskEvent(display(), ButtonReleaseMask | ButtonPressMask, &e))
    /* nada */;

  return was_lit;
#endif
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
  if (_state > 0)
    draw_image(_lit, _lit_mask, width(), height(), 0, 0);
  else
    draw_image(_normal, _normal_mask, width(), height(), 0, 0);
}

bool
Button::within(int xval, int yval) const
{
  return xval >= x() && yval >= y() && xval < x() + width()
    && yval < y() + height();
}
