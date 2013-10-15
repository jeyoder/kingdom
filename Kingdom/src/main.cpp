/*
 * main.cpp
 *
 *  Created on: Sep 12, 2013
 *      Author: crhscs264
 */
#include <iostream>
#include <fstream>
#include <ctime>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "ResourceLoader.h"
#include "AppState.h"
#include "InGameState.h"
#include "FileMapGenerator.h"
#include "TileMap.h"
#include "Game.h"
using namespace std;
using namespace kingdom;
SDL_Window* window;
int main(int argc, char* argv[]) {
	cout << "hello world";

	//Start SDL
	SDL_Init(SDL_INIT_EVERYTHING | SDL_INIT_NOPARACHUTE);
	window = SDL_CreateWindow("Resource Loader", 100, 100, 1024, 768,
			SDL_WINDOW_OPENGL);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	cout << "SDL initialized" << endl;
	// Initialize SDL_ttf library
		   if (TTF_Init() != 0)
		   {
		      cerr << "TTF_Init() Failed: " << TTF_GetError() << endl;
		      SDL_Quit();
		      exit(1);
		   }

	ResourceLoader::initialize(renderer);
	Game game(renderer, window);
	game.run();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	return 0;
}
