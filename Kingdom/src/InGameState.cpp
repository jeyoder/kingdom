/*



 * InGameState.cpp
 *
 *  Created on: Sep 25, 2013
 *      Author: CRHSCS115
 */

#include "InGameState.h"
#include "AppState.h"
/*The state that is the game is in while actually playing.
 * Would handle low level aspects of actually running the game such as rendering, taking userimput, and some help in coordinating network communication
 * */
namespace kingdom {

InGameState::InGameState(TileMap* map) {
	this->map = map;
	this->tileX = 50;
	this->tileY = 50;
}
bool InGameState::render(SDL_Renderer* renderer, SDL_Window* window, double delta, const Uint8* keystates){
	double scrollAmt = delta * scrollSpeed;
	if(keystates[SDL_SCANCODE_A]) {
		tileX -= scrollAmt;
	}
	if(keystates[SDL_SCANCODE_D]) {
		tileX += scrollAmt;
	}
	if(keystates[SDL_SCANCODE_W]) {
		tileY -= scrollAmt;
	}
	if(keystates[SDL_SCANCODE_S]) {
		tileY += scrollAmt;
	}
	map->draw(renderer, window, tileX, tileY);
	return true; //succesful render
}
InGameState::~InGameState() {
	delete map;
}

} /* namespace std */
