#include "app.h"
#include <iostream>
#include <string>

using std::cerr;
using std::cin;
using std::cout;
using std::string;

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

int main() {
	
	system(clear);

	string userName = getString("UserName");
	string passWord = getString("Password");

}
