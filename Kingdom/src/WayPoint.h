/*
 * WayPoint.h
 *
 *  Created on: Oct 18, 2013
 *      Author: CRHSCS115
 */

#ifndef WAYPOINT_H_
#define WAYPOINT_H_

namespace kingdom {

class WayPoint {
private:
	int x;
	int y;
public:
	WayPoint(int X, int Y);
	virtual ~WayPoint();
	int getX();
	int getY();
	WayPoint closestTile(int yourX, int yourY);
	/*int xDir(int yourX);
	int yDir(int yourY);*/
};

} /* namespace kingdom */
#endif /* WAYPOINT_H_ */
