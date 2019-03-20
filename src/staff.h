#ifndef STAFF_H
#define STAFF_H

#include "data_student.h"
#include "data_account.h"

#include <string>
#include <fstream>
#include <vector>
using std::string;
using std::ofstream;
using std::vector;

class Staff {
private:
	bool ClassExisted(const string &);
	bool AddNewClass(const string &); // them 1 class vo database
	void CreateStudent(ofstream &fo_class_student, ofstream &fo_all_student, Student &student, const string &class_name);
	void CreateAccount(ofstream &fo_account, const int &id, const string &user_name, const string &password, const UserRole &role);

public:
	Staff();
	~Staff();
	//For class
	bool ImportClass(const string &class_name, const string &csv);
	void GetClassList(vector <string> &Classes);
	void GetStudentList(vector <Student> &StudentsList, string ClassName);
};

#endif