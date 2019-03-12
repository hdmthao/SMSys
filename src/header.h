#ifndef _HEADER_H
#define _HEADER_H

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <math.h>

using namespace std;

enum UserRole {
	Staft,
	Lecture,
	Student
};

struct Account {
	string ID, username, password;
	bool firstTimeLogin;
	UserRole role;
};

class Generator{
private:
	const long long cbase = 127; // const base 127 - 127 is random number 
	const long long cbase2 = 912; // base2
	const long long cmod = 812948195347; // random prime number
	long long cur_hash;
	long long cur_hash2;
public:
	string generatePassword(const string  &pass);
	string generateEmail(const string &lastName, string firstName);
};


class User{
private:
	Generator generator;
	bool isAuthenticated;
public:
	Account* account_;
	User();
	~User();
	bool Login(string userName, string passWord);
	bool FirstTimeLogin(void);
	void CreateAccount(int id, string userName, string password, UserRole role);
	void DeleteAccount(int id);
};
#endif // 
