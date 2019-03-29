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

	// Staff -> Class
	bool ImportClass(const string &class_name, const string &csv_name);
	bool AddNewStudentToClass(const string &class_name, Student &new_student);
	bool ChangeStudentFromClassAToB(const int &id, string &class_b);
	bool RemoveStudentFromClass(const int &ID);
	bool EditStudentFromClass(Student &student);
	Student GetStudent(const int &id);
	vector<string> GetClassList();
	vector<Student> GetStudentListFromClass(string &class_name);
	vector<string> GetCsvForClass();
	vector<string> GetCsvForCourse();

	// Staff -> course
	bool ImportCourse(const string &course_id, const string &csv_name);
	bool AddNewCourse(Course &new_course, string &class_name, int number_period, Period &period_1, Period &period_2);
	bool AddStudentToCourse(const string &course_id, int student_id);
	bool EditCourse(Course &course);
	Course GetCourseInfo(string &course_id);
	bool RemoveStudentFromCourse(const string &course_id, int student_id);
	bool RemoveCourse(string &course_id);
	vector<string> GetCourselist();
	vector<Student> GetStudentListFromCourse(string &course_name);
	vector<Attendance> GetAttendanceList(string &course_name);
};

#endif
