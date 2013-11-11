/*
 * Pawn.h
 *
 *  Created on: Nov 4, 2013
 *      Author: CRHSCS115
 */

#ifndef PAWN_H_
#define PAWN_H_

#include "Unit.h"

namespace kingdom {

class Pawn: public kingdom::Unit {
public:
	Pawn(int,int ,int);
	virtual ~Pawn();
	//void render(SDL_Renderer*, SDL_Window*);
	virtual SDL_Texture* getTexture(ResourceLoader* Loader);
private:
	SDL_Texture* texture;
};

} /* namespace kingdom */
#endif /* PAWN_H_ */
