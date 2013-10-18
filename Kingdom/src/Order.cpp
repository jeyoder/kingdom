/*
 * Order.cpp
 *
 *  Created on: Oct 18, 2013
 *      Author: CRHSCS115
 */

#include "Order.h"

namespace kingdom {

Order::Order(Unit *ToWho, std::vector<WayPoint*> Waypoints, int TurnsTillExecute) {
	// TODO Auto-generated constructor stub
	this->toWho = ToWho;
	this->waypoints = Waypoints;
	this->turnsTillExecute = TurnsTillExecute;
}

Order::~Order() {
	// TODO Auto-generated destructor stub
}

} /* namespace kingdom */
