/*
 * tiles_thick.cc
 *
 *  Created on: 24.02.2022
 *      Author: martin
 */
#include <tiles_thick.h>
#include <data_tiles_thick.h>
#include "xmj3ts.hh"
#include <iostream>

static const unsigned char *tiles_thick[] = {
	tiles_thick_00_gif,
	tiles_thick_01_gif,
	tiles_thick_02_gif,
	tiles_thick_03_gif,
	tiles_thick_04_gif,
	tiles_thick_05_gif,
	tiles_thick_06_gif,
	tiles_thick_07_gif,
	tiles_thick_08_gif,
	tiles_thick_09_gif,
	tiles_thick_10_gif,
	tiles_thick_11_gif,
	tiles_thick_12_gif,
	tiles_thick_13_gif,
	tiles_thick_14_gif,
	tiles_thick_15_gif,
	tiles_thick_16_gif,
	tiles_thick_17_gif,
	tiles_thick_18_gif,
	tiles_thick_19_gif,
	tiles_thick_20_gif,
	tiles_thick_21_gif,
	tiles_thick_22_gif,
	tiles_thick_23_gif,
	tiles_thick_24_gif,
	tiles_thick_25_gif,
	tiles_thick_26_gif,
	tiles_thick_27_gif,
	tiles_thick_28_gif,
	tiles_thick_29_gif,
	tiles_thick_30_gif,
	tiles_thick_31_gif,
	tiles_thick_32_gif,
	tiles_thick_33_gif,
	tiles_thick_34_gif,
	tiles_thick_35_gif,
	tiles_thick_36_gif,
	tiles_thick_37_gif,
	tiles_thick_38_gif,
	tiles_thick_39_gif,
	tiles_thick_40_gif,
	tiles_thick_41_gif,
	tiles_thick_42_gif,
	tiles_thick_43_gif,
	tiles_thick_44_gif,
	tiles_thick_45_gif,
	tiles_thick_46_gif,
	tiles_thick_47_gif,
	tiles_thick_48_gif,
	tiles_thick_49_gif,
	tiles_thick_50_gif
};

const char *tiles_thick_name[] = {
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
		"base-season",
		"base-flower",
		"base-dragon",
		"base-wind",
		"base-dot",
		"base-bamboo",
		"base-character",
		"obscured",
		"selected"
};

Tileset *load_tileset_thick( FXApp *app )
{
	Xmj3Tileset::TILE_DATA data;

	for( unsigned i = 0; i < sizeof(tiles_thick)/sizeof(tiles_thick[0]); i++ ) {
		data.push_back( Xmj3Tileset::TileDataType( tiles_thick_name[i], tiles_thick[i] ));
	}

	Xmj3Tileset *tileset = new Xmj3Tileset( app, data );

	tileset->xborder( 8 );
	tileset->yborder( 8 );

	return tileset;
}



