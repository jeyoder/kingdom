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
	ResourceLoader(SDL_Renderer* renderer);
	virtual ~ResourceLoader();
	SDL_Texture* loadTexture(std::string filename);
	static ResourceLoader* getInstance();
	static void initialize(SDL_Renderer* renderer);
protected:

private:
	static ResourceLoader* instance;
	SDL_Renderer* renderer;
	std::map <std::string, SDL_Texture*> textureMap;
};

#endif /* RESOURCELOADER_H_ */
