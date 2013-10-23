/*
 * Unit.cpp
 *
 *  Created on: Sep 30, 2013
 *      Author: CRHSCS115
 */

#include "Unit.h"
#include "ResourceLoader.h"
#include "Order.h"
namespace kingdom {

Unit::Unit(int PlayerNumber, int TileX, int TileY) : Drawable(){
	// TODO Auto-generated constructor stub
	this->playerNum = PlayerNumber;
	/*this->tileX = TileX;
	this->tileY = TileY;*/
	switch(this->playerNum){
		case 0:
			this->myImagePlayerSufix = "Green";
			break;
		case 1:
			this->myImagePlayerSufix = "Red";
			break;
	}
	orders = vector<Order*>();
}
void Unit::render(SDL_Renderer* Renderer,SDL_Window* Window){

}
void Unit::giveOrder(Order* theOrder){
	this->orders.push_back(theOrder);
}
void Unit::nextUnitTurn(){
	for(int i = 0; i < orders.size(); i++){
		orders.at(i)->decrementTurns();
	}
	if(orders.at(0)->getTurnsTillExecute <= 0){
		orders.at(0)->activated = true;
	}

	//this->unitTurnState = Animating;
}

Unit::~Unit() {
	// TODO Auto-generated destructor stub
}

} /* namespace kingdom */
