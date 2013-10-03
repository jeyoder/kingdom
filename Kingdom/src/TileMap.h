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

#include "MapLoader.h"
#include "Unit.h"
#include "ResourceLoader.h"
namespace kingdom {
class TileMap {
public:
	TileMap(MapLoader* generator, SDL_Texture* tileset, ResourceLoader* Loader);
	virtual ~TileMap();
	void draw(SDL_Renderer* renderer, SDL_Window* window, double tileX, double tileY);
	int tileAt(int x, int y);
	Unit* unitAt(int x, int y);
	int getW();
	int getH();
	std::vector<short> mapData;
	const int tileW = 32;
	const int tileH = 32;
private:
	SDL_Texture* tileset;

	std::vector<Unit*> mapUnits;

	int mapW;
	int mapH;
	ResourceLoader* theLoader;
};
}
#endif /* TILEMAP_H_ */
