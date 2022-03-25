/*
 * tiles_small.cc
 *
 *  Created on: 24.02.2022
 *      Author: martin
 */
#include <tiles_dorothys.h>
#include <data_tiles_dorothys.h>
#include "gmjts.hh"
#include <iostream>

Tileset *load_tileset_dorothys( MahjonggWindow *root, FXPixelBuffer *pixelbuffer )
{
	GnomeMjTileset *tileset = new GnomeMjTileset( root, pixelbuffer, tiles_dorothys_gif, 10, 0 );

	return tileset;
}



