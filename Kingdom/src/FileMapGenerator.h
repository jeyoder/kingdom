/*
 * FileMapGenerator.h
 *
 *  Created on: Sep 25, 2013
 *      Author: crhscs264
 */

#ifndef FILEMAPGENERATOR_H_
#define FILEMAPGENERATOR_H_

#include <fstream>
#include <vector>
#include <iostream>
class FileMapGenerator {
public:
	FileMapGenerator(std::ifstream* stream);
	virtual ~FileMapGenerator();
	std::vector<short> getData();
	int getWidth();
	int getHeight();
private:
	std::ifstream* stream;
	int mapWidth;
	int mapHeight;
	int stringToInt(const std::string& str);
};

#endif /* FILEMAPGENERATOR_H_ */
