#ifndef BUTTON_HH
#define BUTTON_HH
#include "panel.hh"
#include "alarm.hh"
#include "swwidget.hh"

class Button: public AlarmHooks, public SwWidget {
  
  FXImage  *_normal;
  FXBitmap *_normal_mask;
  FXImage  *_lit;
  FXBitmap *_lit_mask;
  
  int _state;				// 0 off, 1 lit, 2 flashing
  Alarm _flash_alarm;
  
  void change_state(int);
  bool handle_track_event(XEvent *);
  
 public:
  
  Button(SwWindow *);
  
  Button( const Button & other ) = delete;
  Button & operator=( const Button & other ) = delete;

  bool set_normal( const char * name );
  bool set_lit( const char * name );
  
  void draw();
  
  bool within(int, int) const;
  bool track(Time);

  void flash();
  void alarm();
  
};


inline void
Button::draw()
{
  if (_state > 0)
    draw_image(_lit, _lit_mask, width(), height(), 0, 0);
  else
    draw_image(_normal, _normal_mask, width(), height(), 0, 0);
}

inline bool
Button::within(int xval, int yval) const
{
  return xval >= x() && yval >= y() && xval < x() + width()
    && yval < y() + height();
}

#endif
