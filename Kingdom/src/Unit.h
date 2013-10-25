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
#include "WayPoint.h"
#include <vector>
namespace kingdom {
using namespace std;
class Order;
class Unit: public Drawable {
public:
	enum unitTurnState {Input, Animating};
	Unit(int PlayerNumber,int TileX,int TileY);
	int tileX, tileY;
	virtual ~Unit();
	virtual SDL_Texture* getTexture(ResourceLoader* Loader) = 0;
	void giveOrder(Order* TheOrder);
	virtual void nextUnitTurn();
	void moveAnimate(double delta);
	int offsetX,offsetY;
private:
	int playerNum;
	vector<Order*> orders;
	int TilesPerTurn = 1; //Would likely be called something like "Movement Speed" in game UI
	int TimePerTile = 1000; //How many miliseconds it takes to move one tile while animating
	int tilesMovedAlready = 0;
	int msAlreadyAnimated = 0;
	unitTurnState currentUnitTurnState = Input;
	Order* currentOrder = NULL;
	WayPoint currentMoveingToPoint = WayPoint(0,0);
protected:
	virtual void render(SDL_Renderer*, SDL_Window*);
	std::string myImagePlayerSufix;
	std::string myImagePlayerPrefix;

};

} /* namespace kingdom */
#endif /* UNIT_H_ */
