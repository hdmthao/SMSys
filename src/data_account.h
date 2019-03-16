#ifndef DATA_ACCOUNT_H
#define DATA_ACCOUNT_H

#include <string>

using std::string;

enum UserRole {
	STAFF = 10,
	LECTURER,
	STUDENT
};

struct Account {
	int ID;
	string username;
	string password;
	UserRole role;
	bool firstTimeLogin;
};

#endif
