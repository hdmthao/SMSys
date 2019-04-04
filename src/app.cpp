#include "app.h"
#include <iostream>

App::App() :
	user(nullptr) {
	user = new User();
	staff = new Staff();
}

App::~App() {
	delete user;
	delete staff;
}

void App::CreateAccount(string &user_name, string &password) {
	user->CreateAccount(user_name, password);
}


bool App::Login(string user_name, string password) {
	bool login_status = false;

	login_status = user->Login(user_name, password);

	return login_status;
}

bool App::Logout() {
	bool logout_status = false;

	logout_status = user->Logout();

	return logout_status;
}

UserRole App::GetUserRole() {
	return user->account->role;
}

Profile App::GetProfile() {
	Profile profile;

	profile = user->GetProfile();

	return profile;
}

bool App::IsAuthenticated() {
	return user->isAuthenticated;
}

bool App::IsFirstTimeLogin() {
	return user->account->firstTimeLogin;
}

bool App::ChangePassword(string &old_password, string &new_password, string &again_password) {
	bool change_status = false;

	change_status = user->ResetPassword(old_password, new_password, again_password);

	return change_status;
}

bool App::ImportClass(string &class_name, const string &csv_name) {
	bool import_status = false;

	import_status = Staff::ImportClass(class_name, csv_name);

	return import_status;
}

bool App::AddNewStudentToClass(const string &class_name, Student &new_student) {
	bool add_status = false;

	add_status = Staff::AddNewStudentToClass(class_name, new_student);

	return add_status;
}

bool App::EditStudentFromClass(Student &student) {
	bool edit_status = false;

	edit_status = Staff::EditStudentFromClass(student);

	return edit_status;
}

bool App::RemoveStudentFromClass(const int &ID) {
	bool remove_status = false;

	remove_status = Staff::RemoveStudentFromClass(ID);

	return remove_status;
}

bool App::ChangeStudentFromClassAToB(const int &id, string &class_b) {

	bool change_status = false;

	change_status = Staff::ChangeStudentFromClassAToB(id, class_b);

	return change_status;
}

vector<string> App::GetClassList() {
	vector<string> class_list;
	
	class_list = Staff::GetClassList();
	
	return class_list;
}

bool App::GetStudent(const int &ID, Student &student) {
	bool get_status = false;
	
	get_status = Staff::GetStudent(ID, student);

	return get_status;
}

vector<Student> App::GetStudentListFromClass(string &class_name) {
	vector<Student> students_list;
	
	students_list = staff->GetStudentListFromClass(class_name);
	
	return students_list;
}

vector<string> App::GetCsvForClass() {
	vector<string> lists;

	lists = staff->GetCsvForClass();

	return lists;
}

bool App::ImportCourse(const string &csv_name) {
	bool import_status;
	
	import_status = Courses::ImportCourse(csv_name);

	return import_status;
}

bool App::AddNewCourse(Course &new_course, string &class_name, int number_period, Period &period_1, Period &period_2) {
	bool add_status;

	add_status = Courses::AddNewCourse(new_course, class_name, number_period, period_1, period_2);

	return add_status;
}

bool App::EditCourse(Course &course) {
	bool edit_status = false;

	edit_status = Courses::EditCourse(course);

	return edit_status;
}

bool App::RemoveCourse(string &course_id) {
	bool remove_status = false;

	remove_status = Courses::RemoveCourse(course_id);

	return remove_status;
}

bool App::RemoveStudentFromCourse(const string &course_id, int del_student) {
	bool remove_status = false;

	remove_status = Courses::RemoveStudentFromCourse(course_id, del_student);

	return remove_status;
}


bool App::AddStudentToCourse(const string &course_id, int student_id) {
	bool add_status = false;

	add_status = Courses::AddStudentToCourse(course_id, student_id);

	return add_status;
}


vector<string> App::GetCourseList() {
	vector<string> courses_list;

	courses_list = Courses::GetCourseList();

	return courses_list;
}


vector<Student> App::GetStudentListFromCourse(string &course_name) {
	vector<Student> students_list;

	students_list = Staff::GetStudentListFromCourse(course_name);

	return students_list;
}


vector<Attendance> App::GetAttendanceList(string &course_name) {
	vector<Attendance> Attendance_list;

	Attendance_list = Staff::GetAttendanceList(course_name);

	return Attendance_list;
}


Course App::GetCourseInfo(string &course_id) {
	Course course;

	course = Courses::GetCourseInfo(course_id);

	return course;
}


vector<string> App::GetCsvForCourse() {
	vector<string> lists;

	lists = Staff::GetCsvForCourse();

	return lists;
}


vector<string> App::GetCourseListOfStudent(int &id) {
	vector<string> list;

	list = Students::GetCourseList(id);

	return list;
}



vector<string> App::SearchCourse(string &find_id) {
	vector<string> course_list;

	course_list = Courses::SearchCourse(find_id);

	return course_list;
}


bool App::ExportScoreboard(string &course_id) {
	bool export_status;

	export_status = Courses::ExportScoreboard(course_id);

	return export_status;
}


bool App::ExportAttendance(string &course_id) {
	bool export_status;

	export_status = Courses::ExportAttendance(course_id);

	return export_status;
}


vector<string> App::LecturerGetCoursesList() {
	vector<string> list;

	string name = user->account->username;

	list = Lecturers::GetCoursesList(name);
	
	return list;
}

bool App::LecturerEditGrade(string &course_id, Score &score) {
	bool edit_status;

	edit_status = Lecturers::EditGrade(course_id, score);

	return edit_status;
}

bool App::LecturerEditAttendance(int ID, string &course_id, int week, int count) {
	bool edit_status;

	edit_status = Lecturers::EditAttendance(ID, course_id,week,count);

	return edit_status;
}


vector<Score> App::Getscoreboard(string &course_id) {
	vector<Score> scoreboard;

	scoreboard = staff->GetScoreBoard(course_id);
	
	return scoreboard;
}

vector<string> App::GetCsvForScore() {
	vector<string> list;

	list = Lecturers::GetCsvForScore();

	return list;
}

bool App::ImportScore(string &course_id, string &csv_name) {
	bool import_status = false;

	import_status = Lecturers::ImportScoreboard(course_id, csv_name);

	return import_status;
}


string App::StudentCheckIn() {
	string check_in_status = "";

	int ID = this->user->GetStudentID();

	check_in_status = Students::CheckIn(ID);

	return check_in_status;
}


vector<Attendance> App::StudentViewCheckInResult() {
	vector<Attendance> atten;
	int ID = this->user->GetStudentID();

	atten = Students::ViewCheckInResult(ID);

	return atten;
}


vector<Schedule> App::StudentGetSchedule() {
	vector<Schedule> schedule;
	int ID = this->user->GetStudentID();
	schedule = Students::GetSchedule(ID);

	return schedule;

}

vector<Score> App::StudentViewScoreboard() {
	vector<Score> scoreboard;
	int ID = this->user->GetStudentID();
	scoreboard = Students::ViewScore(ID);

	return scoreboard;
}