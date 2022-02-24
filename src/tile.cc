#include "tile.hh"


Tile::Tile()
  : _real(false),
    _mark_val(0),

    _number(0),
    _match(0),
    _row(0),
    _col(0),
    _lev(0),

    _coverage(0),
    _blocked(0)
{
}


Tile::Tile(short r, short c, short l)
  : _real(true),
    _mark_val(0),

    _number(0),
    _match(0),
    _row(r),
    _col(c),
    _lev(l),

    _coverage(0),
    _blocked(0)
{
}
