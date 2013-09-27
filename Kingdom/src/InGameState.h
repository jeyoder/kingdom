/*
 * InGameState.h
 *
 *  Created on: Sep 25, 2013
 *      Author: CRHSCS115
 */

#ifndef INGAMESTATE_H_
#define INGAMESTATE_H_

#include "AppState.h"

namespace kingdom {
/*The state that is the game is in while actually playing.
 * Would handle low level aspects of actually running the game such as rendering, taking userimput, and some help in coordinating network communication
 * */
class InGameState: public kingdom::AppState {
public:
	InGameState();
	virtual ~InGameState();
	bool render();
};

} /* namespace std */
#endif /* INGAMESTATE_H_ */b
