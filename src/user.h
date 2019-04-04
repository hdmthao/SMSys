#ifndef USER_H
#define USER_H

#include "data_account.h"
#include "data_profile.h"

#include <string>

using std::string;



class User {
private:
	UserRole FormatIntToRole(int role);

public:
	User();
	~User();

	Account* account;
	bool isAuthenticated;	

	void CreateAccount(string &user_name, string &password);
	
	bool Login(const string &userName, const string &passWord);
	bool Logout();
	bool FirstTimeLogin(void);
	bool ResetPassword(const string &oldPassword, const string &newPassword, const string &again_password);
	void DeleteAccount(const int &id);
	int GetStudentID();
	Profile GetProfile();
};

#endif // 
