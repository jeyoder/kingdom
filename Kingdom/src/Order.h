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
#include "Order.h"
namespace kingdom {
class Unit;
class Order {
private:
	Unit* toWho;
	std::vector<WayPoint*> waypoints;
	int turnsTillExecute;
public:
	Order(Unit* ToWho, std::vector<WayPoint*> Waypoints, int TurnsTillExecute);
	virtual ~Order();
	void decrementTurns();
	bool activated;
	int getTurnsTillExecute;
	WayPoint nextClosestTile(int myX, );
};

} /* namespace kingdom */
#endif /* ORDER_H_ */
