#ifndef XMJ3TS_HH
#define XMJ3TS_HH
#include "tileset.hh"
#include "fx.h"
#include <liblcdf/gifx.h>

#if 0

class Xmj3Tileset: public Tileset {
  
  enum ImageType {
    itFace,
    itBase,
    itSelected,
    itObscured
  };

  enum ImageError {
    ieNone = 0,
    ieBadGif,
    ieNoBase,
    ieBadSize,
  };
  
  Gif_Stream *_gfs;
  Gif_XContext *_gifx;
  Gif_Colormap *_colormap;
  int _image_error;
  
  Vector<short> _face_ref;
  Vector<short> _base_ref;
  Vector<short> _selected_ref;
  Vector<short> _obscured_ref;
  
  Vector<FXImage*> _images;
  Vector<FXBitmap*> _masks;
  
  void map_one_image(const char *, int, ImageType, Vector<short> &);
  void initialize_images();
  void check_images();
  bool check() const;
  void initialize();
  
  void draw(SwDrawable *, short, short, short, short);
  
 public:
  
  Xmj3Tileset(Gif_Stream *, Gif_XContext *);
  ~Xmj3Tileset();
  
  Xmj3Tileset( const Xmj3Tileset & other ) = delete;
  Xmj3Tileset & operator=( const Xmj3Tileset & other ) = delete;

  bool ok() const				{ return _gfs; }
  
  void draw_normal(const Tile *, SwDrawable *, short x, short y);
  void draw_lit(const Tile *, SwDrawable *, short x, short y);
  void draw_obscured(const Tile *, SwDrawable *, short x, short y);
  
};
#endif
#endif
