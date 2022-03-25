/*
 * tiles_small.cc
 *
 *  Created on: 24.02.2022
 *      Author: martin
 */
#include <tiles_small.h>
#include <data_tiles_gnome.h>
#include "gmjts.hh"
#include <iostream>

Tileset *load_tileset_gnome( MahjonggWindow *root, FXPixelBuffer *pixelbuffer )
{
	GnomeMjTileset *tileset = new GnomeMjTileset( root, pixelbuffer, tiles_gnome_gif, 4, 1 );

/*
    int old_border = tileset->xborder();

    const int BORDER_WIDTH = 4;
    
	tileset->xborder( BORDER_WIDTH );
	tileset->yborder(  BORDER_WIDTH );

    // restore correct width, which was calculated with the old border size
    tileset->width( tileset->width() + old_border - BORDER_WIDTH );
    tileset->height( tileset->height() + old_border - BORDER_WIDTH );
*/

	return tileset;
}



