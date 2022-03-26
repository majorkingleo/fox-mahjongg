/*
 * tiles_small.cc
 *
 *  Created on: 24.02.2022
 *      Author: martin
 */
#include <tiles_gnome.h>
#include <data_tiles_real.h>
#include "kmjts.hh"
#include <iostream>

Tileset *load_tileset_real( MahjonggWindow *root, FXPixelBuffer *pixelbuffer )
{
	KyodaiTileset *tileset = new KyodaiTileset( root,
												pixelbuffer,
												tiles_real_gif,
												tiles_real_background_gif,
												8,
												1 );

	return tileset;
}



