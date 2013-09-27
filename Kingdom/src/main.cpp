/*
 * main.cpp
 *
 *  Created on: Sep 12, 2013
 *      Author: crhscs264
 */
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "ResourceLoader.h"
#include "AppState.h"
#include "InGameState.h"
using namespace std;
using namespace kingdom;
SDL_Window* window;
int main(int argc, char* argv[]) {
	cout << "hello world";

	//Start SDL
	SDL_Init(SDL_INIT_EVERYTHING | SDL_INIT_NOPARACHUTE);
	window = SDL_CreateWindow("Resource Loader", 100, 100, 1024, 768, SDL_WINDOW_OPENGL);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	cout << "SDL initialized" << endl;
	ResourceLoader loader(renderer);
	loader.loadTexture("assets/thor.png");
	SDL_Texture *texture = loader.loadTexture("assets/thor.png");

	//Initialize App State
	InGameState currentAppState = InGameState();
	//Game Loop
	int f = 0;
	while(f < 30*5){
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
		SDL_Delay(1000 / 30);
		f++;
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	return 0;
}
