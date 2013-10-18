/*
 * WayPoint.cpp
 *
 *  Created on: Oct 18, 2013
 *      Author: CRHSCS115
 */

#include "WayPoint.h"

namespace kingdom {

WayPoint::WayPoint(int X, int Y) {
	// TODO Auto-generated constructor stub
	this->x = X;
	this->y = Y;
}
int WayPoint::getX(){
	return x;
}
int WayPoint::getY(){
	return y;
}
WayPoint::~WayPoint() {
	// TODO Auto-generated destructor stub
}

} /* namespace kingdom */
