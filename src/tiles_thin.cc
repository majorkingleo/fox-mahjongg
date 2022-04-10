/*
 * tiles_thin.cc
 *
 *  Created on: 24.02.2022
 *      Author: martin
 */
#include <tiles_thin.h>
#include <data_tiles_thin.h>
#include "xmj3ts.hh"
#include <iostream>

static const unsigned char *tiles_thin[] = {
	tiles_thin_00_gif,
	tiles_thin_01_gif,
	tiles_thin_02_gif,
	tiles_thin_03_gif,
	tiles_thin_04_gif,
	tiles_thin_05_gif,
	tiles_thin_06_gif,
	tiles_thin_07_gif,
	tiles_thin_08_gif,
	tiles_thin_09_gif,
	tiles_thin_10_gif,
	tiles_thin_11_gif,
	tiles_thin_12_gif,
	tiles_thin_13_gif,
	tiles_thin_14_gif,
	tiles_thin_15_gif,
	tiles_thin_16_gif,
	tiles_thin_17_gif,
	tiles_thin_18_gif,
	tiles_thin_19_gif,
	tiles_thin_20_gif,
	tiles_thin_21_gif,
	tiles_thin_22_gif,
	tiles_thin_23_gif,
	tiles_thin_24_gif,
	tiles_thin_25_gif,
	tiles_thin_26_gif,
	tiles_thin_27_gif,
	tiles_thin_28_gif,
	tiles_thin_29_gif,
	tiles_thin_30_gif,
	tiles_thin_31_gif,
	tiles_thin_32_gif,
	tiles_thin_33_gif,
	tiles_thin_34_gif,
	tiles_thin_35_gif,
	tiles_thin_36_gif,
	tiles_thin_37_gif,
	tiles_thin_38_gif,
	tiles_thin_39_gif,
	tiles_thin_40_gif,
	tiles_thin_41_gif,
	tiles_thin_42_gif,
	tiles_thin_43_gif,
	tiles_thin_44_gif,
	tiles_thin_45_gif,
	tiles_thin_46_gif,
	tiles_thin_47_gif,
	tiles_thin_48_gif,
	tiles_thin_49_gif,
	tiles_thin_50_gif
};

const char *tiles_thin_name[] = {
		"base-bamboo",
		"base-character",
		"base-dot",
		"base-dragon",
		"base-flower",
		"obscured",
		"base-season",
		"base-wind",
		"selected",
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
};

Tileset *load_tileset_thin( MahjonggWindow *root, FXPixelBuffer *pixelbuffer, double zoom_factor )
{
	Xmj3Tileset::TILE_DATA data;

	for( unsigned i = 0; i < sizeof(tiles_thin)/sizeof(tiles_thin[0]); i++ ) {
		data.push_back( Xmj3Tileset::TileDataType( tiles_thin_name[i], tiles_thin[i] ));
	}

	Xmj3Tileset *tileset = new Xmj3Tileset( root, pixelbuffer, data, zoom_factor );

    int old_border = tileset->xborder();

    const int BORDER_WIDTH = 4;
    
	tileset->xborder( BORDER_WIDTH );
	tileset->yborder(  BORDER_WIDTH );

    // restore correct width, which was calculated with the old border size
    tileset->width( tileset->width() + old_border - BORDER_WIDTH );
    tileset->height( tileset->height() + old_border - BORDER_WIDTH );

	return tileset;
}



