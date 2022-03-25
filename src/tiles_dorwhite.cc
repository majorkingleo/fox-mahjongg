/*
 * tiles_small.cc
 *
 *  Created on: 24.02.2022
 *      Author: martin
 */
#include <tiles_small.h>
#include <data_tiles_dorwhite.h>
#include "gmjts.hh"
#include <iostream>

Tileset *load_tileset_dorwhite( MahjonggWindow *root, FXPixelBuffer *pixelbuffer )
{
	GnomeMjTileset *tileset = new GnomeMjTileset( root, pixelbuffer, tiles_dorwhite_gif, 10, 0 );

	return tileset;
}



