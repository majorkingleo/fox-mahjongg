/*
 * tiles_small.h
 *
 *  Created on: 24.03.2022
 *      Author: martin
 */

#ifndef SRC_TILES_SMALL_H_
#define SRC_TILES_SMALL_H_

#include "fx.h"
#include "tileset.hh"

class MahjonggWindow;
class FXPixelBuffer;

Tileset *load_tileset_small( MahjonggWindow *root, FXPixelBuffer *pixelbuffer, double zoom_factor );



#endif /* SRC_TILES_THICK_H_ */
