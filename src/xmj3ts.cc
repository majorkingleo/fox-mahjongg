#include "xmj3ts.hh"
#include "tile.hh"
#include "swgeneral.hh"
#include <cstring>
#include "debug.h"
#include <format.h>
#include <cpp_util.h>
#include "main.h"

using namespace Tools;

#define NPICTURES	(Tileset::IVORY_NPICTURES)

Xmj3Tileset::Xmj3Tileset( MahjonggWindow *root, const TILE_DATA & tile_data )
  : Tileset("ivory"),
    _image_error(ieNone),

    _face_ref(),
    _base_ref(),
    _selected_ref(),
    _obscured_ref(),

    _images(),
    _masks(),
    _tile_data( tile_data ),
    _root( root )
{
  _xborder = 4;
  _yborder = 4;
  _shadow = 1;

  initialize_images();
  if (check()) {
    initialize();
  }
}

Xmj3Tileset::~Xmj3Tileset()
{
	for (int i = 0; i < _images.size(); i++) {
		if (_images[i]) {
			delete  _images[i];
		}

		if (_masks[i]) {
			delete _masks[i];
		}
	}
}


/*****
 * code to create & use the map of tile names to picture numbers
 **/

static int nsearch_pictures;
static const char **search_picture_names;
static int *search_picture_numbers;

static int
sort_picture_names(const void *v1, const void *v2)
{
  int i1 = *(int *)v1, i2 = *(int *)v2;
  return strcmp(search_picture_names[i1], search_picture_names[i2]);
}

#define RANGE_ALL	(NPICTURES + 7)

static const char *special_picture_names[] = {
  "season",	"flower",	"dragon",	"wind",
  "dot",	"bamboo",	"character",	"all"
};

static void
initialize_picture_names()
{
  if (search_picture_names) return;
  
  assert(Tileset::IVORY_NPICTURES == NPICTURES);
  int npictures = NPICTURES + 8;
  search_picture_names = new const char *[npictures];
  search_picture_numbers = new int[npictures];
  for (int i = 0; i < NPICTURES; i++) {
    search_picture_names[i] = Tileset::ivory_picture_name(i);
    search_picture_numbers[i] = i;
  }
  for (int i = 0; i < 8; i++) {
    int j = NPICTURES + i;
    search_picture_names[j] = special_picture_names[i];
    search_picture_numbers[j] = j;
  }
  
  nsearch_pictures = npictures;
  qsort(search_picture_numbers, npictures, sizeof(int), &sort_picture_names);
  
  const char **x = search_picture_names;
  search_picture_names = new const char *[npictures];
  for (int i = 0; i < npictures; i++)
    search_picture_names[i] = x[search_picture_numbers[i]];
  delete[] x;
}

static int
find_picture_name(const char *name)
{
  if (name == 0) return -1;
  int l = 0, r = nsearch_pictures - 1;
  while (l <= r) {
    int m = (l + r) / 2;
    int comparison = strcmp(name, search_picture_names[m]);
    if (comparison < 0)
      r = m - 1;
    else if (comparison > 0)
      l = m + 1;
    else
      return search_picture_numbers[m];
  }
  return -1;
}

/******/

void
Xmj3Tileset::map_one_image(const char *name_rest, int image_index,
			   ImageType which, Vector<short> &genericity)
{
  if (*name_rest == '-' || *name_rest == ' ' || *name_rest == '.')
    name_rest++;
  
  int range;
  if (*name_rest == 0)
    range = RANGE_ALL;
  else
    range = find_picture_name(name_rest);
  if (range < 0)
    return;
  
  int left, right;
  switch (range) {
   case NPICTURES: /* seasons  */	left = 0; right = 3; break;
   case NPICTURES+1: /* flowers */	left = 4; right = 7; break;
   case NPICTURES+2: /* dragons */	left = 8; right = 10; break;
   case NPICTURES+3: /* winds */	left = 11; right = 14; break;
   case NPICTURES+4: /* dots */		left = 15; right = 23; break;
   case NPICTURES+5: /* bamboos */	left = 24; right = 32; break;
   case NPICTURES+6: /* characters */	left = 33; right = 41; break;
   case RANGE_ALL:			left = 0; right = 41; break;
   default:				left = right = range; break;
  }
  
  Vector<short> *references = 0;
  if (which == itFace)
    references = &_face_ref;
  else if (which == itBase)
    references = &_base_ref;
  else if (which == itSelected)
    references = &_selected_ref;
  else if (which == itObscured)
    references = &_obscured_ref;
  
  short new_genericity = right - left;
  genericity[image_index] = new_genericity;
  
  for (int i = left; i <= right; i++) {
    short old_image = (*references)[i];
    if (old_image == -1 || genericity[old_image] > new_genericity)
      (*references)[i] = image_index;
  }
}

void
Xmj3Tileset::initialize_images()
{
  initialize_picture_names();
  _base_ref.assign(NPICTURES, -1);
  _selected_ref.assign(NPICTURES, -1);
  _obscured_ref.assign(NPICTURES, -1);
  _face_ref.assign(NPICTURES, -1);
  
  Vector<short> genericity( _tile_data.size(), NPICTURES + 1);
  
  for (int imagei = 0; imagei < _tile_data.size(); imagei++) {

    std::string name = _tile_data[imagei].name;

    FXImage *image = new FXGIFIcon( _root->getApp(), 0, 0, IMAGE_ALPHAGUESS | IMAGE_KEEP );
    FXMemoryStream ms(FXStreamLoad,(FXuchar*)_tile_data[imagei].data);
    if( !image->loadPixels(ms) ) {
    	throw REPORT_EXCEPTION( format("Cannot load image %d", _tile_data[imagei].name) );
    }
    image->create();
    _images.push_back(image);

    DEBUG( format( "creating image %02d => %s %p size: %dx%d",
    	  imagei,
    	  name,
    	  _images.at(imagei),
    	  image->getWidth(),
    	  image->getHeight()));

    _masks.push_back( _root->createBitmapMaskFromImage( image ) );

    if (strncmp(name.c_str(), "base", 4) == 0)
      map_one_image(name.c_str() + 4, imagei, itBase, genericity);
    else if (strncmp(name.c_str(), "selected", 8) == 0)
      map_one_image(name.c_str() + 8, imagei, itSelected, genericity);
    else if (strncmp(name.c_str(), "obscured", 8) == 0)
      map_one_image(name.c_str() + 8, imagei, itObscured, genericity);
    else
      map_one_image(name.c_str(), imagei, itFace, genericity);
  }
  
  
  check_images();
}

void
Xmj3Tileset::check_images()
{
  _image_error = ieNone;
  
  // All four kinds of image must exist for every tile
  for (int i = 0; i < NPICTURES; i++)
    if (_base_ref[i] < 0 || _selected_ref[i] < 0 || _obscured_ref[i] < 0) {
      _image_error = ieNoBase;
      DEBUG( "invalid entry ieNoBase" );
      return;
    }
  
  // Check the sizes of all the images
  // Assume it's broken.
  _image_error = ieBadSize;
  FXImage *img = _images.at(_obscured_ref[0]);
  int w = img->getWidth();
  int h = img->getHeight();
  for (int i = 0; i < NPICTURES; i++) {
    FXImage *img2 = _images.at(_base_ref[i]);
    if (img2->getWidth() != w || img2->getHeight() != h) {
      return;
    }

    img2 = _images.at(_selected_ref[i]);
    if (img2->getWidth() != w || img2->getHeight() != h) {
      return;
    }

    img2 = _images.at(_obscured_ref[i]);
    if (img2->getWidth() != w || img2->getHeight() != h) {
      return;
    }

    img2 = _images.at(_face_ref[i]);
    if (img2->getWidth() > w || img2->getHeight() > h)
      return;
  }
  
  // If we get here, all is hunky-dory!
  _image_error = ieNone;
}

bool
Xmj3Tileset::check() const
{
  // OK
  return true;
}

void
Xmj3Tileset::initialize()
{
  FXImage *image = _images.at(_base_ref[0]);
  _width = image->getWidth() - _xborder;
  _height = image->getHeight() - _yborder;

  DEBUG( format( "image %d has size: %dx%d", _base_ref[0], _width, _height ) );
}

void
Xmj3Tileset::draw(SwDrawable *drawable, short x, short y, short base,
		  short face)
{
  if (base >= 0) {

    drawable->draw_image(_images.at(base), _masks.at(base),
			 _width + _xborder, _height + _yborder, x, y);
  }
  
  if (face >= 0) {
    
    int dx = (_shadow & 1 ? _xborder : 0);
    int dy = (_shadow & 2 ? _yborder : 0);

    FXImage *img = _images.at(face);

    drawable->draw_image( img, _masks[face],
    		img->getWidth(), img->getHeight(), x + dx, y + dy);
  }
}

void
Xmj3Tileset::draw_normal(const Tile *t, SwDrawable *drawable, short x, short y)
{
  int which = picture(t->number());
  assert(which >= 0 && which < NPICTURES);
  draw(drawable, x, y, _base_ref[which], _face_ref[which]);
}

void
Xmj3Tileset::draw_lit(const Tile *t, SwDrawable *drawable, short x, short y)
{
  int which = picture(t->number());
  assert(which >= 0 && which < NPICTURES);
  draw(drawable, x, y, _selected_ref[which], _face_ref[which]);
}

void
Xmj3Tileset::draw_obscured(const Tile *t, SwDrawable *drawable,
			   short x, short y)
{
  int which = picture(t->number());
  assert(which >= 0 && which < NPICTURES);
  draw(drawable, x, y, _obscured_ref[which], -1);
}

