#ifndef SWWIDGET_HH
#define SWWIDGET_HH
#include "swgeneral.hh"

class SwWidget: public SwDrawable {

protected:
  SwWindow *_swwindow;
  
  int _x;
  int _y;
  int _width;
  int _height;
  
  bool _visible;
  
 public:
  
  SwWidget(SwWindow *);
  virtual ~SwWidget()			{ }
  
  SwWidget( const SwWidget & other ) = delete;
  SwWidget & operator=( const SwWidget & other ) = delete;

  FXApp *display() const		{ return _swwindow->display(); }
  FXPixelBuffer* window() const			{ return _swwindow->window(); }
  MahjonggWindow* root() const { return _swwindow->root(); }
  
  int x() const				{ return _x; }
  int y() const				{ return _y; }
  int x_pos() const			{ return _x; } // in case x is a var.
  int y_pos() const			{ return _y; } // in case y is a var.
  int width() const			{ return _width; }
  int height() const			{ return _height; }
  
  bool visible() const			{ return _visible; }
  void set_visible()			{ _visible = true; }
  
  void set_position(int x, int y)	{ _x = x; _y = y; }
  void set_size(int w, int h)		{ _width = w; _height = h; }
  
  void draw_subimage(FXImage *source , FXBitmap *mask, int, int, int, int, int, int) override;
  void clear_area(int, int, int, int);
  
  void invalidate()			{ invalidate(0, 0, _width, _height); }
  void invalidate(int x, int y, int w, int h);
  
};

#endif
