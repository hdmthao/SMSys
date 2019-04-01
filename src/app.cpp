#include "app.h"


App::App() :
	user(nullptr) {
	user = new User();
	staff = new Staff();
	courses = new Courses();
}


App::~App() {
	delete user;
	delete staff;
	delete courses;
}


bool App::Login(string user_name, string password) {
	bool login_status = false;

	login_status = user->Login(user_name, password);

	// check role de cap phat instance
	staff = new Staff();

	return login_status;
}


bool App::Logout() {
	bool logout_status = false;

	logout_status = user->Logout();

	delete staff;
	return logout_status;
}


bool App::ImportClass(const string &class_name, const string &csv_name) {
	bool import_status = false;

	import_status = staff->ImportClass(class_name, csv_name);

	return import_status;
}


bool App::AddNewStudentToClass(const string &class_name, Student &new_student) {
	bool add_status = false;

	add_status = staff->AddNewStudentToClass(class_name, new_student);

	return add_status;
}


bool App::ChangeStudentFromClassAToB(const int &id, string &class_b) {
	bool change_status = false;

	change_status = staff->ChangeStudentFromClassAToB(id, class_b);

	return change_status;
}


bool App::RemoveStudentFromClass(const int &ID) {
	bool remove_status = false;

	remove_status = staff->RemoveStudentFromClass(ID);

	return remove_status;
}


bool App::EditStudentFromClass(Student &student) {
	bool edit_status = false;

	edit_status = staff->EditStudentFromClass(student);

	return edit_status;
}


Student App::GetStudent(const int &ID) {
	Student student = staff->GetStudent(ID);

	return student;
}


vector<string> App::GetClassList() {
	vector<string> class_list;

	class_list = staff->GetClassList();

	return class_list;
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

	import_status = courses->ImportCourse(csv_name);

	return import_status;
}


bool App::AddNewCourse(Course &new_course, string &class_name, int number_period, Period &period_1, Period &period_2) {
	bool add_status;

	add_status = courses->AddNewCourse(new_course, class_name, number_period, period_1, period_2);

	return add_status;
}


bool App::AddStudentToCourse(const string &course_id, int student_id) {
	bool add_status = false;

	add_status = courses->AddStudentToCourse(course_id, student_id);

	return add_status;
}


bool App::EditCourse(Course &course) {
	bool edit_status = false;

	edit_status = courses->EditCourse(course);

	return edit_status;
}


Course App::GetCourseInfo(string &course_id) {
	Course course;

	course = courses->GetCourseInfo(course_id);

	return course;
}
bool App::RemoveCourse(string &course_id) {
	bool remove_status = false;

	remove_status = courses->RemoveCourse(course_id);

	return remove_status;
}


bool App::RemoveStudentFromCourse(const string &course_id, int del_student) {
	bool remove_status = false;

	remove_status = courses->RemoveStudentFromCourse(course_id, del_student);

	return remove_status;
}


vector<string> App::GetCsvForCourse() {
	vector<string> lists;

	lists = staff->GetCsvForCourse();

	return lists;
}


vector<string> App::GetCourselist() {
	vector<string> courses_list;

	courses_list = staff->GetCourselist();

	return courses_list;
}


vector<Student> App::GetStudentListFromCourse(string &course_name) {
	vector<Student> students_list;

	students_list = staff->GetStudentListFromCourse(course_name);

	return students_list;
}

vector<Attendance> App::GetAttendanceList(string &course_name) {
	vector<Attendance> Attendance_list;

	Attendance_list = staff->GetAttendanceList(course_name);

	return Attendance_list;
}


vector<string> App::SearchCourse(string &find_id) {
	vector<string> course_list;

	course_list = courses->SearchCourse(find_id);

	return course_list;
}


bool App::ExportScoreboard(string &course_id) {
	bool export_status;

	export_status = courses->ExportScoreboard(course_id);

	return export_status;
}


bool App::ExportAttendance(string &course_id) {
	bool export_status;

	export_status = courses->ExportAttendance(course_id);

	return export_status;
}
vector <Score> App::GetScoreBoard(string&course_name)
{
	vector<Score> ScoreBoard;

	ScoreBoard = staff->GetScoreBoard(course_name);

	return ScoreBoard;
}
bool App::EditAttendance(string course_ID, Attendance a)
{
	bool EditStatus;

	EditStatus = staff->EditAttendance(course_ID, a);

	return EditStatus;
}
bool App::EditGradeOfStudent(string course_ID, Score a)
{
	bool EditStatus;

	EditStatus = staff->EditGradeOfStudent(course_ID, a);

	return EditStatus;
}
Profile App::GetProfile(const string &userName, UserRole role)
{
	Profile a;
	a = user->GetProfile(userName, role);
	return a;
}
vector<string> App::GetLecturerList(string ID)
{
	vector<string> a;
	a = lecturer->GetLecturerList(ID);
	return a;
}
