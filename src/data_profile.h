  
#ifndef DATA_PROFILE_H
#define DATA_PROFILE_H

#include <string>

using std::string;

struct Profile {
	string ID;
	string role;
	string fullName;
	string gender;
	string class_name;
	string email;
	string DoB;
};

#endif