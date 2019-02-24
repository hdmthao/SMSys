#include "reader.h"
#include <fstream>

using std::ifstream;

Reader::Reader(string fileName) :
	fileName(fileName)
{ }

vector<vector<string> > Reader::getData() {
	ifstream file(fileName);
	vector<vector<string> > dataList;
	string line = "";

	while (getline(file,line)) {
		vector<string> dataLine;
		string tmp = "";
		for (int i = 0; i < line.length(); ++i) {
			if (line[i] == ',') {
				dataLine.push_back(tmp);
				tmp = "";
			} else {
				tmp += line[i];
			}
		}
		dataList.push_back(dataLine);
	}
	
	file.close();
	return dataList;
}
