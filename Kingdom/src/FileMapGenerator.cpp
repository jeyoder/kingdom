/*
 * FileMapGenerator.cpp
 *
 *  Created on: Sep 25, 2013
 *      Author: crhscs264
 */

#include "FileMapGenerator.h"
using namespace std;
FileMapGenerator::FileMapGenerator(std::ifstream* stream) {
	this->stream = stream;
}

FileMapGenerator::~FileMapGenerator() {
	// TODO Auto-generated destructor stub
}

std::vector<short> FileMapGenerator::getData() {
		while(!stream->eof()) {
			std::string line;
			getline(*stream, line);
			size_t pos= line.find_first_of('=');
			string head = line.substr(0, pos);
			if (pos != string::npos) {
				string body = line.substr(pos);
				//found an = declaration
				if(head == "width") {
					this->mapWidth = stringToInt(body);
				} else if (head == "height") {
					this->mapHeight = stringToInt(body);
				} else if (head == "data") {
					while(!stream->eof()) {
						getline(*stream, line);

					}
				}
			}
		}
	std::vector<short> data;
	return data;
}

int stringToInt(const string& str) {
	stringstream convert(str);
	int n;
	convert >> n;
	return n;
}

int FileMapGenerator::getWidth() {

}
int FileMapGenerator::getHeight() {

}

