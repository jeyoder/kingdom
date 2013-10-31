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
#include <iostream>
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
	this->offsetX = 0;
	this->offsetY = 0;
	this->currentUnitTurnState = Input;
	orders = vector<Order*>();
}
void Unit::render(SDL_Renderer* Renderer,SDL_Window* Window){

}
void Unit::giveOrder(Order* theOrder){
	std::cout << "Looky her unit at " << tileX << tileY << "got a order";
	this->orders.push_back(theOrder);
}
void Unit::nextUnitTurn(){
	std::cout << "Hey I'm a Unit at " << tileX << tileY << "taking my turn \n";
	cout.flush();
	for(unsigned int i = 0; i < orders.size(); i++){
		orders.at(i)->decrementTurns();
	}
	if(orders.size() > 0 &&  orders.at(0)->getTurnsTillExecute <= 0){
		orders.at(0)->activated = true;
		this->currentOrder = orders.at(0);
		std::cout << "assigning current order " << currentOrder->completed << "\n";
		std::cout.flush();
	}

	this->currentUnitTurnState = Animating;
}
void Unit::moveAnimate(double delta){
	if(this->currentUnitTurnState == Animating){
		//if(msAlreadyAnimated == -1){
			//If this is the first time this turn
		this->currentMoveingToPoint = currentOrder->nextOrderClosestTile();
			//msAlreadyAnimated = 0;
		//}
		std::cout << "----- \n next closest tile " << currentMoveingToPoint.getX() << ", " << currentMoveingToPoint.getY() << "\n";
		std::cout.flush();
		if(!currentOrder->completed && tilesMovedAlready < TilesPerTurn){
			this->msAlreadyAnimated += delta;
			double workingTime = msAlreadyAnimated;
			if(this->msAlreadyAnimated > this->TimePerTile){
				workingTime = TimePerTile;
			}
			int xFinalOff = (currentMoveingToPoint.getX()-this->tileX != 0) ? abs(currentMoveingToPoint.getX()-this->tileX)/(currentMoveingToPoint.getX()-this->tileX)*TileMap::tileW : (int)0;
			int yFinalOff = (currentMoveingToPoint.getY()-this->tileY != 0) ? abs(currentMoveingToPoint.getY()-this->tileY)/(currentMoveingToPoint.getY()-this->tileY)*TileMap::tileH : (int)0;

			//std::cout << "t parts " <<abs(currentMoveingToPoint.getY()-this->tileX) << ", " << (currentMoveingToPoint.getY()-this->tileY) << ", " << TileMap::tileH;
			std::cout.flush();
			double movedPercent = workingTime/TimePerTile;
			this->offsetX = xFinalOff*movedPercent;
			this->offsetY = yFinalOff*movedPercent;
			//std::cout << "offset " <<offsetX << ", " << offsetY <<  " movedPercent " << movedPercent << " wt " << workingTime << " FinalOff " << xFinalOff << ", " << yFinalOff;
			std::cout.flush();
			if(msAlreadyAnimated > this->TimePerTile){
				//Done for this time
				this->tileX = currentMoveingToPoint.getX();
				this->tileY = currentMoveingToPoint.getY();
				this->offsetX = 0;
				this->offsetY = 0;
				tilesMovedAlready++;
				msAlreadyAnimated = msAlreadyAnimated-TimePerTile;
			}
		}
		else{
			//ok current order is done. Let's call go back to input
			msAlreadyAnimated = 0;
			tilesMovedAlready = 0;
			tilesMovedAlready++;
			if(tilesMovedAlready >= TilesPerTurn){
				tilesMovedAlready = 0;
				this->currentUnitTurnState = Input;
			}
		}
	}
}
Unit::unitTurnState Unit::getUnitTurnState(){
	return currentUnitTurnState;
}
Unit::~Unit() {
	// TODO Auto-generated destructor stub
	for(unsigned int i = 0; i < orders.size(); i++){
		delete orders.at(i);
	}
}

} /* namespace kingdom */
