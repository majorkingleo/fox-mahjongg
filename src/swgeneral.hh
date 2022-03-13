#ifndef SWGENERAL_HH
#define SWGENERAL_HH

#include <liblcdf/gif.h>
#include "fx.h"
#include <string>

class MahjonggWindow;
class FXPixelBuffer;
class FXPixelBufferObject;

class SwDrawable {
  
  SwDrawable(const SwDrawable &);
  SwDrawable &operator=(const SwDrawable &);
  
 public:
  
  SwDrawable()					{ }
  virtual ~SwDrawable();

  void draw_image(FXImage *src, int w, int h, int x, int y);
  void draw_image(FXImage *src, FXBitmap *mask, int w, int h, int x, int y);
  virtual void draw_subimage(FXImage *src, FXBitmap *mask, int src_x, int src_y,
			     int w, int h, int x, int y) = 0;
  
  virtual void clear_area(int x, int y, int w, int h);
  virtual void invalidate(int x, int y, int w, int h);
  
  virtual FXPixelBuffer* window() const = 0;

};

class SwWindow: public SwDrawable {
  

  FXApp    *_display;
  FXPixelBuffer *_window;
  MahjonggWindow *_root;
  
 public:
  
  SwWindow( FXApp *app, FXPixelBuffer *window, MahjonggWindow *root );
  ~SwWindow();
  
  SwWindow( const SwWindow & other ) = delete;
  SwWindow & operator=( const SwWindow & other ) = delete;

  FXApp *display() const	{ return _display; }
  FXPixelBuffer* window() const	override { return _window; }
  MahjonggWindow* root() const { return _root; }
  
  void draw_subimage(FXImage *source, FXBitmap *mask, int, int, int, int, int, int) override;
  void clear_area(int, int, int, int);
  
};

class SwClippedWindow: public SwWindow {
  
  bool _clipping;
  int _clip_left;
  int _clip_top;
  int _clip_right;
  int _clip_bottom;
  
  void do_clip(int &x, int &y, int &w, int &h) const;
  
 public:
  
  SwClippedWindow(FXApp *app, FXPixelBuffer *window, MahjonggWindow *root );
  
  SwClippedWindow( const SwClippedWindow & other ) = delete;
  SwClippedWindow & operator=( const SwClippedWindow & other ) = delete;

  bool clipped() const				{ return _clipping; }
  void unclip()					{ _clipping = false; }
  void intersect_clip(int x, int y, int w, int h);
  void union_clip(int x, int y, int w, int h);
  
  void draw_subimage(FXImage *source, FXBitmap *mask, int, int, int, int, int, int);
  void clear_area(int, int, int, int);
  void invalidate(int, int, int, int);
  
};

//

class SwImage {

 protected:

  FXApp *_display;
  FXImage *_source;
  FXBitmap *_mask;
  int _width;
  int _height;
  
 public:
  
  SwImage(FXApp *app, FXImage *s, int w, int h)
  : _display(app),
    _source(s),
    _mask(0),
    _width(w),
    _height(h)
  {
  }

  SwImage(FXApp *app, FXImage *source, FXBitmap *mask, int w, int h)
  : _display(app),
    _source(source),
    _mask(mask),
    _width(w),
    _height(h)
  {
  }

  SwImage()
  : _display(0),
     _source(0),
     _mask(0),
     _width(0),
     _height(0)
   {
   }

  virtual ~SwImage();
  
  SwImage( const SwImage & other ) = delete;
  SwImage & operator=( const SwImage & other ) = delete;

  void set_image(FXApp *app, FXImage *source, FXBitmap *mask, int w, int h) {
    _display = app; _source = source; _mask = mask; _width = w; _height = h;
  }
  
  virtual void draw(SwDrawable *, int x, int y);
  
};

#if 0
class SwGifImage: public SwImage {

  Gif_Stream *_gfs;
  Gif_Image *_gfi;
  bool _made;
  
  void initialize(Gif_Stream *, Gif_Image *);
  void create_pixmaps(SwDrawable *);
  
 public:

  SwGifImage( const SwGifImage & other ) = delete;
  SwGifImage & operator=( const SwGifImage & other ) = delete;

  SwGifImage(Gif_Stream *gfs, Gif_Image *gfi)
  : _gfs(0),
    _gfi(0),
    _made(false)
  {
	  initialize(gfs, gfi);
  }

  SwGifImage(Gif_Stream *gfs, int n);
  ~SwGifImage();

  void draw(SwDrawable *, int x, int y);
};
#endif


#endif
