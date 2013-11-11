/*
 * King.cpp
 *
 *  Created on: Sep 30, 2013
 *      Author: CRHSCS115
 */

#include "King.h"
#include "Unit.h"
#include "SDL.h"
#include "ResourceLoader.h"
#include "Game.h"
namespace kingdom {

	King::King(int PlayerNumber, int TileX, int TileY) : kingdom::Unit(PlayerNumber,TileX,TileY)  {
		texture = ResourceLoader::getInstance()->loadTexture("assets/KingGreen.png");
		tilesPerTurn = 1;
	}
	SDL_Texture* King::getTexture(ResourceLoader* Loader){
		return texture;
	}

	King::~King() {
		// TODO Auto-generated destructor stub
	}
	/*void render(SDL_Renderer* Renderer,SDL_Window* Window){

	}*/

} /* namespace kingdom */
