/*
 * App.cpp
 *
 *  Created on: Oct 3, 2013
 *      Author: crhscs264
 */

#include <ctime>
#include <iostream>
#include "Game.h"
#include "InGameState.h"
#include "FileMapGenerator.h"
using namespace std;
namespace kingdom {

Game::Game(SDL_Renderer* renderer, SDL_Window* window) {
	this->renderer = renderer;
	this->window = window;
	loader = new ResourceLoader(renderer);

	SDL_Texture *tileset = loader->loadTexture("assets/tileset-1.png");
	ifstream stream;
	stream.open("assets/tilemap.txt");
	if (!stream.is_open()) {
		cout << "map file open failed!" << endl;
		throw "Map open failed!";
	}
	cout << "Tilemap opened successfully" << endl;
	FileMapGenerator generator(&stream);
	TileMap* map = new TileMap(&generator, tileset);
	cout << "Map loaded" << endl;
	cout << "Map width: " << map->getW() << endl;
	cout << "Map height: " << map->getH() << endl;
	cout << map->mapData.size() << " tiles" << endl;
	this->state = new InGameState(map);
	this->keystates = NULL;
}

Game::~Game() {
	delete loader;
}

void Game::run() {
	clock_t startTime;
	int frameCount = 0;
	startTime = clock();
	while (true) {
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				return;
			}
		}
		keystates = SDL_GetKeyboardState(NULL);

		SDL_RenderClear(renderer);
		state->render(renderer, window, 16, keystates);
		SDL_RenderPresent(renderer);
		frameCount++;
		if (((double) (clock() - startTime)) / CLOCKS_PER_SEC > 1.0) {
			cout << frameCount << " FPS" << endl;
			frameCount = 0;
			startTime = clock();
		}
	}
}

void Game::setAppState(AppState* state) {
	if (state == NULL)
		return;
	this->state = state;
}

AppState& Game::getAppState() {
	return *(state);
}

ResourceLoader* Game::getResourceLoader() {
	return loader;
}

} /* namespace kingdom */
