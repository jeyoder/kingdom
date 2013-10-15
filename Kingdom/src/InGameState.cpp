/*



 * InGameState.cpp
 *
 *  Created on: Sep 25, 2013
 *      Author: CRHSCS115
 */

#include "InGameState.h"
#include "AppState.h"

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
	timeSinceLastTurn += delta;
	//std::cout << turnLength;
	//cout.flush();
	//if(timeSinceLastTurn >= turnLength){
		//nextTurn();
		//timeSinceLastTurn = timeSinceLastTurn - turnLength;
	//}
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
	for(SDL_Event e : events) {
		if(e.type == SDL_MOUSEWHEEL) {
			cout << "z: " << scale << endl;
			mouseZoom += e.wheel.y;
			scale = pow(2, (mouseZoom + 1) * 0.15);
		}
	}
		map->draw(renderer, window, tileX, tileY, scale);
	//Render UI
	// Write text to surface
	std::stringstream oss;

	oss << "Turn: " << turnNumber;
	//char* madeString =  oss.str();
	/*char* topText = "Turn: ";
	char integer_string[32];
	sprintf(integer_string, "%d", turnNumber);
	strcat(topText,)*/
	//oss.str();
	SDL_Color text_color = {255, 255, 255};
   textSurface = TTF_RenderText_Solid(font,
		   oss.str().c_str(),
   text_color);
   if (textSurface == NULL)
   {
	  cerr << "TTF_RenderText_Solid() Failed: " << TTF_GetError() << endl;
	  TTF_Quit();
	  SDL_Quit();
	  exit(1);
   }
	this->textTexture = SDL_CreateTextureFromSurface(renderer,textSurface);
	int windowW;
	int windowH;
	SDL_GetWindowSize(window, &windowW, &windowH);
	SDL_Rect destRect = {windowW-textSurface->w-10,10,textSurface->w,textSurface->h};
	SDL_RenderCopy(renderer, this->textTexture, NULL, &destRect);


	return true; //succesful render
}
InGameState::turnState InGameState::getTurnState(){
	return this->currentTurnState;
}
void InGameState::nextTurn(){
	cout << "Next Turn";
}
InGameState::~InGameState() {
	delete map;
}

} /* namespace std */
