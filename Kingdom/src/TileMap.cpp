/*
 * TileMap.cpp
 *
 *  Created on: Sep 25, 2013
 *      Author: crhscs264
 */

#include <iostream>
#include <fstream>
#include <algorithm>
#include "TileMap.h"

using namespace std;

TileMap::TileMap(MapLoader* generator, SDL_Texture* tileset) {
	this->tileset = tileset;
	this->mapW = generator->getWidth();
	this->mapH = generator->getHeight();
	this->mapData = generator->getData();
}

TileMap::~TileMap() {
	// TODO Auto-generated destructor stub
}

void TileMap::draw(SDL_Renderer* renderer, SDL_Window* window, double tileX, double tileY) {
	int windowW;
	int windowH;
	SDL_GetWindowSize(window, &windowW, &windowH);

	int minTileX = max((int) (tileX - (windowW / 2 / tileW)), 0);
	int maxTileX = min((int) (tileX + (windowW / 2 / tileW) + 1), mapW - 1);
	int minTileY = max((int) (tileY - (windowH / 2 / tileH)), 0);
	int maxTileY = min((int) (tileY + (windowH / 2 / tileH) + 1), mapH - 1);

	for (int x = minTileX; x <= maxTileX; x++) {
		for (int y = minTileY; y <= maxTileY; y++) {
			int srcTile = tileAt(x, y);
			SDL_Rect srcRect = {};
			srcRect.x = (srcTile - 1) * tileW;
			srcRect.y = 0;
			srcRect.w = tileW;
			srcRect.h = tileH;

			SDL_Rect destRect = {};
			destRect.x = ((x - tileX) * tileW) + (windowW / 2);
			destRect.y = ((y - tileY) * tileH) + (windowH / 2);
			destRect.w = tileW;
			destRect.h = tileH;

			SDL_RenderCopy(renderer, tileset, &srcRect, &destRect);
		};
	}
}
int TileMap::tileAt(int x, int y) {
return mapData.at(y * mapW + x);
}

int TileMap::getW() {
return mapW;
}

int TileMap::getH() {
return mapH;
}

