/*
 * Unit.h
 *
 *  Created on: Sep 30, 2013
 *      Author: CRHSCS115
 */

#ifndef UNIT_H_
#define UNIT_H_

#include "Drawable.h"
#include <string>
#include "ResourceLoader.h"
#include "Order.h"
#include <vector>
namespace kingdom {
using namespace std;
class Order;
class Unit: public Drawable {
private:
	int playerNum;
	vector<Order*> orders;
	int TilesPerTurn = 1; //Would likely be called something like "Movement Speed" in game UI
	int TimePerTile = 1000; //How many miliseconds it takes to move one tile while animating
protected:
	virtual void render(SDL_Renderer*, SDL_Window*);
	std::string myImagePlayerSufix;
	std::string myImagePlayerPrefix;
public:
	enum unitTurnState {Input, Animating};
	Unit(int PlayerNumber,int TileX,int TileY);
	int tileX, tileY;
	virtual ~Unit();
	virtual SDL_Texture* getTexture(ResourceLoader* Loader) = 0;
	void giveOrder(Order* TheOrder);
	virtual void nextUnitTurn();
};

} /* namespace kingdom */
#endif /* UNIT_H_ */
