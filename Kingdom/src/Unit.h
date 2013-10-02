/*
 * Unit.h
 *
 *  Created on: Sep 30, 2013
 *      Author: CRHSCS115
 */

#ifndef UNIT_H_
#define UNIT_H_

#include "Drawable.h"
#include <string>
namespace kingdom {

class Unit: public Drawable {
private:
	int tileX, tileY;
	int playerNum;
	std::string myImagePlayerSufix;
	std::string myImagePlayerPrefix;
protected:
	virtual void render(SDL_Renderer*, SDL_Window*);
public:
	Unit(int,int,int);
	virtual ~Unit();

};

} /* namespace kingdom */
#endif /* UNIT_H_ */
