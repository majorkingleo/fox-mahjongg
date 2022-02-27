/*
 * FXPixelBuffer.h
 *
 *  Created on: 27.02.2022
 *      Author: martin
 */

#ifndef SRC_FXPIXELBUFFER_H_
#define SRC_FXPIXELBUFFER_H_

#include "fx.h"

#include <vector>
#include <map>

class FXPixelBuffer : public FXCanvas
{
	FXDECLARE(FXPixelBuffer)
protected:
	FXPixelBuffer();
private:
	FXPixelBuffer(const FXPixelBuffer&);
	FXPixelBuffer &operator=(const FXPixelBuffer&);

	class ObjectContainer
	{
	protected:
		int x;
		int y;
		int floor;
		FXImage *image;

	public:
		ObjectContainer( FXImage *image_, int x_, int y_, int floor_ )
		: x( x_ ),
		  y( y_ ),
		  floor( floor_ ),
		  image( image_ )
		{}

		virtual ~ObjectContainer() {}

		ObjectContainer( const ObjectContainer & other ) = delete;
		ObjectContainer & operator=( const ObjectContainer & other ) = delete;

		int getX() const { return x; }
		int getY() const { return y; }
		int getFloor() const { return floor; }
		FXImage *getImage() const { return image; }

		virtual void draw( FXImage *target );
	};

	class BackgroundObjectContainer : public ObjectContainer
	{
		FXDC *dc;

	public:
		BackgroundObjectContainer( FXImage *image_, FXDC *dc_, int x_, int y_, int floor_ )
		: ObjectContainer( image_, x_, y_, floor_ ),
		  dc( dc_ )
		{}

		virtual void draw( FXImage *target ) override;
	};

	std::vector<ObjectContainer*> objects;
	std::map<int,FXImage*> 		 floors;
	std::vector<FXDC*>			 owned_dc;
	std::vector<FXImage*>		 owned_images;

public:
	long onPaint(FXObject*,FXSelector,void*);

	/// Construct new drawing canvas widget
	FXPixelBuffer(FXComposite* p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=FRAME_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0);
	~FXPixelBuffer();

	void detach();
	void create();

	void setBackground( FXImage *img, FXDC *dc = NULL, int floor = -1 );
	void setTiledBackgroundImage( FXImage *image );

	int getLowestFloor() const;
	int getHighestFloor() const;

	FXImage *getOrCreateFloor( int floor );
};



#endif /* SRC_FXPIXELBUFFER_H_ */
