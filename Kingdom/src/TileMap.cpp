/*
 * TileMap.cpp
 *
 *  Created on: Sep 25, 2013
 *      Author: crhscs264
 */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <exception>
#include <cmath>
#include "TileMap.h"
#include "Unit.h"
#include <vector>
#include "King.h"
#include "ResourceLoader.h"
#include <iterator>
#include "Pawn.h"
using namespace std;
namespace kingdom {

TileMap::TileMap(MapLoader* generator, SDL_Texture* tileset) {
	this->tileset = tileset;
	this->mapW = generator->getWidth();
	this->mapH = generator->getHeight();
	this->mapData = generator->getData();
	//mapUnits = std::vector<std::vector<Unit> > (this->mapW); //create a 2d vector containing units
	mapUnits = std::vector<Unit*> (); //create a vector containing pointers to our units
	mapUnits.push_back(new King(0,50, 50));
	mapUnits.push_back(new Pawn(0,51, 49));
	mapUnits.push_back(new Pawn(0,49, 49));
	/*mapUnits.push_back(new King(0,50, 51));
	mapUnits.push_back(new King(0,55,55));*/
	vector<WayPoint*> orderWays = vector<WayPoint*>();
	//orderWays.push_back(new WayPoint(56,50));
	//orderWays.push_back(new WayPoint(56,53));
	//mapUnits.at(0)->giveOrder(new Order(mapUnits.at(0),orderWays,1));
	//orderWays = vector<WayPoint*>();
	//orderWays.push_back(new WayPoint(51,51));
	///orderWays.push_back(new WayPoint(56,53));
	//mapUnits.at(0)->giveOrder(new Order(mapUnits.at(0),orderWays,4));
	//delete mapUnits[5];
	selectedTex = ResourceLoader::getInstance()->loadTexture("assets/selected.png");
	waypointTex = ResourceLoader::getInstance()->loadTexture("assets/target.png");
	waypointChooserTex = ResourceLoader::getInstance()->loadTexture("assets/target_chooser.png");
	pathfindingTex = ResourceLoader::getInstance()->loadTexture("assets/pathfinding-dot.png");
}

TileMap::~TileMap() {
	// TODO Auto-generated destructor stub
}

void TileMap::draw(SDL_Renderer* renderer, SDL_Window* window, double tileX, double tileY, double zoomLevel, vector<Unit*>& selectedUnits, vector<WayPoint>& waypoints, vector<WayPoint>& path) {
	int windowW;
	int windowH;
	SDL_GetWindowSize(window, &windowW, &windowH);


	int minTileX = max((int) (tileX - (windowW / 2 / zoomLevel / tileW)), 0);
	int maxTileX = min((int) (tileX + (windowW / 2 / zoomLevel / tileW) + 1), mapW - 1);
	int minTileY = max((int) (tileY - (windowH / 2 / zoomLevel / tileH)), 0);
	int maxTileY = min((int) (tileY + (windowH / 2 / zoomLevel / tileH) + 1), mapH - 1);

	int selX = 50, selY = 50;
	//render tiles
	for (int x = minTileX; x <= maxTileX; x++) {
		for (int y = minTileY; y <= maxTileY; y++) {
			int srcTile = tileAt(x, y);
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

			SDL_RenderCopy(renderer, tileset, &srcRect, &destRect); //draw the tile
		}
	}
	//render stuff on the tiles
	for (int x = minTileX; x <= maxTileX; x++) {
		for (int y = minTileY; y <= maxTileY; y++) {
			int srcTile = tileAt(x, y);
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
			for(vector<Unit*>::iterator it = selectedUnits.begin(); it != selectedUnits.end(); ++it) {
				Unit* unit = *it;
				if(unit->tileX == x && unit->tileY == y) {
					SDL_RenderCopy(renderer, selectedTex, NULL, &destRect);
				}
			}

			for(vector<WayPoint>::iterator it = waypoints.begin(); it!=waypoints.end(); ++it) {
				WayPoint wp = *it;
				if(wp.getX() == x && wp.getY() == y) {
					SDL_RenderCopy(renderer, waypointChooserTex, NULL, &destRect);
				}
			}
			for(WayPoint wp : path) {
							if(wp.getX() == x && wp.getY() == y) {
								SDL_RenderCopy(renderer, pathfindingTex, NULL, &destRect);
							}
						}


			Unit* drawingUnit = unitAt(x, y);
			if(drawingUnit != NULL){
				SDL_Rect animatedDestRect = destRect;
				//cout << "offsetX = " << drawingUnit->offsetX;
				animatedDestRect.x += drawingUnit->offsetX * zoomLevel;
				animatedDestRect.y += drawingUnit->offsetY * zoomLevel;
				SDL_RenderCopy(renderer, drawingUnit->getTexture(ResourceLoader::getInstance()), NULL, &animatedDestRect); //draw the unit, if exists
			}
		}
	}
}
int TileMap::tileAt(int x, int y) {
	return mapData.at(y * mapW + x);
}
Unit* TileMap::unitAt(int x, int y) {
	for(vector<Unit*>::iterator it = mapUnits.begin(); it != mapUnits.end(); ++it) {
		Unit* unit = *it;
		if(unit->tileX == x && unit->tileY == y) {
			return unit;
		}
	}
	return NULL;
}

std::vector<Unit*> TileMap::getUnitsList(){
	/*std::vector<Unit*> cleanList;
	for(unsigned int i = 0; i < this->mapUnits.size(); i++){
		if(mapUnits.at(i) != NULL){
			cleanList.push_back(mapUnits.at(i));
		}
	}
	return cleanList;*/
	return mapUnits;
}


bool TileMap::isTilePassable(int x, int y) {
	int tile = tileAt(x,y);
	return (tile == 1);
}

int TileMap::getW() {
return mapW;
}

int TileMap::getH() {
	return mapH;
}
}
