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
#include "ResourceLoader.h"
#include "AppState.h"
#include "InGameState.h"
#include "FileMapGenerator.h"
#include "TileMap.h"
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
			SDL_RENDERER_ACCELERATED);
	cout << "SDL initialized" << endl;

	ResourceLoader* loader = ResourceLoader::getInstance(renderer);
	loader->loadTexture("assets/thor.png");
	//SDL_Texture *texture = loader->loadTexture("assets/thor.png");

	loader->loadTexture("assets/KingGreen.png");
	loader->loadTexture("assets/KingRed.png");

	SDL_Texture *tileset = loader->loadTexture("assets/tileset-1.png");
	ifstream stream;
	stream.open("assets/tilemap.txt");
	if (!stream.is_open()) {
		cout << "map file open failed!" << endl;
		return 1;
	}
	cout << "Tilemap opened successfully" << endl;
	FileMapGenerator generator(&stream);
	TileMap map = TileMap(&generator, tileset, loader);
	cout << "Map loaded" << endl;
	cout << "Map width: " << map.getW() << endl;
	cout << "Map height: " << map.getH() << endl;

	cout << map.mapData.size() << " tiles" << endl;
	cout.flush();
	//Initialize App State
	InGameState currentAppState = InGameState();
	//Game Loop
	double tileX = 40;
	double tileY = 40;
	double moveSpeed = .05;
	clock_t startTime;
	int frameCount = 0;
	startTime = clock();
	while (true) {
		 SDL_Event e;
		        while (SDL_PollEvent(&e)) {
		            if (e.type == SDL_QUIT) {
		                return 0;
		            }
		        }

		        const Uint8 *keystates = SDL_GetKeyboardState(NULL);
		        if(keystates[SDL_SCANCODE_W]) {
		        	tileY -= moveSpeed;
		        }
		        if(keystates[SDL_SCANCODE_A]) {
					tileX -= moveSpeed;
				}
		        if(keystates[SDL_SCANCODE_S]) {
					tileY += moveSpeed;
				}
		        if(keystates[SDL_SCANCODE_D]) {
					tileX += moveSpeed;
				}
		        if(keystates[SDL_SCANCODE_ESCAPE]) {
		        	return 0;
		        }
		SDL_RenderClear(renderer);
		map.draw(renderer, window, tileX, tileY);
		SDL_RenderPresent(renderer);
		frameCount++;
		if(((double)(clock() - startTime)) / CLOCKS_PER_SEC > 1.0) {
			cout << frameCount << " FPS" << endl;
			frameCount = 0;
			startTime = clock();
		}
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	return 0;
}
