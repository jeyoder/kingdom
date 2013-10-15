/*



 * InGameState.cpp
 *
 *  Created on: Sep 25, 2013
 *      Author: CRHSCS115
 */

#include "InGameState.h"
#include "AppState.h"
#include <iostream>
#include <cmath>
/*The state that is the game is in while actually playing.
 * Would handle low level aspects of actually running the game such as rendering, taking userimput, and some help in coordinating network communication
 * */
using namespace std;
namespace kingdom {

InGameState::InGameState(MapLoader* loader, std::string tileset) {
	SDL_Texture* tileTexture = ResourceLoader::getInstance()->loadTexture(tileset);
	this->map = new TileMap(loader,tileTexture);
	this->tileX = 50;
	this->tileY = 50;
	this->scale = 1.0;
	this->mouseZoom = 0;
}
bool InGameState::render(SDL_Renderer* renderer, SDL_Window* window, double delta, const Uint8* keystates, vector<SDL_Event> &events){
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
	for(SDL_Event e : events) {
		if(e.type == SDL_MOUSEWHEEL) {
			cout << "z: " << scale << endl;
			mouseZoom += e.wheel.y;
			scale = pow(2, (mouseZoom + 1) * 0.15);
		}
	}
	map->draw(renderer, window, tileX, tileY, scale);
	return true; //succesful render
}
InGameState::~InGameState() {
	delete map;
}

} /* namespace std */
