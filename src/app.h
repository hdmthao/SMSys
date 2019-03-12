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
	bool Logout();


	// cai nay chi de test, sau nay se xoa
	void CreateAccount(const int &id, const string &userName, const string &passWord, const UserRole &role);
};

#endif
