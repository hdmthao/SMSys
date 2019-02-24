#ifndef CLASS_H
#define CLASS_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using std::vector;
using std::string;
using std::ifstream;
using std::ofstream;
using std::to_string;

class Class {
public:
	vector<string> importStudent(string fileName, string className);
	vector<string> setAccount(string id, string className, string name, string password, bool firstTimeLogin);
};

#endif
