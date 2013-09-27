/*
 * ResourceLoader.h
 *
 *  Created on: Sep 20, 2013
 *      Author: crhscs264
 */

#ifndef RESOURCELOADER_H_
#define RESOURCELOADER_H_

#include <string>
#include <map>

#include "SDL.h"
#include "SDL_image.h"

class ResourceLoader {
public:
	static ResourceLoader* getInstance(SDL_Renderer* renderer);

	virtual ~ResourceLoader();
	SDL_Texture* loadTexture(std::string filename);
protected:

private:
	static SDL_Renderer* renderer;
	static ResourceLoader* instance;

	ResourceLoader();
	std::map <std::string, SDL_Texture*> textureMap;


};

#endif /* RESOURCELOADER_H_ */
