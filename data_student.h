#ifndef DATA_STUDENT_H
#define DATA_STUDENT_H

#include <string>

using std::string;

struct Student {
	int ID;
	string first_name;
	string last_name;
	string class_name;
	string gender;
	string dob;
	string email;

	Student(int ID, string first_name, string last_name, string class_name, string gender, string dob, string email) :
		ID(ID), first_name(first_name), last_name(last_name), class_name(class_name), gender(gender), dob(dob), email(email)
	{ }
	Student() {};
};

#endif