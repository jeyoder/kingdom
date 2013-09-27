/*
 * Match.h
 *
 *  Created on: Sep 26, 2013
 *      Author: CRHSCS115
 */

#ifndef MATCH_H_
#define MATCH_H_
#include "Player.h"
#include <vector>

namespace kingdom {
/*Match represents one play match that is going on.
 * would be the base of game logic.
 * would keep track of things such what is the map, who are the players, has someone won, ect
 * would handle functions such as initializing Match's starting properties and progressing things like executing a turn
 */
class Match {
public:
	Match();
	virtual ~Match();
	std::vector<Player> playerLists;
};

} /* namespace std */
#endif /* MATCH_H_ */
