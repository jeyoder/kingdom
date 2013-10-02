/*
 * TileMap.h
 *
 *  Created on: Sep 25, 2013
 *      Author: crhscs264
 */

#ifndef TILEMAP_H_
#define TILEMAP_H_

#include <string>
#include <fstream>
#include <vector>
#include "SDL.h"
#include "MapLoader.h"
#include "Unit.h"
namespace kingdom {
class TileMap {
public:
	TileMap(MapLoader* generator, SDL_Texture* tileset);
	virtual ~TileMap();
	const int tileW = 32;
	const int tileH = 32;
private:
	SDL_Texture* tileset;
	std::vector<short> mapData;
	std::vector<Unit*> mapUnits;
	int mapW;
	int mapH;

};
}
#endif /* TILEMAP_H_ */
