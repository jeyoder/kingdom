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
int WayPoint::getX() const{
	return x;
}
int WayPoint::getY() const{
	return y;
}
WayPoint::~WayPoint() {
	// TODO Auto-generated destructor stub
}

const bool WayPoint::operator== (const WayPoint& comp) {
	return (x == comp.getX() && y == comp.getY());
}

const bool WayPoint::operator!= (const WayPoint& comp) {
	WayPoint compare = comp;
	return !(compare == (*this));
}



} /* namespace kingdom */
