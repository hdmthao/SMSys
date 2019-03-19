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


bool App::AddNewStudent(const string &class_name, Student &new_student) {
	bool add_status = false;

	add_status = staff->AddNewStudent(class_name, new_student);

	return add_status;
}


bool App::ChangeStudentFromClassAToB(const int &id, string &class_b) {
	bool change_status = false;

	change_status = staff->ChangeStudentFromClassAToB(id, class_b);

	return change_status;
}


bool App::RemoveStudent(const int &ID) {
	bool remove_status = false;

	remove_status = staff->RemoveStudent(ID);

	return remove_status;
}


bool App::EditStudent(Student &student) {
	bool edit_status = false;

	edit_status = staff->EditStudent(student);

	return edit_status;
}

Student App::GetStudent(const int &ID) {
	Student student = staff->GetStudent(ID);

	return student;
}