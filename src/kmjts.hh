#ifndef KMJTS_HH
#define KMJTS_HH
#include "tileset.hh"
#include "fx.h"
#include <string>
#include <vector>
#include <map>
#include <FXPixelBuffer.h>


class KyodaiTileset: public Tileset {
  
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

  FXPixelBuffer::RefMImage _background_image;

  int _border;
  
  void initialize_images( const unsigned char *gif_data, const unsigned char* gif_data_background );
  void initialize();
  
  void draw(SwDrawable *, short, short, short);
  
 public:
  
  KyodaiTileset( MahjonggWindow *root,
				 FXPixelBuffer *pixelbuffer,
				 const unsigned char* gif_data,
				 const unsigned char* gif_data_background,
				 int border = 4, int shadow = 1 );
  ~KyodaiTileset();
  
  KyodaiTileset( const KyodaiTileset & other ) = delete;
  KyodaiTileset & operator=( const KyodaiTileset & other ) = delete;

  bool ok() const				{ return true; }
  
  void draw_normal(const Tile *, SwDrawable *, short x, short y) override;
  void draw_lit(const Tile *, SwDrawable *, short x, short y) override;
  void draw_obscured(const Tile *, SwDrawable *, short x, short y) override;
  void erase( const Tile * tile, SwDrawable *drawable ) override;
  
 private:
   FXPixelBuffer::RefMImage createImage( const Tile *t, SwDrawable *drawable, short which );
};
#endif
