/*
 * FXPixelBuffer.cc
 *
 *  Created on: 27.02.2022
 *      Author: martin
 */
#include "FXPixelBuffer.h"
#include "debug.h"
#include <format.h>

using namespace Tools;

FXDEFMAP(FXPixelBuffer) FXPixelBufferMap[]={
		FXMAPFUNC(SEL_PAINT,0,FXPixelBuffer::onPaint)
};

// Object implementation
FXIMPLEMENT(FXPixelBuffer,FXCanvas,FXPixelBufferMap,ARRAYNUMBER(FXPixelBufferMap));

void FXPixelBuffer::ObjectContainer::draw( FXImage *target )
{
	FXDCWindow dc( target );

	FXIcon *icon = dynamic_cast<FXIcon*>( image );

	if( icon ) {
		dc.drawIcon( icon, x, y );
	} else {
		dc.drawImage( image, x, y );
	}
}

void FXPixelBuffer::BackgroundObjectContainer::draw( FXImage *target )
{
	FXDCWindow tdc( target );
	tdc.setFillStyle( dc->getFillStyle() );
	tdc.setTile( dc->getTile() );
	tdc.fillRectangle( 0, 0, target->getWidth(), target->getHeight() );
}

FXPixelBuffer::FXPixelBuffer()
: objects(),
  floors(),
  owned_dc(),
  owned_images()
{

}

FXPixelBuffer::FXPixelBuffer(FXComposite* p,FXObject* tgt,FXSelector sel,FXuint opts,FXint x,FXint y,FXint w,FXint h)
: FXCanvas( p, tgt, sel, opts, x, y, w, h ),
  objects(),
  floors(),
  owned_dc(),
  owned_images()
{

}

FXPixelBuffer::~FXPixelBuffer()
{
	for( auto dc : owned_dc ) {
		delete dc;
	}

	for( auto img : owned_images ) {
		delete img;
	}

	for( auto obj : objects ) {
		delete obj;
	}
}

void FXPixelBuffer::detach()
{
	for( auto img : owned_images ) {
		img->detach();
	}
}

void FXPixelBuffer::create()
{
	FXCanvas::create();

	for( auto img : owned_images ) {
		img->create();
	}
}

void FXPixelBuffer::setTiledBackgroundImage( FXImage *image )
{
	FXDC *dc = new FXDC( getApp() );
	dc->setFillStyle( FILL_TILED );
	dc->setTile( image );

	setBackground( image, dc );
}

void FXPixelBuffer::setBackground( FXImage *img, FXDC *dc, int floor )
{
	owned_dc.push_back( dc );
	objects.push_back( new BackgroundObjectContainer(img, dc, 0, 0, floor ) );

	getOrCreateFloor( floor, true );
}

FXImage *FXPixelBuffer::getOrCreateFloor( int floor, bool base )
{
	auto it = floors.find( floor );

	if( it != floors.end() ) {
		return it->second;
	}

	FXImage *image = 0;

	if( base ) {
		image = new FXImage( getApp(), 0, IMAGE_KEEP, getWidth(), getHeight() );
	} else {
		image = new FXIcon( getApp(), 0, 0, IMAGE_KEEP, getWidth(), getHeight() );
	}

	owned_images.push_back( image );
	image->create();

	floors[floor] = image;

	return image;
}

int FXPixelBuffer::getLowestFloor() const
{
	return floors.begin()->first;
}

int FXPixelBuffer::getHighestFloor() const
{
	return floors.rbegin()->first;
}

// Canvas is an object drawn by another
long FXPixelBuffer::onPaint(FXObject* obj,FXSelector sel,void* ptr)
{
  // return FXCanvas::onPaint( obj, sel, ptr );
  for( auto it : floors ) {
	  FXImage *target = it.second;
	  int floor = it.first;

	  {
		  FXDCWindow dc( target );
		  dc.setForeground( FXRGBA(0,255,0,0) );
		  dc.setBackground( FXRGBA(0,255,0,0) );
		  dc.fillRectangle( 0,0, getWidth(), getHeight() );
	  }


	  for( ObjectContainer *obj : objects ) {
		  if( floor == obj->getFloor() ) {
			  obj->draw( target );
		  }
	  }
  }

  FXImage buffer( getApp(), 0, IMAGE_KEEP, getWidth(), getHeight() );
  buffer.create();

  FXColor *pixels = 0;
  allocElms( pixels, getWidth() * getHeight()  );

  buffer.setData( pixels, IMAGE_KEEP | IMAGE_OWNED, getWidth(), getHeight() );

  for( auto it : floors ) {
	  FXImage *source = it.second;

	  if( !source->getData() ) {
		  DEBUG( "icon option IMAGE_KEEP not set" );
		  source->restore();
	  }

#if 0
	  FXDCWindow dc(this);

	  FXIcon *icon = dynamic_cast<FXIcon*>( source );

	  std::string extra;

	  if( icon ) {
		  extra = "as icon";
		  dc.drawIcon( icon, 0, 0 );
		  // dc.drawImage( icon, 0, 0 );
		  if( !icon->getData() ) {
			  DEBUG( "icon option IMAGE_KEEP not set" );
			  icon->restore();
		  }

		  FXColor transparent_color = FXRGBA( 0, 255, 0, 0 );

		  for( unsigned x = 0; x < width; x++ ) {
			  for( unsigned y = 0; y < height; y++ ) {
				  FXColor color = icon->getPixel( x, y );

				  if( transparent_color != color ) {
					  dc.setPixel( x, y, color );
				  }
			  }
		  }

	  } else {
		  dc.drawArea( source, 0, 0, getWidth(), getHeight(), 0, 0 );
	  }
#endif
	  FXColor transparent_color = FXRGBA( 0, 255, 0, 0 );

	  for( unsigned x = 0; x < width; x++ ) {
		  for( unsigned y = 0; y < height; y++ ) {
			  FXColor color = source->getPixel( x, y );
			  //std::cout << format( "0x%x", FXALPHAVAL( color )) << std::endl;
			  if( FXALPHAVAL( color ) != 0 ) {
				  buffer.setPixel( x, y, color );
			  }
		  }
	  }

	  DEBUG( format( "%s: drawing floor: %d", __FUNCTION__, it.first ) );;
  }

  buffer.render();

  FXDCWindow dc(this);
  dc.drawImage( &buffer, 0, 0 );

  return 0;
}

void FXPixelBuffer::setImage( FXImage *img, int x, int y, int floor )
{
	objects.push_back( new ObjectContainer(img, x, y, floor ) );

	getOrCreateFloor( floor );
}
