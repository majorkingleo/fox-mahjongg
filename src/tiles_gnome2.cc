/*
 * tiles_small.cc
 *
 *  Created on: 24.02.2022
 *      Author: martin
 */
#include <tiles_gnome2.h>
#include <data_tiles_gnome2.h>
#include "gmjts.hh"
#include <iostream>

Tileset *load_tileset_gnome2( MahjonggWindow *root, FXPixelBuffer *pixelbuffer )
{
	GnomeMjTileset *tileset = new GnomeMjTileset( root, pixelbuffer, tiles_gnome2_gif, 4, 1 );

	return tileset;
}



