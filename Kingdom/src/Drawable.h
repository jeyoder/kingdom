/*
 * Drawable.h
 *
 *  Created on: Sep 20, 2013
 *      Author: crhscs264
 */

#ifndef DRAWABLE_H_
#define DRAWABLE_H_
#include "SDL.h"
#include <string>
#include "ResourceLoader.h"
namespace kingdom {
class Drawable {
private:
	std::string myImage;
public:
	Drawable();
	virtual ~Drawable();
	virtual void render(SDL_Renderer*, SDL_Window*) = 0;
	virtual SDL_Texture* getTexture(ResourceLoader* Loader) = 0;
};

#endif /* DRAWABLE_H_ */
}
