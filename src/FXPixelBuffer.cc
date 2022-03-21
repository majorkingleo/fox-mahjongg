/*
 * FXPixelBuffer.cc
 *
 *  Created on: 27.02.2022
 *      Author: martin
 */
#include "FXPixelBuffer.h"
#include "debug.h"
#include <format.h>
#include <cpp_util.h>
#include <main.h>

#if defined(_OPENMP)
#include <omp.h>
#endif

using namespace Tools;

static unsigned long get_microtime()
{
    struct timeval tv1;
    struct timezone tz1;

    gettimeofday(&tv1,&tz1);

    return (unsigned long)(tv1.tv_sec * 1000 + tv1.tv_usec / 1000) ;
}

FXDEFMAP(FXPixelBuffer) FXPixelBufferMap[]={
		FXMAPFUNC(SEL_PAINT,0,FXPixelBuffer::onPaint)
};

// Object implementation
FXIMPLEMENT(FXPixelBuffer,FXCanvas,FXPixelBufferMap,ARRAYNUMBER(FXPixelBufferMap));

Magick::Color FXPixelBuffer::COLOR_TRANSPARENT("transparent");


FXPixelBuffer::FXPixelBuffer()
: objects(),
  floors(),
  owned_dc(),
  buffer(0)
{

}

FXPixelBuffer::FXPixelBuffer(MahjonggWindow *root_, FXComposite* p,FXObject* tgt,FXSelector sel,FXuint opts,FXint x,FXint y,FXint w,FXint h)
: FXCanvas( p, tgt, sel, opts, x, y, w, h ),
  objects(),
  floors(),
  owned_dc(),
  root(root_),
  buffer(0)
{

}

FXPixelBuffer::~FXPixelBuffer()
{
	for( auto dc : owned_dc ) {
		delete dc;
	}

	for( auto obj : objects ) {
		delete obj;
	}

	if( buffer ) {
		delete buffer;
		buffer = 0;
	}
}

void FXPixelBuffer::detach()
{
	if( buffer ) {
		buffer->detach();
	}
}

void FXPixelBuffer::create()
{
	FXCanvas::create();
}

void FXPixelBuffer::setTiledBackgroundImage( FXImage *image, int floor, const std::string & name )
{
	FXDC *dc = new FXDC( getApp() );
	dc->setFillStyle( FILL_TILED );
	dc->setTile( image );

	setBackground( image, dc, -1, name );
}

void FXPixelBuffer::setBackground( FXImage *img, FXDC *dc, int floor, const std::string & name )
{
	owned_dc.push_back( dc );
	objects.push_back( new FXPixelBufferBackgroundObject(this, img, dc, 0, 0, floor, name ) );

	getOrCreateFloor( floor );

    redraw_required = true;
}

FXPixelBuffer::RefMImage FXPixelBuffer::getOrCreateFloor( int floor )
{
	auto it = floors.find( floor );

	if( it != floors.end() ) {
		return it->second;
	}

	Tools::Ref<Magick::Image> mimage = new Magick::Image(Magick::Geometry(getWidth(), getHeight()), COLOR_TRANSPARENT);

	floors[floor] = mimage;

	return mimage;
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
	 unsigned long start_time_function = get_microtime();

  // FXCanvas::onPaint( obj, sel, ptr );

  // detect size change
  if( !floors.empty() ) {
	  if( floors.begin()->second->columns() != getWidth() ||
		  floors.begin()->second->rows() != getHeight() ) {
		  resize(getWidth(), getHeight());
	  }
  }


  for( auto it : floors ) {
	  RefMImage target = it.second;

	  DEBUG( format( "%s: floor %d size: %dx%d", __FUNCTION__, it.first, target->columns(), target->rows() ) );

	  target->fillColor("white");
	  target->draw( Magick::DrawableRectangle(0,0, target->columns(), target->rows() ) );
	  target->transparent("white");

	  int floor = it.first;

	  for( FXPixelBufferObject *obj : objects ) {
		  if( obj ) {
			  if( floor == obj->getFloor() ) {
				  obj->draw( target );
			  }
		  }
	  }
  }

  unsigned long start_time = get_microtime();

  std::list<Magick::Image> images;

  for( auto it : floors ) {
	  RefMImage img = it.second;
	  images.push_back( img );

	  // img->write( format( "img_%d.png", it.first ));

	  DEBUG( format( "%s: drawing floor: %d", __FUNCTION__, it.first ) );;
  }

  DEBUG( format( "%s: window size: %dx%d", __FUNCTION__, getWidth(),getHeight() ) );


  Magick::Image flattenedImage( Magick::Geometry(getWidth(),getHeight()), Magick::Color("transparent") );
  flattenedImage.type(Magick::TrueColorMatteType);

  Magick::flattenImages(&flattenedImage, images.begin(), images.end());

  flattenedImage.modifyImage();

  DEBUG( format( "duration flatten Images: %0.3fms", (get_microtime() - start_time) / 1000.0 ) );

  // flattenedImage.write("out.png");

  if( !buffer ) {
	  buffer = createImage( RefMImage(&flattenedImage,false) );
  } else {
	  updateImage( buffer, RefMImage(&flattenedImage,false) );
  }


  FXDCWindow dc(this);
  dc.drawImage( buffer, 0, 0 );

  redraw_required = false;

  DEBUG( format( "duration repainting: %0.3fms", (get_microtime() - start_time_function) / 1000.0 ) );

  return 0;
}

void FXPixelBuffer::insertObjectAt( FXPixelBufferObject *obj, int idx )
{
	if( idx == -1 ) {
		objects.push_back( obj );
		return;
	}

	if( objects.at(idx) == 0 ) {
		objects[idx] = obj;
		return;
	}

	if( objects.size() < idx ) {
		objects.resize( idx+1 );
	}

	std::vector<FXPixelBufferObject*>::iterator it;
	int i;

	for( i = 0, it = objects.begin(); i <= idx; i++, it++ ) {
		if( i == idx ) {
			objects.insert(it,obj);
			return;
		}
	}
}

FXPixelBufferObject* FXPixelBuffer::setImage( FXImage *img, int x, int y, int floor, const std::string & name, int idx )
{
	FXPixelBufferObject* obj = new FXPixelBufferObject(this, img, x, y, floor, name );

	insertObjectAt( obj, idx );

	getOrCreateFloor( floor );

    redraw_required = true;

	return obj;
}

FXPixelBufferObject* FXPixelBuffer::setImage( RefMImage img, int x, int y, int floor, const std::string & name, int idx )
{
	FXPixelBufferObject* obj = new FXPixelBufferObject(this, img, x, y, floor, name );

	insertObjectAt( obj, idx );

	getOrCreateFloor( floor );

	redraw_required = true;

	return obj;
}

FXPixelBuffer::RefMImage FXPixelBuffer::createImage( FXImage *image )
{
	if( !image->getData() ) {
		DEBUG( format("icon %s option IMAGE_KEEP not set", root->getNameByImage( image ) ) );
		image->restore();
	}

    const int w = image->getWidth();
    const int h = image->getHeight();

    RefMImage mimage = new Magick::Image(Magick::Geometry(image->getWidth(), image->getHeight()), COLOR_TRANSPARENT);

    /* get pixelcache of ImageIn */
#if MagickLibVersion >= 0x700

    mimage->type(TrueColorAlphaType);
    Quantum *pixelsOut = mimage->getPixels(0, 0, w, h);

    for (int y = 0; y != h; ++y) {
        for (int x = 0; x != w; ++x)
        {
            unsigned offset = mimage->channels() * ( w * y + x );

            FXColor xc = image->getPixel(x,y);
            ColorRGB color(FXREDVAL(xc)/255.0,
            		       FXGREENVAL(xc)/255.0,
            		       FXBLUEVAL(xc)/255.0,
            		       FXALPHAVAL(xc)/255.0 );

            pixelsOut[offset + 0] = color.quantumRed();
            pixelsOut[offset + 1] = color.quantumGreen();
            pixelsOut[offset + 2] = color.quantumBlue();
            pixelsOut[offset + 3] = color.quantumAlpha();
        }
    }
#else
    mimage->type(Magick::TrueColorMatteType);
    Magick::PixelPacket *pixelsOut = mimage->getPixels(0, 0, w, h);

#pragma omp parallel
    {
#pragma omp for
    	for (int y = 0; y < h; ++y) {
    		for (int x = 0; x < w; ++x)
    		{
    			FXColor xc = image->getPixel(x,y);
    			/*
            Magick::ColorRGB color(FXREDVAL(xc)/255.0,
            					   FXGREENVAL(xc)/255.0,
            					   FXBLUEVAL(xc)/255.0 );

            FXuint alpha = FXALPHAVAL(xc);
            // in FOX 255 is opaque 0 is transparent
            // in ImageMagick6 0 is opaque 1 is transparent
            color.alpha( 1 - alpha / 255.0 );
            // std::cout << "alpha: " << color.alpha() << " FX: " << alpha << " Green: " << (int)FXGREENVAL(xc) << std::endl;

            pixelsOut[w * y + x] = color;
    			 */

    			pixelsOut[w * y + x].red     = Magick::Color::scaleDoubleToQuantum(FXREDVAL(xc)/255.0);
    			pixelsOut[w * y + x].green   = Magick::Color::scaleDoubleToQuantum(FXGREENVAL(xc)/255.0);
    			pixelsOut[w * y + x].blue    = Magick::Color::scaleDoubleToQuantum(FXBLUEVAL(xc)/255.0);

    			FXuint alpha = FXALPHAVAL(xc);
    			pixelsOut[w * y + x].opacity = Magick::Color::scaleDoubleToQuantum( 1 - alpha / 255.0 );
    		}
    	}
    }
#endif

    mimage->syncPixels();

    return mimage;
}

FXImage *FXPixelBuffer::createImage( RefMImage mimage )
{
	const int w = mimage->columns();
    const int h = mimage->rows();

    FXImage *image = new FXImage( getApp(), 0, IMAGE_KEEP, w, h );
    image->create();

    FXColor *pixels = 0;
    allocElms( pixels, w * h  );
    image->setData( pixels, IMAGE_KEEP | IMAGE_OWNED, w, h );

    /* get pixelcache of ImageIn */
#if MagickLibVersion >= 0x700

    mimage->type(TrueColorAlphaType);
    mimage->modifyImage();

    Quantum *pixelsIn = mimage->getPixels(0, 0, w, h);

    for (int y = 0; y != h; ++y) {
        for (int x = 0; x != w; ++x)
        {
            unsigned offset = mimage->channels() * ( w * y + x );

            Color color(pixelsIn[offset + 0],pixelsIn[offset + 1] ,pixelsIn[offset + 2],pixelsIn[offset + 3]);
            ColorRBG rbg( color );

            FXColor xc = FXRGBA( rbg.red()*255.0,
            					 rbg.green()*255.0,
            					 rbg.blue()*255.0,
            					 rbg.alpha()*255.0 );
            image->setPixel( x, y, xc );
        }
    }
#else
    mimage->type(Magick::TrueColorMatteType);
    mimage->modifyImage();

    Magick::PixelPacket *pixelsIn = mimage->getPixels(0, 0, w, h);

    if( !pixelsIn ) {
    	throw REPORT_EXCEPTION( format( "pixelsIn is null size: %dx%d", w, h ) );
    }

#pragma omp parallel
    {
#pragma omp for
    	for (int y = 0; y < h; ++y) {
    		for (int x = 0; x < w; ++x)
    		{
    			/*
        	Magick::ColorRGB rbg( Magick::Color(pixelsIn[w * y + x]) );
            FXColor xc = FXRGBA( rbg.red()*255.0,
            					 rbg.green()*255.0,
            					 rbg.blue()*255.0,
            					 rbg.alpha()*255.0 );

            image->setPixel( x, y, xc );
    			 */
    			FXint blue  = Magick::Color::scaleQuantumToDouble(pixelsIn[w * y + x].blue) * 255;
    			FXint green = Magick::Color::scaleQuantumToDouble(pixelsIn[w * y + x].green) * 255;
    			FXint red   = Magick::Color::scaleQuantumToDouble(pixelsIn[w * y + x].red) * 255;
    			FXint alpha = Magick::Color::scaleQuantumToDouble(pixelsIn[w * y + x].opacity) * 255;

    			image->setPixel( x, y, FXRGBA(red,green,blue,alpha) );
    		}
    	}
    }
#endif
    image->render();

    return image;
}

FXPixelBufferObject* FXPixelBuffer::getObjectByName( const std::string & name )
{
	for( auto obj : objects ) {
		if( obj->getName() == name ) {
			return obj;
		}
	}

	return 0;
}

void FXPixelBuffer::resize( FXint width, FXint height )
{
	FXCanvas::resize(width, height);

	/* Size changed, recreate image */
	if( buffer ) {
		delete buffer;
		buffer = 0;
	}

	for( auto it : floors ) {
		RefMImage target = it.second;

		// DEBUG( format( "resize floor %d to: %dx%d", it.first, width, height ) );

		// ignore aspect ratio on resize
		Magick::Geometry newsize( width, height );
		newsize.aspect(true);
		target->resize( newsize );

		// DEBUG( format( "resized floor %d to: %dx%d", it.first, target->columns(), target->rows() ) );
	}

	// render everything new
	for( auto obj : objects ) {
		if( obj ) {
			obj->setRedrawRequired();
		}
	}

	redraw_required = true;
}

int FXPixelBuffer::remove( FXPixelBufferObject *obj )
{
	for( int i = 0; i < objects.size(); i++ ) {
		if( obj == objects[i] ) {
			objects[i] = 0;
			delete obj;
			redraw_required = true;
			return i;
		}
	}

	return -1;
}

void FXPixelBuffer::redrawIfDirty()
{
	if( redraw_required ) {
		redraw();
		return;
	}

	for( auto it = objects.begin(); it != objects.end(); it++ ) {
		if( *it ) {
			if( (*it)->redrawRequired() ) {
				redraw();
				break;
			}
		}
	}
}

void FXPixelBuffer::updateImage( FXImage *image, RefMImage mimage )
{
	const int w = mimage->columns();
    const int h = mimage->rows();

    if( image->getData() == 0 ) {
    	FXColor *pixels = 0;
    	allocElms( pixels, w * h  );
    	image->setData( pixels, IMAGE_KEEP | IMAGE_OWNED, w, h );
    }

    /* get pixelcache of ImageIn */
#if MagickLibVersion >= 0x700

    mimage->type(TrueColorAlphaType);
    mimage->modifyImage();

    Quantum *pixelsIn = mimage->getPixels(0, 0, w, h);

    for (int y = 0; y != h; ++y) {
        for (int x = 0; x != w; ++x)
        {
            unsigned offset = mimage->channels() * ( w * y + x );

            Color color(pixelsIn[offset + 0],pixelsIn[offset + 1] ,pixelsIn[offset + 2],pixelsIn[offset + 3]);
            ColorRBG rbg( color );

            FXColor xc = FXRGBA( rbg.red()*255.0,
            					 rbg.green()*255.0,
            					 rbg.blue()*255.0,
            					 rbg.alpha()*255.0 );
            image->setPixel( x, y, xc );
        }
    }
#else
    mimage->type(Magick::TrueColorMatteType);
    mimage->modifyImage();

    Magick::PixelPacket *pixelsIn = mimage->getPixels(0, 0, w, h);

    if( !pixelsIn ) {
    	throw REPORT_EXCEPTION( format( "pixelsIn is null size: %dx%d", w, h ) );
    }

    unsigned long start_time = get_microtime();

#pragma omp parallel
    {
#pragma omp for
    	for ( int y = 0; y < h; ++y ) {
    		for ( int x = 0; x < w; ++x )
    		{
    			/*
    			Magick::ColorRGB rbg( pixelsIn[w * y + x] );
    			FXColor xc = FXRGBA( rbg.red()*255.0,
    					rbg.green()*255.0,
    					rbg.blue()*255.0,
    					rbg.alpha()*255.0 );
    					image->setPixel( x, y, xc );
    			*/

    			FXint blue  = Magick::Color::scaleQuantumToDouble(pixelsIn[w * y + x].blue) * 255;
    			FXint green = Magick::Color::scaleQuantumToDouble(pixelsIn[w * y + x].green) * 255;
    			FXint red   = Magick::Color::scaleQuantumToDouble(pixelsIn[w * y + x].red) * 255;
    			FXint alpha = Magick::Color::scaleQuantumToDouble(pixelsIn[w * y + x].opacity) * 255;

    			image->setPixel( x, y, FXRGBA(red,green,blue,alpha) );
    		}
    	}
    }



    DEBUG( format( "duration converting Image to FXImage: %0.3fms", (get_microtime() - start_time) / 1000.0 ) );

#endif
    image->render();
}
