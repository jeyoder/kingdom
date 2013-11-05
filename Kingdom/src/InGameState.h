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
#include "SDL_ttf.h"
#include "WayPoint.h"
#include "Order.h"
#include <sstream>
using namespace std;
namespace kingdom {
/*The state that is the game is in while actually playing.
 * Would handle low level aspects of actually running the game such as rendering, taking userimput, and some help in coordinating network communication
 * */
class InGameState: public kingdom::AppState {
public:
	InGameState(MapLoader* loader, std::string tile);
	virtual ~InGameState();


	enum turnState {Input, Processing, AnimatingTurn}; //tells what state turn is in. Will go something like "Input -> SyncingTurn -> AnimatingTurn -> Input -> ect."
	turnState getTurnState();
	void nextTurn();
	bool render(SDL_Renderer* renderer, SDL_Window* window, double delta, const Uint8* keystates, std::vector<SDL_Event> &events);
private:
	TileMap* map;
	double tileX; // x and y of the center of the screen, in tiles. changes with
	double tileY; // scrolling
	int turnNumber = 0;
	turnState currentTurnState;
	double timeSinceLastTurn;
	double turnLength;
	std::vector<Unit*> selectedUnits;

	bool inOrderMode = false;
	Order tempOrder;
	std::vector<WayPoint> tempOrderPath;

	std::stringstream stringMaker;
	TTF_Font *font;
	double scale; // current map scaling factor (controlled by zoomimg)
	int mouseZoom;// mouse zoom (starts at 0, number of clicks of the scroll wheel)
	const double scrollSpeed = 0.01;
};

} /* namespace std */
#endif /* INGAMESTATE_H_ */
