//#define WINDOWS
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

#ifndef HELPER_H
#define HELPER_H

#include <string>
#include <fstream>
#include <vector>

using std::string;
using std::ifstream;
using std::ofstream;
using std::vector;

namespace Helper {
	bool isValidFileName(string fileName, string extName);
	string getCurrentWorkingDir();
	bool isEmptyFile(ofstream &file);
	vector<vector<string> > getDataFromFile(string fileName);
	void writeDataToFile(ofstream &fo, vector<string> data);
}

// delete pointer
#define SAFE_DELETE(pointer) \
{ \
	if (pointer) \
	{ \
		delete(pointer); \
		pointer = nullptr; \ 
	} \
} 
#endif
