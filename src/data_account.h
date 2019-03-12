#ifndef DATA_ACCOUNT_H
#define DATA_ACCOUNT_H
#include <string>
using std::string;
enum UserRole { Staff = 10, Lecturer, Student };
struct Account {
	string ID;
	string username;
	string password;
	UserRole role;
	bool firstTimeLogin;
};
#endif
