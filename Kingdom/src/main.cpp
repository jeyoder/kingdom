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
using namespace std;

int main(int argc, char* argv[]) {
	cout << "hello world";
	SDL_Init(SDL_INIT_EVERYTHING | SDL_INIT_NOPARACHUTE);
	SDL_Window *window = SDL_CreateWindow("Resource Loader", 100, 100, 1024, 768, SDL_WINDOW_OPENGL);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	cout << "SDL initialized" << endl;
	ResourceLoader loader(renderer);
	loader.loadTexture("assets/thor.png");
	SDL_Texture *texture = loader.loadTexture("assets/thor.png");
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
	SDL_Delay(5000);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	return 0;
}
