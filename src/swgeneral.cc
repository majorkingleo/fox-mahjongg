#include "swgeneral.hh"
#include <cstdio>
#include "debug.h"
#include <format.h>
#include "main.h"

using namespace Tools;

SwDrawable::~SwDrawable()
{
}

void
SwDrawable::clear_area(int, int, int, int)
{
}

void
SwDrawable::invalidate(int, int, int, int)
{
}

//

SwWindow::SwWindow(FXApp *display, FXWindow *window, MahjonggWindow *root )
  : _display(display),
    _window(window),
    _root( root )
{
}

SwWindow::~SwWindow()
{
}

void
SwWindow::draw_subimage(FXImage *source, FXBitmap *mask,
			int src_x, int src_y, int width, int height,
			int x, int y)
{
  if (source && width > 0 && height > 0) {
      FXDCWindow image_gc(window());
      /*      
      if (mask) {          
          // XSetClipMask(_display, image_gc, mask);
          image_gc.setClipMask( mask );
          
          // TODO ?
          // XSetClipOrigin(_display, image_gc, x - src_x, y - src_y);
      }  else {      
          image_gc.setClipRectangle( x, y, width, height );
          }*/
      

      FXIcon *icon = dynamic_cast<FXIcon*>( source );

      if( icon != 0 ) {
          DEBUG( format("drawing icon transparent color: 0x%X OPAQUE: %d ALPHAGUESS: %d",
                        icon->getTransparentColor(),
                        icon->getOptions() & IMAGE_OPAQUE,
                        icon->getOptions() & IMAGE_ALPHAGUESS));
          image_gc.drawIcon( icon, x, y);
          // _root->setCurrentImage( icon );
      } else {
          DEBUG( "drawing image" );
          image_gc.drawImage( source, x, y);
          // _root->setCurrentImage( source );
      }
      
	  // image_gc->clearClipRectangle();
      // XCopyArea(_display, source, _window, image_gc, src_x, src_y,
      //      width, height, x, y);
  }
}

void
SwWindow::clear_area(int x, int y, int width, int height)
{
  if (width > 0 && height > 0) {
   // XClearArea(_display, _window, x, y, width, height, False);
  }
}

//

SwClippedWindow::SwClippedWindow(FXApp *app, FXWindow *window, MahjonggWindow *root )
  : SwWindow(app, window, root ),
    _clipping(false),
    _clip_left(0),
    _clip_top(0),
    _clip_right(0),
    _clip_bottom(0)
{
}

void
SwClippedWindow::intersect_clip(int left, int top, int w, int h)
{
  int right = left + w;
  int bottom = top + h;
  if (_clipping) {
    if (left < _clip_left) left = _clip_left;
    if (right > _clip_right) right = _clip_right;
    if (top < _clip_top) top = _clip_top;
    if (bottom > _clip_bottom) bottom = _clip_bottom;
  }
  _clip_left = left;
  _clip_right = right;
  _clip_top = top;
  _clip_bottom = bottom;
  _clipping = true;
}

void
SwClippedWindow::union_clip(int left, int top, int w, int h)
{
  int right = left + w;
  int bottom = top + h;
  if (_clipping) {
    if (left > _clip_left) left = _clip_left;
    if (right < _clip_right) right = _clip_right;
    if (top > _clip_top) top = _clip_top;
    if (bottom < _clip_bottom) bottom = _clip_bottom;
  }
  _clip_left = left;
  _clip_right = right;
  _clip_top = top;
  _clip_bottom = bottom;
  _clipping = true;
}

void
SwClippedWindow::do_clip(int &x, int &y, int &width, int &height) const
{
  if (_clipping) {
    if (x + width > _clip_right)
      width = _clip_right - x;
    if (y + height > _clip_bottom)
      height = _clip_bottom - y;
    if (x < _clip_left) {
      width -= _clip_left - x;
      x = _clip_left;
    }
    if (y < _clip_top) {
      height -= _clip_top - y;
      y = _clip_top;
    }
  }
}

void
SwClippedWindow::draw_subimage(FXImage *source, FXBitmap *mask,
		       int src_x, int src_y, int width, int height,
		       int x, int y)
{
  short old_x = x, old_y = y;
  do_clip(x, y, width, height);
  if (width > 0 && height > 0) {
      //	DEBUG( "draw_subimage" );
    SwWindow::draw_subimage(source, mask, src_x + x - old_x, src_y + y - old_y,
			    width, height, x, y);
  } else {
	  DEBUG( format("not drawing subimage: width: %d height: %d", width, height ) );
  }
}

void
SwClippedWindow::clear_area(int x, int y, int width, int height)
{
  do_clip(x, y, width, height);
  SwWindow::clear_area(x, y, width, height);
}

void
SwClippedWindow::invalidate(int x, int y, int width, int height)
{
  do_clip(x, y, width, height);
  SwWindow::invalidate(x, y, width, height);
}

//

SwImage::~SwImage()
{
  delete _source;
  delete _mask;
}

void
SwImage::draw(SwDrawable *drawable, int x, int y)
{
  if (_source)
    drawable->draw_subimage(_source, _mask, 0, 0, _width, _height, x, y);
}

#if 0
SwGifImage::SwGifImage(Gif_Stream *gfs, int image_number)
: _gfs(0),
  _gfi(0),
  _made(false)
{
  initialize(gfs, Gif_GetImage(gfs, image_number));
}

SwGifImage::~SwGifImage()
{
  if (_gfi) {
    _gfi->refcount--;
    if (!_gfi->refcount) Gif_DeleteImage(_gfi);
  }
  _gfs->refcount--;
  if (!_gfs->refcount) Gif_DeleteStream(_gfs);
}

void
SwGifImage::initialize(Gif_Stream *gfs, Gif_Image *gfi)
{
  _gfs = gfs;
  _gfi = gfi;
  _gfs->refcount++;
  if (_gfi) _gfi->refcount++;
}

void
SwGifImage::create_pixmaps(SwDrawable *drawable)
{
  if (!_gfi) return;
  Gif_XContext *gifx = drawable->get_gif_x_context();
  Pixmap source = Gif_XImage(gifx, _gfs, _gfi);
  Pixmap mask = None;
  if (_gfi->transparent >= 0)
    mask = Gif_XMask(gifx, _gfs, _gfi);
  set_image(gifx->display, source, mask, _gfi->width, _gfi->height);
  _made = true;
}

void
SwGifImage::draw(SwDrawable *drawable, int x, int y)
{
  if (!_made)
    create_pixmaps(drawable);
  if (_source)
    drawable->draw_subimage(_source, _mask, 0, 0, _width, _height, x, y);
}

#endif

