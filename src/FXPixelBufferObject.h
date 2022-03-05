/*
 * FXPixelBufferObject.h
 *
 *  Created on: 02.03.2022
 *      Author: martin
 */

#ifndef SRC_FXPIXELBUFFEROBJECT_H_
#define SRC_FXPIXELBUFFEROBJECT_H_

#include "fx.h"
#include <ref.h>
#include <Magick++.h>
#include <string>

class FXPixelBuffer;

class FXPixelBufferObject
{
public:
	typedef Tools::Ref<Magick::Image> RefMImage;

protected:
	FXPixelBuffer *pixel_buffer;
	int x;
	int y;
	int floor;
	FXImage *image;
	RefMImage mimage;
	const std::string name;

public:
	FXPixelBufferObject( FXPixelBuffer *pixel_buffer_,
						 FXImage *image_,
						 int x_,
						 int y_,
						 int floor_,
						 const std::string & name_ );


	virtual ~FXPixelBufferObject();

	FXPixelBufferObject( const FXPixelBufferObject & other ) = delete;
	FXPixelBufferObject & operator=( const FXPixelBufferObject & other ) = delete;

	int getX() const { return x; }
	int getY() const { return y; }
	int getFloor() const { return floor; }
	FXImage *getImage() const { return image; }

	virtual void draw( RefMImage & target );

	const std::string & getName() const { return name; }

	void setX( int x_ ) { x = x_; }
	void setY( int y_ ) { y = y_; }

	void setDirty() { mimage = NULL; }
};

class FXPixelBufferBackgroundObject : public FXPixelBufferObject
{
	FXDC *dc;

public:
	FXPixelBufferBackgroundObject( FXPixelBuffer *pixel_buffer_,
								   FXImage *image_,
								   FXDC *dc_,
								   int x_,
								   int y_,
								   int floor_,
								   const std::string & name_ );

	virtual void draw( RefMImage & target ) override;
};



#endif /* SRC_FXPIXELBUFFEROBJECT_H_ */
