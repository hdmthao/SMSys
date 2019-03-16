#include "app.h"

#include <iostream>
#include <string>

using std::cerr;
using std::cin;
using std::cout;
using std::string;

App* app = new App();

string getString(string msg) {
	string x;
	cout << msg << " :";
	cin >> x;
	return x;
}

int getInt(string msg) {
	int x;
	cout << msg << " :";
	cin >> x;
	return x;
}


void TestLogin() {
	string userName = getString("Ten Dang nhap");
	string password = getString("matkhau");

	if (app->Login(userName, password)) {
		cout << "Login OK";
	} else {
		cout << "Login Fail";
	}

}

void TestImportClass() {
	string new_class_name = getString("Ten lop moi");
	string csv_name = "18CTT2-Students.csv";

	app->ImportClass(new_class_name, csv_name);
}

int main() {
	
//	TestCreateAccount(2);
//	TestLogin();
	TestImportClass();
}
