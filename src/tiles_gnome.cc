/*
 * tiles_small.cc
 *
 *  Created on: 24.02.2022
 *      Author: martin
 */
#include <tiles_gnome.h>
#include <data_tiles_gnome.h>
#include "gmjts.hh"
#include <iostream>

Tileset *load_tileset_gnome( MahjonggWindow *root, FXPixelBuffer *pixelbuffer, double zoom_factor )
{
	GnomeMjTileset *tileset = new GnomeMjTileset( root, pixelbuffer, tiles_gnome_gif, 4, 1, zoom_factor );

	return tileset;
}



