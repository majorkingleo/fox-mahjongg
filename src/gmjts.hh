#ifndef GMJTS_HH
#define GMJTS_HH
#include "fx.h"
#include "tileset.hh"
#include <map>
#include "FXPixelBuffer.h"


class GnomeMjTileset: public Tileset {
  
	struct ObjectData
	{
		FXPixelBuffer::RefMImage img;
		short which;

		ObjectData()
		: img(),
		  which(-1)
		{}

		~ObjectData()
		{}
	};


  enum ImageError {
    ieNone = 0,
    ieBadGif,
    ieBadSize,
  };
  
  int _image_error;
  
  std::vector<FXPixelBuffer::RefMImage> _images;
  
  MahjonggWindow *_root;
  std::map<int,FXPixelBufferObject*> _objects_by_tilenumber;

  FXPixelBuffer::RefMImage _base_image;
  FXPixelBuffer*  		   _pixelbuffer;
  int					   _border;

  void initialize_images( const unsigned char *gif_data );
  void check_images();
  bool check() const;
  void initialize();

  
 public:
  
  GnomeMjTileset( MahjonggWindow *root, FXPixelBuffer *pixelbuffer, const unsigned char* gif_data, int border = 4, int shadow = 1 );
  ~GnomeMjTileset();
  
  GnomeMjTileset( const GnomeMjTileset & other ) = delete;
  GnomeMjTileset & operator=( const GnomeMjTileset & other ) = delete;

  bool ok() const override { return true; }

  void draw_normal(const Tile *, SwDrawable *, short x, short y) override;
  void draw_lit(const Tile *, SwDrawable *, short x, short y) override;
  void draw_obscured(const Tile *, SwDrawable *, short x, short y) override;
  void erase( const Tile * tile, SwDrawable *drawable ) override;
  
 private:
  FXPixelBuffer::RefMImage createImage( const Tile *t, SwDrawable *drawable, short which );

};
#endif

