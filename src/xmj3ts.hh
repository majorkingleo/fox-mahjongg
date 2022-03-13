#ifndef XMJ3TS_HH
#define XMJ3TS_HH
#include "tileset.hh"
#include "fx.h"
#include <string>
#include <vector>
#include <map>
#include <FXPixelBuffer.h>

class MahjonggWindow;

class Xmj3Tileset: public Tileset {
  
public:
	struct TileDataType
	{
		std::string name;
		const unsigned char *data;

		TileDataType( const std::string & name_,
					  const unsigned char *data_ )
		: name( name_ ),
		  data( data_ )
		{}
	};

	typedef std::vector<TileDataType> TILE_DATA;

	struct ObjectData
	{
		FXPixelBuffer::RefMImage img;
		short background;
		short foreground;

		ObjectData()
		: img(),
		  background(-1),
		  foreground(-1)
		{}

		~ObjectData()
		{}
	};

protected:

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
  
  int _image_error;
  
  Vector<short> _face_ref;
  Vector<short> _base_ref;
  Vector<short> _selected_ref;
  Vector<short> _obscured_ref;
  
  Vector<FXImage*> _images;
  Vector<FXBitmap*> _masks;
  


  TILE_DATA _tile_data;

  MahjonggWindow *_root;
  std::map<int,FXPixelBufferObject*> _objects_by_tilenumber;

  void map_one_image(const char *, int, ImageType, Vector<short> &);
  void initialize_images();
  void check_images();
  bool check() const;
  void initialize();
  
  void draw(SwDrawable *, short, short, short, short);
  
 public:
  
  Xmj3Tileset( MahjonggWindow *root, const TILE_DATA & tile_data );
  ~Xmj3Tileset();
  
  Xmj3Tileset( const Xmj3Tileset & other ) = delete;
  Xmj3Tileset & operator=( const Xmj3Tileset & other ) = delete;

  bool ok() const override	{ return true; }
  
  void draw_normal(const Tile *, SwDrawable *, short x, short y);
  void draw_lit(const Tile *, SwDrawable *, short x, short y);
  void draw_obscured(const Tile *, SwDrawable *, short x, short y);
  
 protected:
  FXPixelBuffer::RefMImage createImage( const Tile *t, SwDrawable *drawable, short background, short foreground );
  FXPixelBuffer::RefMImage createImage( const Tile *t, SwDrawable *drawable, short background );
};
#endif
