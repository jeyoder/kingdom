/*
 * Unit.cpp
 *
 *  Created on: Sep 30, 2013
 *      Author: CRHSCS115
 */

#include "Unit.h"

namespace kingdom {

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
}
void Unit::render(SDL_Renderer* Renderer,SDL_Window* Window){

}
Unit::~Unit() {
	// TODO Auto-generated destructor stub
}

} /* namespace kingdom */
