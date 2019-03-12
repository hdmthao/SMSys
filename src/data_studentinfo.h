#ifndef DATA_STUDENTINFO_H
#define DATA_STUDENTINFO_H

#include <string>

using std::string;

struct StudentInfo {
	int ID;
	string firstName;
	string lastName;
	string className;
	string gender;
	string DoB;
	string email;
};

#endif
