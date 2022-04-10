#include "gmjts.hh"
#include "tile.hh"
#include "swgeneral.hh"
#include <cstring>
#include "main.h"
#include <format.h>
#include <debug.h>

using namespace Tools;

#define NPICTURES	(Tileset::IVORY_NPICTURES)
#define NIMAGES		(2*NPICTURES + 1)

#define NACROSS		21
#define NDOWN		4

GnomeMjTileset::GnomeMjTileset(MahjonggWindow *root,
							   FXPixelBuffer *pixelbuffer,
							   const unsigned char *gif_data,
							   int border,
							   int shadow,
							   double zoom_factor )
: Tileset("ivory"),
  _image_error(ieNone),
  _images(),
  _root(root),
  _objects_by_tilenumber(),
  _base_image(),
  _pixelbuffer( pixelbuffer ),
  _border(border),
  _zoom_factor(zoom_factor)
{
	_shadow = shadow;

	initialize_images(gif_data);
	if (check()) {
		initialize();
	}
}

GnomeMjTileset::~GnomeMjTileset()
{
	_images.clear();
}

void GnomeMjTileset::initialize_images(const unsigned char *gif_data)
{
	Ref<FXImage> img = new FXGIFImage(_root->getApp(), gif_data, IMAGE_KEEP);
	_base_image = _pixelbuffer->createImage(img);

	_pixelbuffer->scaleImage( _base_image, _zoom_factor );

	_images.resize(NIMAGES);
	_border *= _zoom_factor;

	check_images();
}

void GnomeMjTileset::check_images()
{
	// Check the size
	if (_base_image->columns() % NACROSS != 0 || _base_image->rows() % NDOWN != 0) {
		_image_error = ieBadSize;
		DEBUG( format( "Image has bad size %dx%d : %d %% %d = %d   %d %% %d = %d ",
					   _base_image->columns(),
					   _base_image->rows(),
					   _base_image->columns(),
					   NACROSS,
					   _base_image->columns() % NACROSS,
					   _base_image->rows(),
					   NDOWN,
					   _base_image->rows() % NDOWN ) );
		return;
	}

	_image_error = ieNone;
}

bool GnomeMjTileset::check() const
{
	return _image_error == ieNone;
}

void GnomeMjTileset::initialize()
{
  _xborder = _yborder = _border;

  _width = (_base_image->columns() / NACROSS) - _xborder;
  _height = (_base_image->rows() / NDOWN) - _yborder;

}

static int mapping[] = { 33, 34, 35, 36, /* 0-3: seasons */
38, 39, 40, 41, /* 4-7: plants; switch w/seasons?? */
14, 37, 13, /* 8-10: dragons */
9, 11, 12, 10, /* 11-14: winds */
0, 1, 2, 3, 4, 5, 6, 7, 8, /* 15-23: circles */
24, 25, 26, 27, 28, 29, 30, 31, 32, /* 24-32: bamboo */
15, 16, 17, 18, 19, 20, 21, 22, 23, /* 33-41: characters */
};

void GnomeMjTileset::draw_normal(const Tile *t, SwDrawable *drawable, short x, short y)
{
  DEBUG( format( "create tile: % 3d at %03dx%03d level: %d ", t->number(), x, y, t->lev() ));


  int which = picture(t->number());
  assert(which >= 0 && which < NPICTURES);
  // draw(drawable, x, y, which);

  FXPixelBufferObject *obj = _objects_by_tilenumber[t->number()];
  FXPixelBuffer::RefMImage image;

  if( !obj ) {

	  image = createImage( t, drawable, which );
	  obj = _objects_by_tilenumber[t->number()];

  } else {
	  ObjectData *od = (ObjectData*)obj->getData();

	  // nothing changed
	  if( od->which == which ) {
		  image = od->img;
	  } else {
		  image = createImage( t, drawable, which );
		  obj = _objects_by_tilenumber[t->number()];
	  }
  }

  obj->setImage( image );
  obj->setX( x );
  obj->setY( y );
}

void GnomeMjTileset::draw_lit(const Tile *t, SwDrawable *drawable, short x, short y)
{

  int which = picture(t->number());
  assert(which >= 0 && which < NPICTURES);
//  draw(drawable, x, y, which + NPICTURES);

  which = which + NPICTURES;

  FXPixelBufferObject *obj = _objects_by_tilenumber[t->number()];
  FXPixelBuffer::RefMImage image;

  if( !obj ) {

	  image = createImage( t, drawable, which );
	  obj = _objects_by_tilenumber[t->number()];

  } else {
	  ObjectData *od = (ObjectData*)obj->getData();

	  // nothing changed
	  if( od->which == which ) {
		  image = od->img;
	  } else {
		  image = createImage( t, drawable, which );
		  obj = _objects_by_tilenumber[t->number()];
	  }
  }

  obj->setImage( image );
  obj->setX( x );
  obj->setY( y );
}

void GnomeMjTileset::draw_obscured(const Tile *t, SwDrawable *drawable, short x, short y)
{
	// draw(drawable, x, y, 2*NPICTURES);
	short which = 2*NPICTURES;

	FXPixelBufferObject *obj = _objects_by_tilenumber[t->number()];
	FXPixelBuffer::RefMImage image;

	if( !obj ) {

		image = createImage( t, drawable, which );
		obj = _objects_by_tilenumber[t->number()];

	} else {
		ObjectData *od = (ObjectData*)obj->getData();

		// nothing changed
		if( od->which == which ) {
			image = od->img;
		} else {
			image = createImage( t, drawable, which );
			obj = _objects_by_tilenumber[t->number()];
		}
	}

	obj->setImage( image );
	obj->setX( x );
	obj->setY( y );
}

FXPixelBuffer::RefMImage GnomeMjTileset::createImage( const Tile *t, SwDrawable *drawable, short which )
{
	// clear object data
	int insert_idx = -1;

	if( _objects_by_tilenumber[t->number()] ) {
		FXPixelBufferObject *obj = _objects_by_tilenumber[t->number()];
		ObjectData *od = (ObjectData*)obj->getData();
		delete od;
		obj->setData(0);
		insert_idx = drawable->window()->remove( obj );
	}

	FXPixelBuffer::RefMImage img = _images.at(which);

	int w = _width + _xborder, h = _height + _yborder;

	if (!img.valid()) {
		int pos;
		if (which == 2*NPICTURES) {
			pos = 37; // white dragon
		} else if (which >= NPICTURES) {
			pos = mapping[which - NPICTURES] + 42;
		} else {
			pos = mapping[which];
		}
		//_images[which] = Gif_XSubImageColormap
		//		(_gifx, gfi, _colormap, (pos%NACROSS)*w, (pos/NACROSS)*h, w, h);
		img = new Magick::Image( *_base_image );
		img->crop( Magick::Geometry( w, h, (pos%NACROSS)*w, (pos/NACROSS)*h ) );
		 _images[which] = img;

		//_masks[which] = Gif_XSubMask
		//		(_gifx, gfi, (pos%NACROSS)*w, (pos/NACROSS)*h, w, h);
	}


	FXPixelBufferObject *obj = drawable->window()->setImage( img, 0, 0, t->lev(), format( "Tile %d", t->number()), insert_idx );
	_objects_by_tilenumber[t->number()] = obj;
	ObjectData *od = new ObjectData();
	od->img = img;
	od->which = which;
	obj->setData(od);

	return img;
}

void GnomeMjTileset::erase( const Tile * t, SwDrawable *drawable )
{
	if( t == NULL ) {
		for( auto pair : _objects_by_tilenumber ) {
			if( pair.second ) {
				ObjectData *od = (ObjectData*)pair.second->getData();
				delete od;
				pair.second->setData(0);
				drawable->window()->remove( pair.second );
			}
		}
		_objects_by_tilenumber.clear();
		return;
	}

	// clear object data
	if( _objects_by_tilenumber[t->number()] ) {
		FXPixelBufferObject *obj = _objects_by_tilenumber[t->number()];
		ObjectData *od = (ObjectData*)obj->getData();
		delete od;
		obj->setData(0);
		drawable->window()->remove( obj );
		_objects_by_tilenumber[t->number()] = 0;
	}
}

