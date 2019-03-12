#ifndef APP_H
#define APP_H

#include "user.h"
#include <string>

using std::string;



class App {
private:
	User* user;


public:
	App();
	~App();

	bool Login(string userName, string passWord);

};

#endif
