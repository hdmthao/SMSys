#ifndef APP_H
#define APP_H

#include "user.h"
#include "staff.h"

#include <string>

using std::string;



class App {
private:
	User* user;
	Staff* staff;

public:
	App();
	~App();

	// All User
	bool Login(string userName, string passWord);
	bool Logout();

	//Staff
	bool ImportClass(const string &class_name, const string &csv_name);

};

#endif
