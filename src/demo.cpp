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

void TestCreateAccount(int n) {
	int id = 18125130;
	string userName = "";
	string passWord = "";

	while (n > 0) {
		n--;
		id++;
		userName = getString("UserName");
		passWord = getString("password");
		app->CreateAccount(id, userName, passWord, UserRole::Student);	
	}
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

int main() {
	
	// TestCreateAccount(2);
	//TestLogin();
}