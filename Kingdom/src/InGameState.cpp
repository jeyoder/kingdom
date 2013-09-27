/*



 * InGameState.cpp
 *
 *  Created on: Sep 25, 2013
 *      Author: CRHSCS115
 */

#include "InGameState.h"
#include "AppState.h"
/*The state that is the game is in while actually playing.
 * Would handle low level aspects of actually running the game such as rendering, taking userimput, and some help in coordinating network communication
 * */
namespace kingdom {

InGameState::InGameState() {
	// TODO Auto-generated constructor stub

}
bool InGameState::render(){
	//Render
	//TODO render map
	//TODO render Units
	//TODO render Unit-to-Unit and Unit-to-Map interactions
	//TODO render UI

	return true; //succesful render
}
InGameState::~InGameState() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
