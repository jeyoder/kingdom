/*
 * Unit.cpp
 *
 *  Created on: Sep 30, 2013
 *      Author: CRHSCS115
 */

#include "Unit.h"
#include "ResourceLoader.h"
#include "Order.h"
#include "WayPoint.h"
#include <cmath>
#include "TileMap.h"
namespace kingdom {
using namespace std;
Unit::Unit(int PlayerNumber, int TileX, int TileY) : Drawable(){
	// TODO Auto-generated constructor stub
	this->playerNum = PlayerNumber;
	this->tileX = TileX;
	this->tileY = TileY;
	switch(this->playerNum){
		case 0:
			this->myImagePlayerSufix = "Green";
			break;
		case 1:
			this->myImagePlayerSufix = "Red";
			break;
	}
	this->currentUnitTurnState = Input;
	orders = vector<Order*>();
}
void Unit::render(SDL_Renderer* Renderer,SDL_Window* Window){

}
void Unit::giveOrder(Order* theOrder){
	this->orders.push_back(theOrder);
}
void Unit::nextUnitTurn(){
	for(unsigned int i = 0; i < orders.size(); i++){
		orders.at(i)->decrementTurns();
	}
	if(orders.size() > 0 &&  orders.at(0)->getTurnsTillExecute <= 0){
		orders.at(0)->activated = true;
		this->currentOrder = orders.at(0);
	}

	this->currentUnitTurnState = Animating;
}
void Unit::moveAnimate(double delta){
	if(this->currentUnitTurnState == Animating){
		if(msAlreadyAnimated == 0){
			this->currentMoveingToPoint = currentOrder->nextOrderClosestTile();
		}
		this->msAlreadyAnimated += delta;
		int workingTime = msAlreadyAnimated;
		if(this->msAlreadyAnimated > this->TimePerTile){
			workingTime = TimePerTile;
		}
		int xFinalOff = abs(currentMoveingToPoint.getX()-this->tileX)/(currentMoveingToPoint.getX()-this->tileX)*TileMap::tileW;
		int yFinalOff = abs(currentMoveingToPoint.getY()-this->tileY)/(currentMoveingToPoint.getY()-this->tileY)*TileMap::tileH;
		double movedPercent = workingTime/TimePerTile;
		this->offsetX = xFinalOff*movedPercent;
		this->offsetY = yFinalOff*movedPercent;
	}
}
Unit::~Unit() {
	// TODO Auto-generated destructor stub
}

} /* namespace kingdom */
