/*
 * TileMap.cpp
 *
 *  Created on: Sep 25, 2013
 *      Author: crhscs264
 */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include "TileMap.h"
#include "Unit.h"
#include <vector>
#include "King.h"
#include "ResourceLoader.h"
using namespace std;
namespace kingdom {

TileMap::TileMap(MapLoader* generator, SDL_Texture* tileset) {
	this->tileset = tileset;
	this->mapW = generator->getWidth();
	this->mapH = generator->getHeight();
	this->mapData = generator->getData();
	//mapUnits = std::vector<std::vector<Unit> > (this->mapW); //create a 2d vector containing units
	mapUnits = std::vector<Unit*> (this->mapW*this->mapH); //create a 2d vector containing units
	mapUnits[50*50+50] = new King(0,5,5);
	//delete mapUnits[5];
}

TileMap::~TileMap() {
	// TODO Auto-generated destructor stub
}

void TileMap::draw(SDL_Renderer* renderer, SDL_Window* window, double tileX, double tileY, double zoomLevel) {
	int windowW;
	int windowH;
	SDL_GetWindowSize(window, &windowW, &windowH);

	zoomLevel = floor(zoomLevel * tileW) / tileW; //round zoomLevel to the nearest tile width multiple
	int minTileX = max((int) (tileX - (windowW / 2 / zoomLevel / tileW)), 0);
	int maxTileX = min((int) (tileX + (windowW / 2 / zoomLevel / tileW) + 1), mapW - 1);
	int minTileY = max((int) (tileY - (windowH / 2 / zoomLevel / tileH)), 0);
	int maxTileY = min((int) (tileY + (windowH / 2 / zoomLevel / tileH) + 1), mapH - 1);


	for (int x = minTileX; x <= maxTileX; x++) {
		for (int y = minTileY; y <= maxTileY; y++) {
			int srcTile = tileAt(x, y);
			Unit* drawingUnit = unitAt(x, y);
			SDL_Rect srcRect = {};
			srcRect.x = (srcTile - 1) * tileW;
			srcRect.y = 0;
			srcRect.w = tileW;
			srcRect.h = tileH;

			SDL_Rect destRect = {};
			destRect.x = ((x - tileX) * tileW * zoomLevel) + (windowW / 2);
			destRect.y = ((y - tileY) * tileH * zoomLevel) + (windowH / 2);
			//cout << "X: " << destRect.x << " / " << endl;
			destRect.w = tileW * zoomLevel;
			destRect.h = tileH * zoomLevel;

			SDL_RenderCopy(renderer, tileset, &srcRect, &destRect);
			if(drawingUnit != NULL){
				SDL_RenderCopy(renderer, drawingUnit->getTexture(theLoader), NULL, &destRect);
			}

		};
	}
}
int TileMap::tileAt(int x, int y) {
	return mapData.at(y * mapW + x);
}
Unit* TileMap::unitAt(int x, int y) {
	return mapUnits.at(y * mapW + x);
}
int TileMap::getW() {
return mapW;
}

int TileMap::getH() {
	return mapH;
}
}
