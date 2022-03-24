/*
 * tiles_small.cc
 *
 *  Created on: 24.02.2022
 *      Author: martin
 */
#include <tiles_small.h>
#include <data_tiles_small.h>
#include "xmj3ts.hh"
#include <iostream>

static const unsigned char *tiles_small[] = {
	tiles_small_00_gif,
	tiles_small_01_gif,
	tiles_small_02_gif,
	tiles_small_03_gif,
	tiles_small_04_gif,
	tiles_small_05_gif,
	tiles_small_06_gif,
	tiles_small_07_gif,
	tiles_small_08_gif,
	tiles_small_09_gif,
	tiles_small_10_gif,
	tiles_small_11_gif,
	tiles_small_12_gif,
	tiles_small_13_gif,
	tiles_small_14_gif,
	tiles_small_15_gif,
	tiles_small_16_gif,
	tiles_small_17_gif,
	tiles_small_18_gif,
	tiles_small_19_gif,
	tiles_small_20_gif,
	tiles_small_21_gif,
	tiles_small_22_gif,
	tiles_small_23_gif,
	tiles_small_24_gif,
	tiles_small_25_gif,
	tiles_small_26_gif,
	tiles_small_27_gif,
	tiles_small_28_gif,
	tiles_small_29_gif,
	tiles_small_30_gif,
	tiles_small_31_gif,
	tiles_small_32_gif,
	tiles_small_33_gif,
	tiles_small_34_gif,
	tiles_small_35_gif,
	tiles_small_36_gif,
	tiles_small_37_gif,
	tiles_small_38_gif,
	tiles_small_39_gif,
	tiles_small_40_gif,
	tiles_small_41_gif,
	tiles_small_42_gif,
	tiles_small_43_gif,
	tiles_small_44_gif,
};

const char *tiles_small_name[] = {
		"season-1",
		"season-2",
		"season-3",
		"season-4",
		"flower-1",
		"flower-2",
		"flower-3",
		"flower-4",
		"dragon-1",
		"dragon-2",
		"dragon-3",
		"wind-1",
		"wind-2",
		"wind-3",
		"wind-4",
		"dot-1",
		"dot-2",
		"dot-3",
		"dot-4",
		"dot-5",
		"dot-6",
		"dot-7",
		"dot-8",
		"dot-9",
		"bamboo-1",
		"bamboo-2",
		"bamboo-3",
		"bamboo-4",
		"bamboo-5",
		"bamboo-6",
		"bamboo-7",
		"bamboo-8",
		"bamboo-9",
		"character-1",
		"character-2",
		"character-3",
		"character-4",
		"character-5",
		"character-6",
		"character-7",
		"character-8",
		"character-9",
		"base",
		"selected",
		"obscured",
};

Tileset *load_tileset_small( MahjonggWindow *root )
{
	Xmj3Tileset::TILE_DATA data;

	for( unsigned i = 0; i < sizeof(tiles_small)/sizeof(tiles_small[0]); i++ ) {
		data.push_back( Xmj3Tileset::TileDataType( tiles_small_name[i], tiles_small[i] ));
	}

	Xmj3Tileset *tileset = new Xmj3Tileset( root, data );

    int old_border = tileset->xborder();

    const int BORDER_WIDTH = 4;
    
	tileset->xborder( BORDER_WIDTH );
	tileset->yborder(  BORDER_WIDTH );

    // restore correct width, which was calculated with the old border size
    tileset->width( tileset->width() + old_border - BORDER_WIDTH );
    tileset->height( tileset->height() + old_border - BORDER_WIDTH );

	return tileset;
}



