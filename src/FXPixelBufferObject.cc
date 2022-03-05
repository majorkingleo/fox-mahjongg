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
  name( name_ )
{}

FXPixelBufferObject::~FXPixelBufferObject()
{

}

void FXPixelBufferObject::draw( RefMImage & target )
{
	FXIcon *icon = dynamic_cast<FXIcon*>( image );

	if( !mimage.valid() ) {
		mimage = pixel_buffer->createImage( icon );
	}

	target->composite(*mimage, x, y, Magick::OverCompositeOp);
}

FXPixelBufferBackgroundObject::FXPixelBufferBackgroundObject( FXPixelBuffer *pixel_buffer_,FXImage *image_, FXDC *dc_, int x_, int y_, int floor_, const std::string & name_ )
: FXPixelBufferObject( pixel_buffer_, image_, x_, y_, floor_, name_ ),
  dc( dc_ )
{}

void FXPixelBufferBackgroundObject::draw( RefMImage & target )
{
	if( !mimage.valid() ) {
		FXImage *bg_image = pixel_buffer->createImage( target );

		{
			FXDCWindow tdc( bg_image );
			tdc.setFillStyle( dc->getFillStyle() );
			tdc.setTile( dc->getTile() );
			tdc.fillRectangle( 0, 0, bg_image->getWidth(), bg_image->getHeight() );
		}

		bg_image->restore();

		mimage = pixel_buffer->createImage( bg_image );
	}

	target->composite(*mimage, x, y, Magick::OverCompositeOp);
}



