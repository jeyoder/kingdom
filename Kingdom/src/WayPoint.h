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
	int getX() const;
	int getY() const;
	const bool operator== (const WayPoint& comp);
	const bool operator!= (const WayPoint& comp);
};


} /* namespace kingdom */
#endif /* WAYPOINT_H_ */
