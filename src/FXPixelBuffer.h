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
#include <Magick++.h>
#include <ref.h>
#include "FXPixelBufferObject.h"

class MahjonggWindow;

class FXPixelBuffer : public FXCanvas
{
public:
	typedef Tools::Ref<Magick::Image> RefMImage;

protected:
	FXDECLARE(FXPixelBuffer)
protected:
	FXPixelBuffer();
private:
	FXPixelBuffer(const FXPixelBuffer&);
	FXPixelBuffer &operator=(const FXPixelBuffer&);

	static Magick::Color COLOR_TRANSPARENT;



	std::vector<FXPixelBufferObject*> 	objects;
	std::map<int,RefMImage>				floors;
	std::vector<FXDC*>			 		owned_dc;
	MahjonggWindow 				 		*root;
	bool 								redraw_required;

public:
	long onPaint(FXObject*,FXSelector,void*);

	/// Construct new drawing canvas widget
	FXPixelBuffer(MahjonggWindow *root, FXComposite* p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=FRAME_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0);
	~FXPixelBuffer();

	void detach();
	void create();

	FXPixelBufferObject* setImage( FXImage *img, int x, int y, int floor, const std::string & name = "" );
	FXPixelBufferObject* setImage( RefMImage img, int x, int y, int floor, const std::string & name = "" );
	void setBackground( FXImage *img, FXDC *dc = NULL, int floor = -1, const std::string & name = "" );
	void setTiledBackgroundImage( FXImage *image, int floor = -1, const std::string & name = "" );

	int getLowestFloor() const;
	int getHighestFloor() const;

	RefMImage getOrCreateFloor( int floor );

	FXPixelBufferObject* getObjectByName( const std::string & name );

	void redraw() {
		onPaint( 0, 0, 0 );
	}

	void resize( FXint width, FXint height ) override;

	void remove( FXPixelBufferObject *obj );

	void redrawIfDirty();

public:
	RefMImage createImage( FXImage *image );
	FXImage *createImage( RefMImage mimage );

};



#endif /* SRC_FXPIXELBUFFER_H_ */
