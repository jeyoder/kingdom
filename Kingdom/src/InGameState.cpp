/*



 * InGameState.cpp
 *
 *  Created on: Sep 25, 2013
 *      Author: CRHSCS115
 */

#include "InGameState.h"
#include "AppState.h"
#include "Game.h"
#include "Order.h"
#include <string>
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "time.h"
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
//#include <ctime>
#include <vector>
#include <iostream>
#include <cmath>

/*The state that is the game is in while actually playing.
 * Would handle low level aspects of actually running the game such as rendering, taking userimput, and some help in coordinating network communication
 * */
using namespace std;
namespace kingdom {
using namespace std;

InGameState::InGameState(MapLoader* loader, std::string tileset) {
	SDL_Texture* tileTexture = ResourceLoader::getInstance()->loadTexture(tileset);
	this->map = new TileMap(loader,tileTexture);
	this->tileX = 50;
	this->tileY = 50;

	this->currentTurnState = Input;
	this->turnNumber = 0;
	this->turnLength = 5; //5 second turn time
	// Load a font
   font = TTF_OpenFont("assets/fonts/FreeMono.ttf", 16);
   if (font == NULL)
   {
	  cerr << "TTF_OpenFont() Failed: " << TTF_GetError() << endl;
	  TTF_Quit();
	  SDL_Quit();
	  exit(1);
   }

  // time(&lastTurnTime); //set last time
   	timeSinceLastTurn = 0;
	this->scale = 1.0;
	this->mouseZoom = 0;
	turnLength = 5000;
	inOrderMode = false;
}

//bool InGameState::render(SDL_Renderer* renderer, SDL_Window* window, double delta, const Uint8* keystates){
	//Check Game Stuff
	//time_t now;
	//time(&now);

	//double elapseTime = difftime(now,now);
	//cout << elapseTime;
	/*printf( "\nProgram takes %6.0f seconds.\n", elapseTime);
	if(elapseTime >= turnLength){
		nextTurn();
		time(&lastTurnTime); //store new time
	}*/

bool InGameState::render(SDL_Renderer* renderer, SDL_Window* window, double delta, const Uint8* keystates, vector<SDL_Event> &events){
	//Game Logic
	switch (currentTurnState){
		case Input:
			timeSinceLastTurn += delta;
			if(timeSinceLastTurn >= turnLength){
				nextTurn();
				timeSinceLastTurn = timeSinceLastTurn - turnLength;
			}
			break;
		case Animating:
			bool StillAnimating = false;
			std::vector<Unit*> unitList = this->map->getUnitsList();
			for(unsigned int i = 0; i < unitList.size(); i++){
				if(unitList.at(i)->getUnitTurnState() == Unit::Animating){
					StillAnimating = true; //if someone is still animating we have to stay in the animating state
					unitList.at(i)->moveAnimate(delta);
				}
			}
			if(!StillAnimating){
				this->currentTurnState = Input;
			}
			break;
	}


	//

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
	//Render map
	for(SDL_Event e : events) { //iterate through vector of events we received
		if(e.type == SDL_MOUSEWHEEL) {
			cout << "z: " << scale << endl;
			mouseZoom += e.wheel.y;
			scale = pow(2, (mouseZoom + 1) * 0.15); //scale the mouse for a nice linear zoom
			scale = floor(scale * map->tileW) / map->tileW; //round scale to the nearest tile width multiple. prevents tile gaps.
		} else if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP || e.type == SDL_MOUSEMOTION) {
			int windowW;
			int windowH;
			int mouseX, mouseY;
			unsigned int mouseButtons;
			SDL_GetWindowSize(window, &windowW, &windowH);
			mouseButtons = SDL_GetMouseState(&mouseX, &mouseY);
			int clickX = (tileX * map->tileW * scale) - (windowW / 2) + mouseX; //tile location in pixels
			int clickY = (tileY * map->tileH * scale) - (windowH / 2) + mouseY;
			int clickedTileX = clickX / (map->tileW * scale); //convert to tiles
			int clickedTileY = clickY / (map->tileH * scale);
			if(e.button.button == SDL_BUTTON_LEFT && e.type == SDL_MOUSEBUTTONUP) { //on lmb release
				Unit* clickedUnit = map->unitAt(clickedTileX, clickedTileY);
				selectedUnits.clear();
				inOrderMode = false;
				if (clickedUnit) {
					selectedUnits.push_back(clickedUnit);
				} else {
					cout << "No clicky unit..." << endl;
				}
			} else if (e.button.button == SDL_BUTTON_RIGHT && selectedUnits.size() > 0 && e.type == SDL_MOUSEBUTTONDOWN) { //right click start, start an order, show the waypoint chooser
				if(clickedTileX >= 0 && clickedTileX <= map->getW() && clickedTileY >= 0 && clickedTileY <= map->getH()) { //if the click was actually on the map
					inOrderMode = true;
					vector<WayPoint> orderPoints = {WayPoint(clickedTileX, clickedTileY)};
					tempOrder = Order(orderPoints, 1, map);
					tempOrderPath = tempOrder.getPath(selectedUnits.front()->getPosition());
				}
			} else if (e.button.button == SDL_BUTTON_RIGHT && selectedUnits.size() > 0 && e.type == SDL_MOUSEBUTTONUP) { //right click end, dispatch the order and clear the waypoint chooser
				inOrderMode = false;
				if(clickedTileX >= 0 && clickedTileX <= map->getW() && clickedTileY >= 0 && clickedTileY <= map->getH()) { //if click is inside tha map
					vector<WayPoint> orderPoints = {WayPoint(clickedTileX, clickedTileY)};
					tempOrder = Order(orderPoints, 1, map);
					tempOrderPath = tempOrder.getPath(selectedUnits.front()->getPosition());
				}
				cout << "Dispatch Order" << endl;
				Order* ptr = new Order(tempOrder);
				selectedUnits.front()->giveOrder(ptr);
			} else if (e.type == SDL_MOUSEMOTION) { //on mouse move
				if((mouseButtons & SDL_BUTTON_RMASK) && inOrderMode) { //if the  rmb is down and a unit is receiving orders
					vector<WayPoint> orderPoints = {WayPoint(clickedTileX, clickedTileY)};
					tempOrder = Order(orderPoints, 1, map);
					tempOrderPath = tempOrder.getPath(selectedUnits.front()->getPosition());

				}
			}
		}
	}
	if(inOrderMode) {
		vector<WayPoint> orderPoints = tempOrder.getWayPoints();
		map->draw(renderer, window, tileX, tileY, scale, selectedUnits, orderPoints, tempOrderPath);

	} else {
		vector<WayPoint> empty;
		map->draw(renderer, window, tileX, tileY, scale, selectedUnits, empty, empty);
	}
	//Render UI
	// Write text to surface
	std::stringstream turnText;
	if(this->currentTurnState == Input){
		turnText << "Turn: " << turnNumber << " (" << ceil((turnLength-timeSinceLastTurn)/1000) << ")";
	}
	else{
		turnText << "Taking Turn...";
	}
	SDL_Color text_color = {255, 255, 255};
	int windowW;
	int windowH;
	SDL_GetWindowSize(window, &windowW, &windowH);
	Game::renderText(turnText.str(),font, text_color, windowW - 120, 10, renderer);

	cout.flush();
	return true; //succesful render
}
InGameState::turnState InGameState::getTurnState(){
	return this->currentTurnState;
}
void InGameState::nextTurn(){
	turnNumber++;
	this->currentTurnState = Processing;
	cout << "Starting Turn " << turnNumber <<endl;
	//Tell all the units to take their turn
	std::vector<Unit*> unitList = this->map->getUnitsList();
	for(Unit* unit : unitList){
		unit->nextUnitTurn();
	}
	//Change turn state
	this->currentTurnState = Animating; //Will remain in animated state until all units report their state to input
}
InGameState::~InGameState() {
	delete map;
}

} /* namespace std */
