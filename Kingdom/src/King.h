/*
 * King.h
 *
 *  Created on: Sep 30, 2013
 *      Author: CRHSCS115
 */

#ifndef KING_H_
#define KING_H_

#include "Unit.h"

namespace kingdom {

class King: public kingdom::Unit {
public:
	King(int,int ,int);
	virtual ~King();
	void render(SDL_Renderer*, SDL_Window*);
};

} /* namespace kingdom */
#endif /* KING_H_ */
