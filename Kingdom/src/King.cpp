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
namespace kingdom {

	King::King(int PlayerNumber, int TileX, int TileY) : kingdom::Unit(PlayerNumber,TileX,TileY)  {
		// TODO Auto-generated constructor stub

	}
	SDL_Texture* King::getTexture(ResourceLoader* Loader){
		return Loader->loadTexture("assets/KingGreen.png");
	}

	King::~King() {
		// TODO Auto-generated destructor stub
	}
	/*void render(SDL_Renderer* Renderer,SDL_Window* Window){

	}*/

} /* namespace kingdom */
