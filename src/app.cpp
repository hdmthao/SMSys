#include "app.h"


App::App() :
	user(nullptr) {
	user = new User();
}


App::~App() {
	delete user;
}


bool App::Login(string userName, string passWord) {
	bool loginStatus = false;

	loginStatus = user->Login(userName, passWord);

	return loginStatus;
}


bool App::Logout() {
	bool logoutStatus = false;

	logoutStatus = user->Logout();

	return logoutStatus;
}


// Cai nay chi de test, sau nay se xoa
void App::CreateAccount(const int &id, const string &userName, const string &passWord, const UserRole &role) {
	user->CreateAccount(id, userName, passWord, role);
}