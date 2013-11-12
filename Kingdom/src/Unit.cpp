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
	currentOrder = nullptr;
	msAlreadyAnimated = 0;
	tilesMovedAlready = 0;
	tilesPerTurn = 0;
	timePerTile = 1000;
}

WayPoint Unit::getPosition() {
	return WayPoint(tileX, tileY);
}
void Unit::render(SDL_Renderer* Renderer,SDL_Window* Window){

}
void Unit::giveOrder(Order* theOrder){
	std::cout << "Looky here unit at (" << tileX << "," << tileY << ") got a order";
	this->orders.push_back(theOrder);
}
void Unit::nextUnitTurn(){
	if(orders.size() > 0){ //if we have orders...
		for(unsigned int i = 0; i < orders.size(); i++){
			orders.at(i)->decrementTurns(); //, then decrement their turns
		}
		for(int i = orders.size() - 1; i >= 0; i--){
			//loop through and look for most recent order that is is ready
			if(orders.at(i)->getTurnsTillExecute() <= 0){
				orders.at(i)->activated = true;
				this->currentOrder = orders.at(i);
				this->currentUnitTurnState = Animating;
				currentMovingToPoint = currentOrder->nextTile(getPosition());
				//delete everything before it
				for(int ii = 0; ii < i; ii++){
					std::cout << "deleting ii " << ii << "\n";
					std::cout.flush();
					delete orders.at(ii);
					orders.erase(orders.begin() + ii);
				}

				break;
			}
		}
	}
}
void Unit::moveAnimate(double delta){

	if(this->currentUnitTurnState == Animating){
		//if(msAlreadyAnimated == -1){
			//If this is the first time this turn

			currentOrder->updateStatus(getPosition());
			//msAlreadyAnimated = 0;
		//}
		//std::cout << "----- \n next closest tile " << currentMoveingToPoint.getX() << ", " << currentMoveingToPoint.getY() << " tiles already movied " << tilesMovedAlready <<"\n";
		std::cout.flush();
		if(currentOrder != NULL && !currentOrder->completed() && tilesMovedAlready < tilesPerTurn){
			this->msAlreadyAnimated += delta;
			double workingTime = msAlreadyAnimated;
			if(this->msAlreadyAnimated > this->timePerTile){
				workingTime = timePerTile;
			}
			int xFinalOff = (currentMovingToPoint.getX()-this->tileX != 0) ? abs(currentMovingToPoint.getX()-this->tileX)/(currentMovingToPoint.getX()-this->tileX)*TileMap::tileW : (int)0;
			int yFinalOff = (currentMovingToPoint.getY()-this->tileY != 0) ? abs(currentMovingToPoint.getY()-this->tileY)/(currentMovingToPoint.getY()-this->tileY)*TileMap::tileH : (int)0;

			//std::cout << "t parts " <<abs(currentMoveingToPoint.getY()-this->tileX) << ", " << (currentMoveingToPoint.getY()-this->tileY) << ", " << TileMap::tileH;
			//std::cout.flush();
			double movedPercent = workingTime/timePerTile;
			this->offsetX = xFinalOff*movedPercent;
			this->offsetY = yFinalOff*movedPercent;
			//std::cout << "offset " <<offsetX << ", " << offsetY <<  " movedPercent " << movedPercent << " wt " << workingTime << " FinalOff " << xFinalOff << ", " << yFinalOff << "\n";
			//std::cout.flush();
			if(msAlreadyAnimated > this->timePerTile){ // find a new tile

				//Done for this time
				this->tileX = currentMovingToPoint.getX();
				this->tileY = currentMovingToPoint.getY();
				this->offsetX = 0;
				this->offsetY = 0;
				tilesMovedAlready++;
				this->currentMovingToPoint = currentOrder->nextTile(WayPoint(tileX, tileY));
				msAlreadyAnimated = msAlreadyAnimated-timePerTile;
			}
		}
		else{
			//ok current order is done. Let's call go back to input
			msAlreadyAnimated = 0;
			//tilesMovedAlready = 0;
			//tilesMovedAlready++;
			if(tilesMovedAlready >= tilesPerTurn || currentOrder->completed()){
				tilesMovedAlready = 0;
				this->currentUnitTurnState = Input;
			}
			if(currentOrder->completed()){
				for(vector<Order*>::iterator order = orders.begin(); order != orders.end(); ++order){
					if(*order == currentOrder){
						orders.erase(order);
						break;
					}
				}
				delete currentOrder;
				std::cout << "made5 and size is now " <<orders.size();
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
