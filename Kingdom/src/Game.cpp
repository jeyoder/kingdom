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

#include "SDL.h"
#include "SDL_ttf.h"
using namespace std;
namespace kingdom {

Game::Game(SDL_Renderer* renderer, SDL_Window* window) {
	this->renderer = renderer;
	this->window = window;
	FileMapGenerator loader("assets/tilemap.txt");
	this->state = new InGameState(&loader, "assets/tileset-1.png");
	this->keystates = NULL;
}

Game::~Game() {

}

void Game::run() {
	clock_t startTime;
	clock_t lastFrameTime;
	int frameCount = 0;
	startTime = lastFrameTime = clock();
	while (true) {
		int delta = (clock() - lastFrameTime) * 1000 / CLOCKS_PER_SEC;
		lastFrameTime = clock();
		SDL_Event e;
		vector<SDL_Event> events;
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				return;
			} else {
				events.push_back(e);
			}
		}
		keystates = SDL_GetKeyboardState(NULL);
		if (keystates[SDL_SCANCODE_ESCAPE])
			return;
		SDL_RenderClear(renderer);
		state->render(renderer, window, delta, keystates, events);
		SDL_RenderPresent(renderer); //will vsync
		frameCount++;
		if (((double) (clock() - startTime)) / CLOCKS_PER_SEC > 1.0) {
			cout << frameCount << " FPS d=" << delta << endl;
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

void Game::renderText(std::string text, TTF_Font* font, SDL_Color color, int x, int y, SDL_Renderer* renderer) {
	SDL_Surface* textSurface = TTF_RenderText_Blended(font, text.c_str(), color);

	if (textSurface == NULL) {
		cerr << "TTF_RenderText_Solid() Failed: " << TTF_GetError() << endl;
		TTF_Quit();
		SDL_Quit();
		exit(1);
	}
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_Rect dest = { x, y, textSurface->w, textSurface->h };
	SDL_RenderCopy(renderer, textTexture, NULL, &dest);
}

} /* namespace kingdom */
