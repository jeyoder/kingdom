
/*
 * FileMapGenerator.cpp
 *
 *  Created on: Sep 25, 2013
 *      Author: crhscs264
 */

#include "FileMapGenerator.h"
#include <sstream>
#include <iostream>
#include <string>
#include <istream>
using namespace std;
FileMapGenerator::FileMapGenerator(std::ifstream* stream) {
	this->stream = stream;
	this->mapWidth = -1;
	this->mapHeight = -1;
	while (!stream->eof()) {
		std::string line;
		getline(*stream, line);
		size_t pos = line.find_first_of('=');
		string head = line.substr(0, pos);
		if (pos != string::npos) {
			string body = line.substr(pos+1);
			//found an = declaration
			if (head == "width") {
				this->mapWidth = stringToInt(body);
			} else if (head == "height") {
				this->mapHeight = stringToInt(body);
			} else if (head == "data") {
				for(int i=0; i<mapHeight; i++) { // get each line in the data section
					getline(*stream, line);
					std::stringstream row(line);
					string tile;
					while (getline(row, tile, ',')) { //get each individual tile, separated by commas
						this->data.push_back(stringToInt(tile));
					}
				}
			}
		}
	}
}

FileMapGenerator::~FileMapGenerator() {
	// TODO Auto-generated destructor stub
}

std::vector<short> FileMapGenerator::getData() {
	return data;
}

int FileMapGenerator::stringToInt(const string& str) {
	stringstream convert(str);
	int n;
	convert >> n;
	return n;
}

int FileMapGenerator::getWidth() {
	return mapWidth;
}
int FileMapGenerator::getHeight() {
	return mapHeight;
}

