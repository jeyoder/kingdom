/*
 * Order.cpp
 *
 *  Created on: Oct 18, 2013
 *      Author: CRHSCS115
 */

#include "Order.h"
#include <iostream>
namespace kingdom {

Order::Order(Unit *ToWho, std::vector<WayPoint*> Waypoints, int TurnsTillExecute) {
	// TODO Auto-generated constructor stub
	this->toWho = ToWho;
	this->waypoints = Waypoints;
	this->turnsTillExecute = TurnsTillExecute;

}
void Order::decrementTurns(){
	turnsTillExecute--;
	std::cout << "order decrementing. now have " << turnsTillExecute << "turns \n";
	std::cout.flush();
}
WayPoint Order::nextOrderClosestTile(){
	if(this->toWho->tileX == waypoints.at(onWaypoint)->getX() && this->toWho->tileY == waypoints.at(onWaypoint)->getY()){
		//Already reached current waypoint
		if(onWaypoint < waypoints.size() - 1){
			onWaypoint++;
		}
		else{
			this->completed = true;
			return WayPoint(toWho->tileX,toWho->tileY);
		}
	}
	return waypoints.at(onWaypoint)->closestTile(toWho->tileX,toWho->tileY);
}
Order::~Order() {
	// TODO Auto-generated destructor stub
}

} /* namespace kingdom */
