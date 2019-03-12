#include "app.h"



App::App() :
	user(nullptr) {
	user = new user();
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
