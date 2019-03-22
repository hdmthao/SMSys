#ifndef APP_H
#define APP_H

#include "user.h"
#include "staff.h"
#include "courses.h"

#include <string>

using std::string;



class App {
private:
	User* user;
	Staff* staff;
	Courses* courses;
		
public:
	App();
	~App();

	// All User
	bool Login(string userName, string passWord);
	bool Logout();

	//Staff
	bool ImportClass(const string &class_name, const string &csv_name);
	bool AddNewStudent(const string &class_name, Student &new_student);
	bool ChangeStudentFromClassAToB(const int &id, string &class_b);
	bool RemoveStudent(const int &ID);
	bool EditStudent(Student &student);
	Student GetStudent(const int &id);
	vector<string> GetClassList();
	vector<Student> GetStudentList(string &class_name);
	vector<string> GetCsvForClass();
	vector<string> GetCsvForCourse();

	//Courses
	bool ImportCourse(const string &course_id, const string &csv_name);
};

#endif
