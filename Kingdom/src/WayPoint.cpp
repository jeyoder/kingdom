/*
 * WayPoint.cpp
 *
 *  Created on: Oct 18, 2013
 *      Author: CRHSCS115
 */

#include "WayPoint.h"
#include <cmath>
#include <iostream>
namespace kingdom {
using namespace std;
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
WayPoint WayPoint::closestTile(int YourX, int YourY){
	int xRealOff = this->x-YourX;
	int yRealOff = this->y-YourY;
	int xOff = 0;
	int yOff = 0;
	if(abs(xRealOff) > 0 || abs(yRealOff) > 0){
		if(abs(xRealOff) > abs(yRealOff)){
			xOff = (xRealOff != 0) ? abs(xRealOff)/xRealOff : 0; //will out put 1 or -1 depending on sign of reall offset
		}
		else{
			yOff = (yRealOff != 0) ? abs(yRealOff)/yRealOff : 0;
		}
	}
	//cout << "waypoint Off " << xOff << ", " << yOff << "real off " << xRealOff << ", " << yRealOff;
	//cout.flush();
	return WayPoint(YourX+xOff, YourY+yOff);
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
