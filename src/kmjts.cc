#include "kmjts.hh"
#include "tile.hh"
#include "game.hh"
#include "swgeneral.hh"
#include <cstring>
#include "main.h"
#include <format.h>
#include <debug.h>

using namespace Tools;

#define NPICTURES	(Tileset::IVORY_NPICTURES)
#define NIMAGES		(2*NPICTURES + 1)

#define NACROSS		9
#define NDOWN		5

KyodaiTileset::KyodaiTileset(MahjonggWindow *root,
							 FXPixelBuffer *pixelbuffer,
							 const unsigned char *gif_data,
							 const unsigned char* gif_data_background,
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
    _background_image(),
    _border(border),
    _zoom_factor( zoom_factor )
{

  _shadow = shadow;

  initialize_images(gif_data, gif_data_background);
  initialize();
}

KyodaiTileset::~KyodaiTileset()
{
  _images.clear();
}

void KyodaiTileset::initialize_images(const unsigned char *gif_data,
									  const unsigned char* gif_data_background )
{
	Ref < FXImage > img = new FXGIFImage(_root->getApp(), gif_data, IMAGE_KEEP);
	_base_image = _pixelbuffer->createImage(img);

	_pixelbuffer->scaleImage( _base_image, _zoom_factor );

	Ref < FXImage > img_bg = new FXGIFImage(_root->getApp(), gif_data_background, IMAGE_KEEP);
	_background_image = _pixelbuffer->createImage(img_bg);

	_pixelbuffer->scaleImage( _background_image, _zoom_factor );

	_images.resize(NIMAGES);

	_border *= _zoom_factor;
}

void KyodaiTileset::initialize()
{
	_xborder = _yborder = _border;

	_width = _base_image->columns() / NACROSS;
	_height = _base_image->rows() / NDOWN;

	DEBUG( format( "width: %d height: %d xborder: %d yborder: %d",
			_width,
			_height,
			_xborder,
			_yborder ) );
}

static int mapping[] = { 27, 28, 29, 30, /* 0-3: seasons */
36, 37, 38, 39, /* 4-7: plants; switch w/seasons?? */
40, 41, 42, /* 8-10: dragons */
31, 32, 33, 34, /* 11-14: winds */
0, 1, 2, 3, 4, 5, 6, 7, 8, /* 15-23: circles */
9, 10, 11, 12, 13, 14, 15, 16, 17, /* 24-32: bamboo */
18, 19, 20, 21, 22, 23, 24, 25, 26, /* 33-41: characters */
};


void KyodaiTileset::draw_normal(const Tile *t, SwDrawable *drawable, short x, short y)
{
	int which = picture(t->number());
	assert(which >= 0 && which < NPICTURES);

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

void KyodaiTileset::draw_lit(const Tile *t, SwDrawable *drawable, short x, short y)
{
	int which = picture(t->number());
	assert(which >= 0 && which < NPICTURES);

	which += NPICTURES;

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

	//draw(drawable, x, y, which + NPICTURES);
}

void KyodaiTileset::draw_obscured(const Tile* t, SwDrawable *drawable, short x, short y)
{
	//draw(drawable, x, y, NIMAGES - 1);

	short which = NIMAGES - 1;

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


FXPixelBuffer::RefMImage KyodaiTileset::createImage( const Tile *t, SwDrawable *drawable, short which )
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

	if (!img.valid()) {

		bool draw_lit = false;

		int pos;
		if (which == NIMAGES - 1) {
			pos = 43; // blank
		} else if (which >= NPICTURES) {
			pos = mapping[which - NPICTURES];
			draw_lit = true;
		}
		else {
			pos = mapping[which];
		}

		// _images[which] = Gif_XSubImageColormap(_gifx, gfi, gfcm, (pos % NACROSS) * _width, (pos / NACROSS) * _height,
		//		_width, _height);

		FXPixelBuffer::RefMImage mimage_fg = new Magick::Image( *_base_image );
		mimage_fg->crop( Magick::Geometry( _width, _height, (pos%NACROSS)* _width, (pos/NACROSS)* _height ) );
		DEBUG( format( "tile size: %dx%d", _width, _height ) );

		if( draw_lit ) {
			//mimage_fg->colorize( 50, Magick::ColorRGB( 0xec, 0xef, 0x4b ));
			// mimage_fg->colorize( 40, Magick::ColorRGB( 0.4, 0.4, 0.01 ));
			// mimage_fg->contrast( 100000000 );
			// mimage_fg->contrastStretch(0,1000);
			// mimage_fg->floodFillColor( Magick::Geometry( 0, 0, 5, 5 ), Magick::ColorRGB( 0.4, 0.4, 0.01 ) );

			mimage_fg->colorize( 40, Magick::ColorRGB( 0, 0, 0.4 ));
			// mimage_fg->colorize( 60, Magick::ColorRGB( 0.9, 0.9, 0.01 ));
		}

		int dx = (_shadow & 1 ? _xborder : 0);
		int dy = (_shadow & 2 ? _yborder : 0);

		img = new Magick::Image( *_background_image );
		img->composite(*mimage_fg, dx, dy, Magick::OverCompositeOp);

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

void KyodaiTileset::erase( const Tile * t, SwDrawable *drawable )
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

