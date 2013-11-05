/*
 * Order.h
 *
 *  Created on: Oct 18, 2013
 *      Author: CRHSCS115
 */

#ifndef ORDER_H_
#define ORDER_H_

#include <vector>
#include "Unit.h"
#include "WayPoint.h"
#include "TileMap.h"
namespace kingdom {
using namespace std;
class Order {
private:
	Unit* toWho;
	TileMap* map;
	std::vector<WayPoint> waypoints;
	int turnsTillExecute;
	std::vector<WayPoint> aStar(WayPoint from, WayPoint to);
public:
	Order(Unit *ToWho, std::vector<WayPoint> Waypoints, int TurnsTillExecute, TileMap* map);
	Order();
	virtual ~Order();
	std::vector<WayPoint> getPath();
	std::vector<WayPoint> getWayPoints();
};

} /* namespace kingdom */
#endif /* ORDER_H_ */
