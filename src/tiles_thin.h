/*
 * tiles_thin.h
 *
 *  Created on: 24.02.2022
 *      Author: martin
 */

#ifndef SRC_TILES_THIN_H_
#define SRC_TILES_THIN_H_

#include "fx.h"
#include "tileset.hh"

class MahjonggWindow;
class FXPixelBuffer;

Tileset *load_tileset_thin( MahjonggWindow *root, FXPixelBuffer *pixelbuffer, double zoom_factor );



#endif /* SRC_TILES_THICK_H_ */
