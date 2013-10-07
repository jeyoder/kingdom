/*
 * ResourceLoader.cpp
 *
 *  Created on: Sep 20, 2013
 *      Author: crhscs264
 */
#include <iostream>
#include "ResourceLoader.h"

using namespace std;
ResourceLoader::ResourceLoader(SDL_Renderer* renderer) {
	this->renderer = renderer;
}

ResourceLoader::~ResourceLoader() {

}

SDL_Texture* ResourceLoader::loadTexture(std::string filename) {
	cout << "Texture loading: " << filename << endl;
	SDL_Texture* texture = textureMap[filename];
	if (texture) {
		cout << filename << " found in cache." << endl;
		return textureMap[filename];
	} else {
		cout << filename << " not cached" << endl;
		texture = IMG_LoadTexture(renderer, filename.c_str());
		if(texture) {
			textureMap[filename] = texture;
			cout << filename << " successfully loaded from file" << endl;
			return texture;
		} else {
			cout << filename << " img load failed" << endl;
			return NULL;
		}
	}
}

