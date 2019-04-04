#ifndef APP_H
#define APP_H

#include "user.h"
#include "staff.h"
#include "courses.h"
#include "students.h"
#include "lecturers.h"

#include <string>

using std::string;



class App {
private:
	User* user;
	Staff* staff;

public:
	App();
	~App();

	// Init staff account
	void CreateAccount(string &user_name, string &password);
	
	// All User
	bool Login(string userName, string passWord);
	bool Logout();
	UserRole GetUserRole();
	Profile GetProfile();
	bool IsAuthenticated();
	bool IsFirstTimeLogin();
	bool ChangePassword(string &old_password, string &new_password, string &again_password);

	// Staff -> Class
	bool ImportClass(string &class_name, const string &csv_name);
	bool AddNewStudentToClass(const string &class_name, Student &new_student);
	bool EditStudentFromClass(Student &student);
	bool RemoveStudentFromClass(const int &ID);
	bool ChangeStudentFromClassAToB(const int &id, string &class_b);
	bool GetStudent(const int &id, Student &student);
	vector<string> GetClassList();
	vector<Student> GetStudentListFromClass(string &class_name);
	vector<string> GetCsvForClass();
	vector<string> GetCsvForCourse();

	// Staff -> course
	bool ImportCourse(const string &csv_name);
	bool AddNewCourse(Course &new_course, string &class_name, int number_period, Period &period_1, Period &period_2);
	bool AddStudentToCourse(const string &course_id, int student_id);
	bool EditCourse(Course &course);
	Course GetCourseInfo(string &course_id);
	bool RemoveStudentFromCourse(const string &course_id, int student_id);
	bool RemoveCourse(string &course_id);
	vector<string> GetCourseList();
	static vector<string> GetCourseListOfStudent(int &id);
	vector<Student> GetStudentListFromCourse(string &course_name);
	vector<Attendance> GetAttendanceList(string &course_name);
	vector<string> SearchCourse(string &find_id);
	bool ExportScoreboard(string &course_id);
	bool ExportAttendance(string &course_id);

	// Lecturer
	vector<string> LecturerGetCoursesList();
	bool LecturerEditAttendance(int ID, string &course_id, int week, int count);
	vector<Score> Getscoreboard(string &course_id);
	bool LecturerEditGrade(string &course_id, Score &score);
	vector<string> GetCsvForScore();
	bool ImportScore(string &course_id, string &csv_name);
	
	// Student
	string StudentCheckIn();
	vector<Attendance> StudentViewCheckInResult();
	vector<Schedule> StudentGetSchedule();
	vector<Score> StudentViewScoreboard();
};

#endif
