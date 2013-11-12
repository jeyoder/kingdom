/*
 * Pawn.cpp
 *
 *  Created on: Nov 4, 2013
 *      Author: CRHSCS115
 */

#include "Pawn.h"

namespace kingdom {

Pawn::Pawn(int PlayerNumber, int TileX, int TileY) : kingdom::Unit(PlayerNumber,TileX,TileY)  {
	// TODO Auto-generated constructor stub
	texture = ResourceLoader::getInstance()->loadTexture("assets/PawnGreen.png");
	tilesPerTurn = 2000;
	timePerTile = 100;
}
SDL_Texture* Pawn::getTexture(ResourceLoader* Loader){
		return texture;
	}
Pawn::~Pawn() {
	// TODO Auto-generated destructor stub
}

} /* namespace kingdom */
