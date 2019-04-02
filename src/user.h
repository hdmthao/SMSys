#ifndef USER_H
#define USER_H

#include "data_account.h"
#include <string>

using std::string;



class User {
private:
	bool isAuthenticated;
	Account* account;
	
	UserRole FormatIntToRole(int role);

public:
	User();
	~User()
		;
	bool Login(const string &userName, const string &passWord);
	bool Logout();
	bool FirstTimeLogin(void);
	bool ResetPassword(const string &oldPassword, const string &newPassword);
	void DeleteAccount(const int &id);
	int GetStudentID();
};

#endif // 
