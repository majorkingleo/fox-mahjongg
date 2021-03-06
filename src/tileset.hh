#ifndef TILESET_HH
#define TILESET_HH
#include <liblcdf/vector.hh>
class Tile;
class SwDrawable;

class Tileset {
 protected:
  
  int _xborder;
  int _yborder;
  int _shadow;
  int _width;
  int _height;
  
  int _ntiles;
  int _npictures;
  int _nmatches;
  Vector<short> _pictures;
  Vector<short> _matches;
  
  void initialize_ivory();
  
 public:

  enum Shadow {
    shadowNW = 0, shadowNE = 1, shadowSW = 2, shadowSE = 3
  };
  
  Tileset(short ntiles, short npictures, short nmatches);
  Tileset(const char *);		// set up by name, e.g. "ivory"
  virtual ~Tileset()			{ }
  
  Tileset( const Tileset & other ) = delete;
  Tileset & operator=( const Tileset & other ) = delete;

  virtual bool ok() const = 0;
  
  void xborder( int xborder )   { _xborder = xborder; }
  int xborder() const			{ return _xborder; }

  void yborder( int yborder )   { _yborder = yborder; }
  int yborder() const			{ return _yborder; }

  void shadow( int shadow ) 	{ _shadow = shadow; }
  int shadow() const			{ return _shadow; }

  void width( int width )       { _width = width; }  
  int width() const			    { return _width; }

  void height( int height )     { _height = height; };
  int height() const			{ return _height; }
  
  int ntiles() const			{ return _ntiles; }
  int npictures() const			{ return _npictures; }
  int nmatches() const			{ return _nmatches; }
  
  short picture(short tile) const	{ return _pictures[tile]; }
  short match(short tile) const		{ return _matches[tile]; }
  
  virtual void draw_normal(const Tile *, SwDrawable *, short x, short y) = 0;
  virtual void draw_lit(const Tile *, SwDrawable *, short x, short y) = 0;
  virtual void draw_obscured(const Tile *, SwDrawable *, short x, short y) = 0;
  virtual void erase( const Tile * tile, SwDrawable *drawable ) = 0;

  // Information about the normal tileset, called `ivory'.
  static const char *ivory_picture_name(int);
  static const int IVORY_NTILES = 144;
  static const int IVORY_NPICTURES = 42;
  static const int IVORY_NMATCHES = 36;
  
};

/* Requirement:
   If x % 2 == 0 && x >= 0 && x < ntiles(), then match(x) == match(x + 1). */

#endif
