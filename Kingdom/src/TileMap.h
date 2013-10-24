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
#include "WayPoint.h"
namespace kingdom {
class TileMap {
public:
	TileMap(MapLoader* generator, SDL_Texture* tileset);
	virtual ~TileMap();
	void draw(SDL_Renderer* renderer, SDL_Window* window, double tileX, double tileY, double zoomLevel, std::vector<Unit*>& selectedUnits, std::vector<WayPoint>& waypoints);
	int tileAt(int x, int y);
	Unit* unitAt(int x, int y);
	int getW();
	int getH();
	std::vector<short> mapData;
	static const int tileW = 64;
	static const int tileH = 64;
	std::vector<Unit*> getUnitsList();
private:
	SDL_Texture* tileset;

	std::vector<Unit*> mapUnits;

	int mapW;
	int mapH;
	SDL_Texture* selectedTex;
	SDL_Texture* waypointTex;
};
}
#endif /* TILEMAP_H_ */
