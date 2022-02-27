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
	dc.drawImage( image, x, y );
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

	getOrCreateFloor( floor );
}

FXImage *FXPixelBuffer::getOrCreateFloor( int floor )
{
	auto it = floors.find( floor );

	if( it != floors.end() ) {
		return it->second;
	}

	FXImage *image = new FXImage( getApp(), 0, IMAGE_KEEP, getWidth(), getHeight() );
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
  DEBUG( __FUNCTION__ );

  // return FXCanvas::onPaint( obj, sel, ptr );
  for( auto it : floors ) {
	  FXImage *target = it.second;
	  int floor = it.first;

	  for( ObjectContainer *obj : objects ) {
		  if( floor == obj->getFloor() ) {
			  obj->draw( target );
		  }
	  }
  }

  for( auto it : floors ) {
	  FXImage *source = it.second;

	  FXDCWindow dc(this);
	  dc.drawArea( source, 0, 0, getWidth(), getHeight(), 0, 0 );
  }

  return 0;
}
