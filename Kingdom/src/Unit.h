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
#include "ResourceLoader.h"
namespace kingdom {

class Unit: public Drawable {
private:
	int tileX, tileY;
	int playerNum;

protected:
	virtual void render(SDL_Renderer*, SDL_Window*);
	std::string myImagePlayerSufix;
	std::string myImagePlayerPrefix;
public:
	Unit(int,int,int);
	virtual ~Unit();
	virtual SDL_Texture* getTexture(ResourceLoader* Loader) = 0;
};

} /* namespace kingdom */
#endif /* UNIT_H_ */
