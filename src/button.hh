#ifndef BUTTON_HH
#define BUTTON_HH
#include "panel.hh"
#include "alarm.hh"
#include "swwidget.hh"

class Button: public AlarmHooks, public SwWidget {
  
  FXImage  *_normal;
  FXImage  *_lit;
  FXPixelBufferObject *_obj;
  std::string _name;
  
  int _state;				// 0 off, 1 lit, 2 flashing
  Alarm _flash_alarm;
  
  void change_state(int);
  
 public:
  
  Button(SwWindow *);
  
  Button( const Button & other ) = delete;
  Button & operator=( const Button & other ) = delete;

  bool set_normal( const char * name );
  bool set_lit( const char * name );
  
  void draw();
  
  bool within(int, int) const;
  bool track( FXuint time );

  void flash();
  void alarm();
  
};

#endif
