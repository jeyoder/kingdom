/*
 * PathfindingNode.cpp
 *
 *  Created on: Oct 29, 2013
 *      Author: crhscs264
 */

#include "PathfindingNode.h"
#include <cmath>
namespace kingdom {
PathfindingNode::PathfindingNode() : waypoint(-1, -1){
	this->scored = false;
	this->totalScore = -1;
	this->pastScore = -1;
}

PathfindingNode::PathfindingNode(WayPoint pt) : waypoint(pt){
	this->scored = false;
	this->totalScore = -1;
	this->pastScore = -1;
}

int PathfindingNode::distanceTo(WayPoint pt) {
	return std::abs(waypoint.getX() - pt.getX()) + std::abs(waypoint.getY() - pt.getY());
}

bool PathfindingNode::operator<(const PathfindingNode& comp) const{ //for binary searching
	if(waypoint.getY() < comp.waypoint.getY()) return true;
	else if (waypoint.getY() > comp.waypoint.getY()) return false;
	else {
		if (waypoint.getX() < comp.waypoint.getX()) return true;
		else return false;
	}
}



PathfindingNode::~PathfindingNode() {
	// TODO Auto-generated destructor stub
}

} /* namespace kingdom */
