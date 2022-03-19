/*
 * FXPixelBufferObject.cc
 *
 *  Created on: 02.03.2022
 *      Author: martin
 */
#include "FXPixelBufferObject.h"
#include "FXPixelBuffer.h"
#include <format.h>
#include <debug.h>

using namespace Tools;

FXPixelBufferObject::FXPixelBufferObject( FXPixelBuffer *pixel_buffer_, FXImage *image_, int x_, int y_, int floor_, const std::string & name_ )
: pixel_buffer( pixel_buffer_ ),
  x( x_ ),
  y( y_ ),
  floor( floor_ ),
  image( image_ ),
  mimage(),
  name( name_ ),
  data(0),
  redraw_required(true)
{}

FXPixelBufferObject::FXPixelBufferObject( FXPixelBuffer *pixel_buffer_, RefMImage image_, int x_, int y_, int floor_, const std::string & name_ )
: pixel_buffer( pixel_buffer_ ),
  x( x_ ),
  y( y_ ),
  floor( floor_ ),
  image( 0 ),
  mimage( image_ ),
  name( name_ ),
  data(0),
  redraw_required(true)
{}

FXPixelBufferObject::~FXPixelBufferObject()
{

}

void FXPixelBufferObject::draw( RefMImage & target )
{
	if( image ) {
		FXIcon *icon = dynamic_cast<FXIcon*>( image );

		if( !mimage.valid() ) {
			mimage = pixel_buffer->createImage( icon );
		}
	}

	target->composite(*mimage, x, y, Magick::OverCompositeOp);

	redraw_required = false;
}

void FXPixelBufferObject::setImage( FXImage *image_ )
{
	if( image == image_ ) {
		return;
	}

	image = image_;
	setDirty();
}

void FXPixelBufferObject::setImage( RefMImage image_ )
{
	if( mimage.valid() ) {
		if( mimage.address() == image_.address() ) {
			return;
		}
	}

	mimage = image_;
	redraw_required = true;
}

void FXPixelBufferObject::setDirty()
{
	mimage = RefMImage();
	redraw_required = true;
	DEBUG( format( "%d: %s valid: %d", __FUNCTION__, name, mimage.valid() ));
}


void FXPixelBufferObject::setX( int x_ )
{
	if( x != x_ ) {
		redraw_required = true;
	}
	x = x_;
}

void FXPixelBufferObject::setY( int y_ )
{
	if( y != y_ ) {
		redraw_required = true;
	}

	y = y_;
}


FXPixelBufferBackgroundObject::FXPixelBufferBackgroundObject( FXPixelBuffer *pixel_buffer_,FXImage *image_, FXDC *dc_, int x_, int y_, int floor_, const std::string & name_ )
: FXPixelBufferObject( pixel_buffer_, image_, x_, y_, floor_, name_ ),
  dc( dc_ )
{}

void FXPixelBufferBackgroundObject::draw( RefMImage & target )
{
	if( !mimage.valid() || redraw_required ) {
		FXImage *bg_image = pixel_buffer->createImage( target );

		{
			FXDCWindow tdc( bg_image );
			tdc.setFillStyle( dc->getFillStyle() );
			tdc.setTile( dc->getTile() );
			tdc.fillRectangle( 0, 0, bg_image->getWidth(), bg_image->getHeight() );
		}

		bg_image->restore();
		DEBUG( format( "%s: bg_image width: %d height: %d", __FUNCTION__, bg_image->getWidth(), bg_image->getHeight()));

		mimage = pixel_buffer->createImage( bg_image );
		delete bg_image;
	}

	DEBUG( format( "%s: target width: %d height: %d", __FUNCTION__, target->columns(), target->rows()));

	target->composite(*mimage, x, y, Magick::OverCompositeOp);
	redraw_required = false;
}




