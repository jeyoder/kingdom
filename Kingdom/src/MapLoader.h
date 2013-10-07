/*
 * MapGenerator.h
 *
 *  Created on: Sep 25, 2013
 *      Author: crhscs264
 */

#ifndef MAPGENERATOR_H_
#define MAPGENERATOR_H_

#include <vector>

class MapLoader {
public:
	MapLoader();
	virtual ~MapLoader();

	virtual std::vector<short> getData() = 0;
	virtual int getWidth() = 0;
	virtual int getHeight() = 0;
};

#endif /* MAPGENERATOR_H_ */
