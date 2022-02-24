#ifndef KMJTS_HH
#define KMJTS_HH
#include <liblcdf/gif.h>
#include <liblcdf/gifx.h>
#include "tileset.hh"

#if 0
class KyodaiTileset: public Tileset {
  
  enum ImageError {
    ieNone = 0,
    ieBadGif,
    ieBadSize,
  };
  
  Gif_Stream *_gfs;
  Gif_XContext *_gifx;
  Gif_Colormap *_colormap;
  Gif_Colormap *_hi_colormap;
  Gif_Colormap *_background_colormap;
  int _image_error;
  
  Vector<Pixmap> _images;
  Pixmap _background;
  Pixmap _background_mask;
  
  void initialize_images();
  void check_images();
  bool check() const;
  void initialize();
  
  void draw(SwDrawable *, short, short, short);
  
 public:
  
  KyodaiTileset(Gif_Stream *, Gif_XContext *);
  ~KyodaiTileset();
  
  KyodaiTileset( const KyodaiTileset & other ) = delete;
  KyodaiTileset & operator=( const KyodaiTileset & other ) = delete;

  bool ok() const				{ return _gfs; }
  
  void draw_normal(const Tile *, SwDrawable *, short x, short y);
  void draw_lit(const Tile *, SwDrawable *, short x, short y);
  void draw_obscured(const Tile *, SwDrawable *, short x, short y);
  
};
#endif
#endif
