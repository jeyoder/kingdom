/*
 * Order.cpp
 *
 *  Created on: Oct 18, 2013
 *      Author: CRHSCS115
 */
#include <iostream>
#include "Order.h"
#include "PathfindingNode.h"
#include <set>
#include <map>
using namespace std;
namespace kingdom {

Order::Order(std::vector<WayPoint> Waypoints, int TurnsTillExecute, TileMap* map) {
	// TODO Auto-generated constructor stub
	this->waypoints = Waypoints;
	this->turnsTillExecute = TurnsTillExecute;
	this->map = map;
	this->activated = false;
}
void Order::decrementTurns(){
	turnsTillExecute--;
}
int Order::getTurnsTillExecute(){
	return turnsTillExecute;
}
WayPoint Order::nextTile(WayPoint currentPos){
	if (waypoints.size() == 0 || waypoints.front() == currentPos) return currentPos;

	vector<WayPoint> path =  aStar(currentPos,waypoints.front());

    return path.size() > 0 ? path.front() : currentPos;
}

void Order::updateStatus(WayPoint currentPos) {
	if(waypoints.size() > 0 && currentPos == waypoints.front()) { //reached goal waypoint
		waypoints.erase(waypoints.begin());
	}
}

bool Order::completed() {
	return (waypoints.size() == 0);
}



Order::Order() {
	this->waypoints = vector<WayPoint>();
	this->turnsTillExecute = 0;
	this->map = nullptr;
	this->activated = false;
}

vector<WayPoint> Order::getPath(WayPoint startPos) {
	return aStar(startPos, waypoints.front()); //TODO: do all waypoints
}

vector<WayPoint> Order::getWayPoints() {
	return waypoints;
}
Order::~Order() {
	// TODO Auto-generated destructor stub
}

vector<WayPoint> Order::aStar(WayPoint from, WayPoint to) {
	std::map<PathfindingNode, PathfindingNode> parent;
	set<PathfindingNode> closedSet;
	set<PathfindingNode> openSet;
	PathfindingNode initialNode = PathfindingNode(from);
	initialNode.pastScore = 0;
	initialNode.totalScore = initialNode.distanceTo(to);
	initialNode.scored = true;
//	cout << "Initial Node: " << from.getX() << ", " << from.getY() << endl;
	openSet.insert(initialNode);
	vector<PathfindingNode> path;

	while(openSet.size() > 0) {
		//find the node with the lowest f score from the open set
		PathfindingNode current = *openSet.begin();
		for(set<PathfindingNode>::iterator it = openSet.begin(); it != openSet.end(); ++it) {
			if((*it).totalScore < current.totalScore) {
				current = *it;
			}
		}
		//cout << "Processing node: " << current.waypoint.getX() << "," << current.waypoint.getY() << endl;
		if(current.waypoint.getX() == to.getX() && current.waypoint.getY() == to.getY()) {
		//	cout << "DONE! found node " << to.getX() << "," << to.getY() << ", rebuilding path..." << endl;
			vector<WayPoint> result;
			PathfindingNode resultNode = current;
			while(resultNode.waypoint != from) {
				result.insert(result.begin(), resultNode.waypoint);
		//		cout << "<= (" << resultNode.waypoint.getX() << "," << resultNode.waypoint.getY() << ")"  << endl;
				resultNode = parent.at(resultNode);
			}
			return result;
		}
		//put that node into the closed set
		openSet.erase(current);
		closedSet.insert(current);

		//iterate through its neighbors
		int curX = current.waypoint.getX();
		int curY = current.waypoint.getY();
			for (int dir=0; dir<4; dir++) {
				int x = curX;
				int y = curY;
				if 		(dir == 0) x--;
				else if (dir == 1) x++;
				else if (dir == 2) y--;
				else if (dir == 3) y++;
				PathfindingNode neighbor(WayPoint(x,y));
				if (!(x == curX && y == curY) && x >= 0 && x < map->getW() && y >=0 && y < map->getH() && closedSet.find(neighbor) == closedSet.end()
					&& map->isTilePassable(x,y) && map->unitAt(x,y) == nullptr) { //if it's actually a neighbor, and not in the closed set
					//cout << "  Processing Neighbor: " << x << "," << y ;

					int possiblePastScore = current.pastScore + 1;
					int possibleTotalScore = possiblePastScore + neighbor.distanceTo(to); //find its probable scores
					//cout << ": probPast = " << possiblePastScore << " propTot = " << possibleTotalScore;
					if(openSet.find(neighbor) == openSet.end() || possibleTotalScore < neighbor.totalScore) { // if the neighbor's already in the open set and has a lower score, we don't care about it
					//	cout << " it's new! key " << neighbor.waypoint.getX() << "," << neighbor.waypoint.getY() << " val" << curX << "," << curY;
						//parent.insert(std::map<PathfindingNode, PathfindingNode>::value_type(neighbor, current));
						parent[neighbor] = current;

						parent.at(neighbor);

						neighbor.pastScore = possiblePastScore;
						neighbor.totalScore = possibleTotalScore;
						if(openSet.find(neighbor) == openSet.end()) {
					//		cout << " ..insert to openSet";
							openSet.insert(neighbor);
						}
					}
		//			cout << endl;
				}
			}
	}
	vector<WayPoint> bad;
	return bad;
}

} /* namespace kingdom */
