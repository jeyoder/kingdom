/*
 * PathfindingNode.h
 *
 *  Created on: Oct 29, 2013
 *      Author: crhscs264
 */

#ifndef PATHFINDINGNODE_H_
#define PATHFINDINGNODE_H_
#include "WayPoint.h"
namespace kingdom {

class PathfindingNode {
public:
	virtual ~PathfindingNode();
	WayPoint waypoint;
	int pastScore;
	int totalScore;
	bool scored;
	int distanceTo(WayPoint pt);
	PathfindingNode(WayPoint pt);
	PathfindingNode();
	bool operator<(const PathfindingNode& comp) const;
};

} /* namespace kingdom */
#endif /* PATHFINDINGNODE_H_ */
