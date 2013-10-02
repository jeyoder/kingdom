/*
 * TileMap.cpp
 *
 *  Created on: Sep 25, 2013
 *      Author: crhscs264
 */

#include <iostream>
#include <fstream>
#include "TileMap.h"
#include "Unit.h"
#include <vector>
#include "King.h"
using namespace std;
namespace kingdom {
TileMap::TileMap(MapLoader* generator, SDL_Texture* tileset) {
	this->tileset = tileset;
	this->mapW = generator->getWidth();
	this->mapH = generator->getHeight();
	this->mapData = generator->getData();
	//mapUnits = std::vector<std::vector<Unit> > (this->mapW); //create a 2d vector containing units
	mapUnits = std::vector<Unit*> (this->mapW); //create a 2d vector containing units
	mapUnits[5] = new King(0,5,5);
	delete mapUnits[5];
}

TileMap::~TileMap() {
	// TODO Auto-generated destructor stub
}
}
