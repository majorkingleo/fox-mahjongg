#ifndef GMJTS_HH
#define GMJTS_HH
#include "fx.h"
#include "tileset.hh"

#if 0
class MahjonggWindow;

class GnomeMjTileset: public Tileset {
  
  enum ImageError {
    ieNone = 0,
    ieBadGif,
    ieBadSize,
  };
  
  int _image_error;
  
  Vector<FXImage*> _images;
  Vector<FXImage*> _masks;
  
  void initialize_images();
  void check_images();
  bool check() const;
  void initialize();
  
  void draw(SwDrawable *, short, short, short);
  
 public:
  
  GnomeMjTileset( MahjonggWindow *root );
  ~GnomeMjTileset();
  
  GnomeMjTileset( const GnomeMjTileset & other ) = delete;
  GnomeMjTileset & operator=( const GnomeMjTileset & other ) = delete;

  bool ok() const override { return true; }

  void draw_normal(const Tile *, SwDrawable *, short x, short y);
  void draw_lit(const Tile *, SwDrawable *, short x, short y);
  void draw_obscured(const Tile *, SwDrawable *, short x, short y);
  
};
#endif
#endif
