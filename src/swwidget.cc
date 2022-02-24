#include "swwidget.hh"


SwWidget::SwWidget(SwWindow *swwindow)
  : _swwindow(swwindow),

    _x(0),
    _y(0),
    _width(0),
    _height(0),

	_visible(false)
{
}

void
SwWidget::draw_subimage(FXImage *src, FXBitmap *mask, int src_x, int src_y,
			int w, int h, int x, int y)
{
  if (x < 0) {
    w += x;
    src_x -= x;
    x = 0;
  }
  if (y < 0) {
    h += y;
    src_y -= y;
    y = 0;
  }
  if (x + w > _width)
    w = _width - x;
  if (y + h > _height)
    h = _height - y;
  if (w >= 0 && h >= 0)
    _swwindow->draw_subimage(src, mask, src_x, src_y, w, h, x + _x, y + _y);
}

void
SwWidget::clear_area(int x, int y, int w, int h)
{
  if (x < 0) {
    w += x;
    x = 0;
  }
  if (y < 0) {
    h += y;
    y = 0;
  }
  if (x + w > _width)
    w = _width - x;
  if (y + h > _height)
    h = _height - y;
  if (w >= 0 && h >= 0)
    _swwindow->clear_area(x + _x, y + _y, w, h);
}

void
SwWidget::invalidate(int x, int y, int w, int h)
{
  _swwindow->invalidate(x + _x, y + _y, w, h);
}
