#ifndef READER_H
#define READER_H

#include <string>
#include <vector>

using std::vector;
using std::string;

class Reader {
	string fileName;

public:
	Reader(string fileName);

	vector<vector<string> > getData();
};

#endif

