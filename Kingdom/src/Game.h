/*
 * App.h
 *
 *  Created on: Oct 3, 2013
 *      Author: crhscs264
 */

#ifndef APP_H_
#define APP_H_
#include "SDL.h"
#include "ResourceLoader.h"
#include "AppState.h"
namespace kingdom {

class Game {
public:
	Game(SDL_Renderer* renderer, SDL_Window* window);
	virtual ~Game();
	void run();
	AppState& getAppState();
	void setAppState(AppState* state);
	Uint8* getKeyStates();
private:
	SDL_Renderer* renderer;
	SDL_Window* window;
	AppState* state;
	const Uint8* keystates;
};

} /* namespace kingdom */
#endif /* APP_H_ */
