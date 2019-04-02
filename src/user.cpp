#include "user.h"
#include "generator.h"
#include "path.h"
#include "helper.h"

#include <fstream>
#include <vector>
#include <iostream>

using std::ifstream;
using std::ofstream;
using std::ios;
using std::vector;

User::User() :
	isAuthenticated(false), account(nullptr)
{ }


User::~User() {
	delete account;
}


bool User::Login(const string &userName, const string &passWord) {
	Account cur_acc;
	int cur_role;
	ifstream in;

	in.open(Path::ACCOUNT);

	while (in >> cur_acc.ID >> cur_acc.username >> cur_acc.password >> cur_role >> cur_acc.firstTimeLogin) {
		if (userName == cur_acc.username && Generator::generatePassword(passWord) == cur_acc.password) {
			cur_acc.role = Helper::FormatIntToRole(cur_role);
			this->isAuthenticated = true;
			this->account = new Account();
			this->account->ID = cur_acc.ID;
			this->account->username = cur_acc.username;
			this->account->password = cur_acc.password;
			this->account->role = cur_acc.role;
			this->account->firstTimeLogin = cur_acc.firstTimeLogin;
			in.close();
			return true;
		}
	}

	in.close();

	return false;
}

int User::GetStudentID() {
	// if (this->account->role != UserRole::STUDENT) {
	// 	return 0;
	// }
	return this->account->ID;
}


bool User::Logout() {
	if (!this->isAuthenticated) return false;

	delete account;
	this->isAuthenticated = false;
	
	return true;

}


bool User::FirstTimeLogin(void){
	return this->account->firstTimeLogin;
}


bool User::ResetPassword(const string &oldPassword, const string &newPassword){
	vector <Account> ListAcc;
	Account cur_acc;
	int cur_role;
	bool resetStatus = false;

	ifstream in;
	in.open(Path::ACCOUNT);
	
	while (in >> cur_acc.ID >> cur_acc.username >> cur_acc.password >> cur_role >> cur_acc.firstTimeLogin) {
		if (this->account->ID == cur_acc.ID && cur_acc.password == Generator::generatePassword(oldPassword)) {
			cur_acc.password = Generator::generatePassword(newPassword);
			resetStatus = true;
		}
		cur_acc.role = Helper::FormatIntToRole(cur_role);
		ListAcc.push_back(cur_acc);
	}
	
	in.close();

	if (!resetStatus) {
		return false;
	}

	ofstream out;
	out.open(Path::ACCOUNT);

	while (!ListAcc.empty()) {
		out << ListAcc.back().ID << " " << ListAcc.back().username << " " << ListAcc.back().password << " " << ListAcc.back().role << " " << ListAcc.back().firstTimeLogin << "\n";
		ListAcc.pop_back();
	}

	out.close();

	return true;
}