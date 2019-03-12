#include "header.h"

string Generator::generatePassword(const string  &pass) {
	string result = "";
	cur_hash = 0;
	cur_hash2 = 0; // for cbase2
	for (int i = 0; i < pass.length(); i++) {
		cur_hash = (cur_hash * cbase + pass[i] - '0' + 1) % cmod;
		cur_hash2 = (cur_hash2 * cbase2 + pass[i] - '0' + 1) % cmod;

	}
	while (cur_hash) {
		if (cur_hash % 16 < 10)
			result += (cur_hash % 16 + '0');
		else
			result += (cur_hash % 16 - 10 + 'A');
		cur_hash /= 16;
	}
	while (cur_hash2) {
		if (cur_hash2 % 16 < 10)
			result += (cur_hash2 % 16 + '0');
		else
			result += (cur_hash2 % 16 - 10 + 'A');
		cur_hash2 /= 16;
	}
	return result;
}

string Generator::generateEmail(const string &lastName, string firstName) {
	string result = "";
	for (int i = 0; i < lastName.length(); i++){
		if (lastName[i] >= 65 && lastName[i] <= 90)
			result += lastName[i] + 32;
	}
	firstName[0] += 32;
	result += firstName + "18@apcs.vn";
	return result;
}

User::User() {
	account_ = new Account();
}
User::~User() {
	delete account_;
}
bool User::Login(string userName, string passWord){
	Account cur_acc;
	int cur_role;
	ifstream in;
	in.open("data/account/account.txt");
	while (in >> cur_acc.ID >> cur_acc.username >> cur_acc.password >> cur_role >> cur_acc.firstTimeLogin) {
		//cout << cur_acc.ID << " " << cur_acc.username << " " << cur_acc.password << "\n";
		if (userName == cur_acc.username && generator.generatePassword(passWord) == cur_acc.password) {
			switch(cur_role) {
			case UserRole::Lecture:
				cur_acc.role = UserRole::Lecture;
				break;
			case UserRole::Staft:
				cur_acc.role = UserRole::Staft;
				break;
			case UserRole::Student:
				cur_acc.role = UserRole::Student;
				break;
			default:
				break;
			}
			account_->ID = cur_acc.ID;
			account_->username = cur_acc.username;
			account_->password = cur_acc.password;
			account_->role = cur_acc.role;
			account_->firstTimeLogin = cur_acc.firstTimeLogin;
			in.close();
			return 1;
		}
	}
	in.close();
	return 0;
}

bool User::FirstTimeLogin(void){
	return User::account_->firstTimeLogin;
}

void User::CreateAccount(int id, string userName, string password, UserRole role){
	ofstream out;
	out.open("data/account/account.txt", ios::app);
	out << id << " " << userName << " " << generator.generatePassword(password) << " " << role << " " << 1 << "\n"; // firsttime is true
	out.close();
}

void User::DeleteAccount(int id){

}
