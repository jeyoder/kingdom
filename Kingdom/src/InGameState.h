/*
 * InGameState.h
 *
 *  Created on: Sep 25, 2013
 *      Author: CRHSCS115
 */

#ifndef INGAMESTATE_H_
#define INGAMESTATE_H_

#include <string>
#include <vector>
#include "SDL.h"
#include "AppState.h"
#include "TileMap.h"
namespace kingdom {
/*The state that is the game is in while actually playing.
 * Would handle low level aspects of actually running the game such as rendering, taking userimput, and some help in coordinating network communication
 * */
class InGameState: public kingdom::AppState {
public:
	InGameState(MapLoader* loader, std::string tile);
	virtual ~InGameState();
	bool render(SDL_Renderer* renderer, SDL_Window* window, double delta, const Uint8* keystates, std::vector<SDL_Event> &events);
private:
	TileMap* map;
	double tileX;
	double tileY;
	double scale;
	int mouseZoom;
	const double scrollSpeed = 0.01;
};

} /* namespace std */
#endif /* INGAMESTATE_H_ */
