/*
 * Order.h
 *
 *  Created on: Oct 18, 2013
 *      Author: CRHSCS115
 */

#ifndef ORDER_H_
#define ORDER_H_

#include <vector>
#include <list>
#include "TileMap.h"
#include "Unit.h"
#include "WayPoint.h"

#include "Order.h"
namespace kingdom {
class Unit;
class TileMap;
class Order {
private:
	TileMap* map;
	std::vector<WayPoint> waypoints;
	int turnsTillExecute;
	std::vector<WayPoint> aStar(WayPoint from, WayPoint to);
public:
	Order(std::vector<WayPoint> Waypoints, int TurnsTillExecute, TileMap* map);
	Order();
	virtual ~Order();
	std::vector<WayPoint> getPath(WayPoint startPos);
	std::vector<WayPoint> getWayPoints();
	void decrementTurns();
	bool activated;
	int getTurnsTillExecute();
	WayPoint nextTile(WayPoint currentPos);
	bool completed();
	void updateStatus(WayPoint currentPos);
};

} /* namespace kingdom */
#endif /* ORDER_H_ */
