#ifndef SWGENERAL_HH
#define SWGENERAL_HH
#include <liblcdf/gifx.h>
#include <X11/Xlib.h>


class SwDrawable {
  
  SwDrawable(const SwDrawable &);
  SwDrawable &operator=(const SwDrawable &);
  
 public:
  
  SwDrawable()					{ }
  virtual ~SwDrawable();
  
  virtual Gif_XContext *get_gif_x_context() = 0;
  
  void draw_image(Pixmap src, int w, int h, int x, int y);
  void draw_image(Pixmap src, Pixmap mask, int w, int h, int x, int y);  
  virtual void draw_subimage(Pixmap src, Pixmap mask, int src_x, int src_y,
			     int w, int h, int x, int y) = 0;
  
  virtual void clear_area(int x, int y, int w, int h);
  virtual void invalidate(int x, int y, int w, int h);
  
};

class SwWindow: public SwDrawable {
  
  Display *_display;
  Window _window;
  int _depth;
  
  GC _copy_gc;
  GC _masked_image_gc;
  
  Gif_XContext *_gifx;
  
 public:
  
  SwWindow(Display *, Window, int = -1);
  ~SwWindow();
  
  SwWindow( const SwWindow & other ) = delete;
  SwWindow & operator=( const SwWindow & other ) = delete;

  Display *display() const			{ return _display; }
  Window window() const				{ return _window; }
  int depth() const				{ return _depth; }
  
  Gif_XContext *get_gif_x_context();
  
  void draw_subimage(Pixmap, Pixmap, int, int, int, int, int, int);
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
  
  SwClippedWindow(Display *, Window, int = -1);
  
  SwClippedWindow( const SwClippedWindow & other ) = delete;
  SwClippedWindow & operator=( const SwClippedWindow & other ) = delete;

  bool clipped() const				{ return _clipping; }
  void unclip()					{ _clipping = false; }
  void intersect_clip(int x, int y, int w, int h);
  void union_clip(int x, int y, int w, int h);
  
  void draw_subimage(Pixmap, Pixmap, int, int, int, int, int, int);
  void clear_area(int, int, int, int);
  void invalidate(int, int, int, int);
  
};

//

class SwImage {

 protected:

  Display *_display;
  Pixmap _source;
  Pixmap _mask;
  int _width;
  int _height;
  
 public:
  
  SwImage(Display *d, Pixmap s, int w, int h)
  : _display(d),
    _source(s),
    _mask(0),
    _width(w),
    _height(h)
  {
  }

  SwImage(Display *d, Pixmap s, Pixmap m, int w, int h)
  : _display(d),
    _source(s),
    _mask(m),
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

  void set_image(Display *d, Pixmap s, Pixmap m, int w, int h) {
    _display = d; _source = s; _mask = m; _width = w; _height = h;
  }
  
  virtual void draw(SwDrawable *, int x, int y);
  
};


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


inline void
SwDrawable::draw_image(Pixmap src, int w, int h, int x, int y)
{
  draw_subimage(src, 0, 0, 0, w, h, x, y);
}

inline void
SwDrawable::draw_image(Pixmap src, Pixmap mask, int w, int h, int x, int y)
{
  draw_subimage(src, mask, 0, 0, w, h, x, y);
}

inline
SwGifImage::SwGifImage(Gif_Stream *gfs, int image_number)
: _gfs(0),
  _gfi(0),
  _made(false)
{
  initialize(gfs, Gif_GetImage(gfs, image_number));
}

#endif
