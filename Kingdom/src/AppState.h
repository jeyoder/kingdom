/*
 * AppState.h
 *
 *  Created on: Sep 25, 2013
 *      Author: CRHSCS115
 */

#ifndef APPSTATE_H_
#define APPSTATE_H_

namespace kingdom {
/*Keeps track of what state the program is in
 * ex. InGame, InLobby, InSettings
 */
class AppState {
public:
	AppState();
	virtual ~AppState();
	virtual bool render() = 0; //Abstract method Renders the game state
};

} /* namespace std */
#endif /* APPSTATE_H_ */
