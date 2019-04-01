#ifndef DATA_PROFILE_H
#define DATA_PROFILE_H

#include <string>
#include "data_account.h"
using std::string;

struct Profile {
	string ID;
	UserRole role;
	string fullName;
	string gender;
	string class_name;
	string email;
	string DoB;
};

#endif
