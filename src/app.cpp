#include "app.h"


App::App() :
	user(nullptr) {
	user = new User();
}


App::~App() {
	delete user;
}


bool App::Login(string user_name, string password) {
	bool login_status = false;

	login_status = user->Login(user_name, password);

	// check role de cap phat instance
	staff = new Staff();

	return login_status;
}


bool App::Logout() {
	bool logout_status = false;

	logout_status = user->Logout();

	delete staff;
	return logout_status;
}


bool App::ImportClass(const string &class_name, const string &csv_name) {
	bool import_status = false;

	import_status = staff->ImportClass(class_name, csv_name);

	return import_status;
}
