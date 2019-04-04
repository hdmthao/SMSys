#include "app.h"
#include "helper.h"

#include <iostream>
#include <string>
#include <limits>
#include <iomanip>

using std::cerr;
using std::cin;
using std::cout;
using std::string;
using std::setw;
using std::left;
using std::setfill;
using std::pair;
using std::make_pair;

App* app = new App();

string getString(string msg) {
	string x;
	cout << msg << " :";
	getline(cin, x);
	// cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return x;
}

int getInt(string msg) {
	int x;
	cout << msg << " :";
	cin >> x;
	// cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	return x;
}

void PressToContinue() {
	cout << "Press enter to continue";
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Header() {
	cout << setfill('-') << setw(135) << "\n";
	cout << setfill(' ') << "\n";
}

void ShowStudentInfo(Student &student) {
	cout << "| " << setw(15) << left << "ID";
	cout << "| " << setw(25) << left << "Last name";
	cout << "| " << setw(10) << left << "First name";
	cout << "| " << setw(10) << left << "Class";
	cout << "| " << setw(10) << left << "Gender";
	cout << "| " << setw(15) << left << "DoB";
	cout << "| " << setw(25) << left << "Email";
	cout << "| " << setfill('-') << setw(130) << "\n";
	cout << setfill(' ') << "\n";
	string tmp_last_name = student.last_name;
	Helper::ConvertStringToSpace(tmp_last_name);
	cout << "| " << setw(15) << left << student.ID;
	cout << "| " << setw(25) << left << tmp_last_name;
	cout << "| " << setw(10) << left << student.first_name;
	cout << "| " << setw(10) << left << student.class_name;
	cout << "| " << setw(10) << left << student.gender;
	cout << "| " << setw(15) << left << student.dob;
	cout << "| " << setw(25) << left << student.email;
	cout << "\n\n";
}

void ShowCourseInfo(Course &course) {
	cout << "| " << setw(15) << left << "ID";
	cout << "| " << setw(35) << left << "Course name";
	cout << "| " << setw(15) << left << "Lecturer";
	cout << "| " << setw(15) << left << "Start Date";
	cout << "| " << setw(15) << left << "End Date";

	cout << "| " << setfill('-') << setw(95) << "\n";
	cout << setfill(' ') << "\n";
	string tmp_name = course.name;
	Helper::ConvertStringToSpace(tmp_name);
	cout << "| " << setw(15) << left << course.ID;
	cout << "| " << setw(35) << left << tmp_name;
	cout << "| " << setw(15) << left << course.lecturer;
	cout << "| " << setw(15) << left << course.start_date;
	cout << "| " << setw(15) << left << course.end_date;

	cout << "\n\n";
}

void ShowStudentListInfo(vector<Student> &student_list) {
	cout << setw(12) << left << "ID" << setw(25) << left <<  "Full Name" << setw(9) << left << "Gender" <<
	setw(15) << left << "Day Of Birth" << setw(25) << left << "Email" << "\n";
	cout << setfill('-') << setw(80) << "-" << "\n";
	cout << setfill(' ');
	for (int i = 0; i < student_list.size(); ++i) {
		cout << setw(12) << left << student_list[i].ID;
		cout << setw(25) << left << Helper::GetFullName(student_list[i].first_name, student_list[i].last_name);
		cout << setw(9) << left << student_list[i].gender;
		cout << setw(15) << left << student_list[i].dob;
		cout << setw(25) << left << student_list[i].email;
		cout << "\n";
	}
	cout << setfill('-') << setw(80) << "-" << "\n";
	cout << setfill(' ') << "\n";

}

void ShowAttendanceList(vector<Attendance> &Attendance_list) {

	cout << setw(12) << left << "ID" << setw(25) << left <<  "Full Name";
	for (int i = 0; i < 10; ++i) {
		string week = "";
		if (i < 9) week = "Week-0" + std::to_string(i); else week = "Week-10";
		cout << setw(10) << left << week;
	}
	cout << "\n";
	cout << setfill('-') << setw(135) << "-" << "\n";
	cout << setfill(' ');
	for (int i = 0; i < Attendance_list.size(); ++i) {
		cout << setw(12) << left << Attendance_list[i].ID;
		cout << setw(25) << left << Helper::GetFullName(Attendance_list[i].first_name, Attendance_list[i].last_name);
		for (int k = 0; k < Attendance_list[i].week.size(); k++)
		{
			string tmp = std::to_string(Attendance_list[i].week[k]) + "/2";
			cout << setw(10) << left << tmp;
		}
		cout << "\n";
	}
	cout << setfill('-') << setw(135) << "-" << "\n";
	cout << setfill(' ') << "\n";
	cout << "\n";
}

void ShowScoreboard(vector<Score> &scoreboard) {

	cout << "| " << setw(13) << left << "Student ID";
	cout << "| " << setw(35) << left << "Full Name";
	cout << "| " << setw(10) << left << "MIDTERM";
	cout << "| " << setw(10) << left << "LAB";
	cout << "| " << setw(10) << left << "BONUS";
	cout << "| " << setw(10) << left << "FINAL";
	cout << "| " << setw(10) << left << "ABCF";
	cout << "| " << setw(10) << left << "GPA";
	cout << "|\n"; 
	cout << setfill('-') << setw(124) << "";
	cout << setfill(' ') << "\n";
	for (int i = 0; i < scoreboard.size(); ++i) {
		cout << "| " << setw(13) << left << scoreboard[i].ID;
		cout << "| " << setw(35) << left << Helper::GetFullName(scoreboard[i].first_name, scoreboard[i].last_name);
		cout << "| " << setw(10) << left << scoreboard[i].mid_term;
		cout << "| " << setw(10) << left << scoreboard[i].lab;
		cout << "| " << setw(10) << left << scoreboard[i].bonus;
		cout << "| " << setw(10) << left << scoreboard[i].final_term;
		cout << "| " << setw(10) << left << scoreboard[i].ABCF;
		cout << "| " << setw(10) << left << scoreboard[i].GPA;
		cout << "|\n";
		cout << setfill('-') << setw(124) << "";
		cout << setfill(' ') << "\n";
	}
	cout << "\n";


}
// TEST OK
void TestLogin() {
	Header();
	cout << ">> You must login first\n";
	cout << "[RUN] Login\n\n";

	string userName = getString("Username");
	string password = getString("Password");
	
	cout << "\n";
	if (app->Login(userName, password)) {
		cout << ">> You were login as ";
		UserRole role = app->GetUserRole();
		switch (role) {
			case UserRole::STAFF:
				cout << "staff";
				break;
			case UserRole::LECTURER:
				cout << "lecturer";
				break;
			case UserRole::STUDENT:
				cout << "student";
				break;
			default:
				break;
		}
		cout << "\n";
		if (app->IsFirstTimeLogin()) {
			cout << "\nIt is the first time you login. You need to change password\n\n";
			while (1) {
				string old_password = getString("Old password");
				string new_password = getString("New password");
				string again_password = getString("Retype password");

				if (app->ChangePassword(old_password, new_password, again_password)) {
					break;
				}
				cout << ">> Something wrong! Please do it again\n";
			}
		}
	} else {
		cout << ">> Wrong username or password\n";
	}

	cout << "\n";
	cout << "[DONE] Login\n";
	PressToContinue();
}

// TEST OK
void TestLogout() {
	Header();
	cout << "[RUN] Logout\n\n";

	if (app->Logout()) {
		cout << ">> You were logout\n";
	} else {
		cout << ">> Something wrong when logout\n";
	}

	cout << "\n";
	cout << "[DONE] Logout\n";
	cout << "Press any key to continue";
	cin.ignore();
}

// TEST OK
void TestChangePassword() {
	Header();
	cout << "[RUN] Change Password\n\n";
	
	string old_password = getString("Old password");
	string new_password = getString("New password");
	string again_password = getString("Retype new password");

	if (app->ChangePassword(old_password, new_password, again_password)) {
		cout << ">> Change password successfully\n";
	} else {
		cout << ">> Something wrong when change password\n";
	}
	
	cout << "\n";
	cout << "[DONE] Change Password\n";
	cout << "Press any key to continue";
	cin.ignore();
}

// TEST OK
void TestViewProfile() {
	Header();
	cout << "[RUN] View profile\n\n";

	Profile profile;
	profile = app->GetProfile();

	cout << "| " << setw(15) << left << "ID";
	cout << "| " << setw(35) << left << "Full name";
	cout << "| " << setw(15) << left << "Role";
	cout << "| " << setw(10) << left << "Class";
	cout << "| " << setw(10) << left << "Gender";
	cout << "| " << setw(15) << left << "DoB";
	cout << "| " << setw(25) << left << "Email";

	cout << "| " << setfill('-') << setw(140) << "\n";
	cout << setfill(' ') << "\n";
	cout << "| " << setw(15) << left << profile.ID;
	cout << "| " << setw(35) << left << profile.fullName;
	cout << "| " << setw(15) << left << profile.role;
	cout << "| " << setw(10) << left << profile.class_name;
	cout << "| " << setw(10) << left << profile.gender;
	cout << "| " << setw(15) << left << profile.DoB;
	cout << "| " << setw(25) << left << profile.email;
	cout << "\n\n";

	cout << "[DONE] View profile\n\n";
	cout << "Press any key to continue";
	cin.ignore();
}

// TEST OK
void TestImportClass() {
	Header();
	cout << "[RUN] Import class\n\n";

	vector<string> list_import = app->GetCsvForClass();
	cout << ">> List Of CSV file\n\n";
	for (int i = 0; i < list_import.size(); ++i) {
		cout << i + 1 << ". " << list_import[i] << "\n";
	}
	cout << "0. Back\n";
	cout << "\n";
	int id = getInt("Enter index CSV file you wanna import");
	if (id < 0 || id > list_import.size()) {
		cout << "Something wrong when import\n";
	} else if (id == 0) {
		return;
	} else {
		string new_class_name = getString("Enter class ID");

		cout << "\n";
		if (app->ImportClass(new_class_name, list_import[id - 1])) {
			cout << ">> Import student from CSV file to class " + new_class_name + " sucessfully\n";
		} else {
			cout << ">> Something wrong when import class\n";
		}

		cout << "\n";
		cout << "[DONE] Import class\n";
		cout << "Press enter to continue";
		PressToContinue();
	}
}

// TEST OK
void TestAddNewStudentToClass() {
	Header();
	cout << "[RUN] Manually add a new student to a class\n\n";

	vector<string> list_class = app->GetClassList();
	cout << ">> List of class\n\n";
	for (int i = 0; i < list_class.size(); ++i) {
		cout << i + 1 << ". " << list_class[i] << "\n";
	}
	cout << "0. Back\n";
	cout << "\n";

	int id = getInt("Enter index of class you wanna to add a new student");

	if (id < 0 || id > list_class.size()) {
		cout << "Something wrong when choose index of class\n";
	} else if (id == 0) {
		return;
	} else {
		cout << "\n";
		cout << ">> Get information for new student\n";
		Student new_student;
		new_student.ID = getInt("Enter ID");
		new_student.first_name = getString("Enter first name");
		new_student.last_name = getString("Enter last name");
		new_student.gender = getString("Enter gender (\'male\'/\'female\')");
		new_student.dob = getString("Enter DoB (\'dd\'/\'mm\'/\'yyyy\'");
		new_student.class_name = list_class[id - 1];
		cout << "\n";

		if (app->AddNewStudentToClass(list_class[id - 1], new_student)) {
			ShowStudentInfo(new_student);
			cout << ">> Add new student to class " << list_class[id - 1] << " succesfullly\n";
		} else {
			cout << ">> Something wrong when add new student to class " << list_class[id - 1] << "\n";
		}

	}

	cout << "\n";
	cout << "[DONE] Manually add a new student to a class\n";
	PressToContinue();
}


void TestEditStudentFromClass() {
	Header();
	cout << "[RUN] Edit an existing student\n\n";
	int id = getInt("Enter ID of student wanna edit");

	Student student;
	bool exist_student = app->GetStudent(id, student);
	
	if (!exist_student) {
		cout << "\n";
		cout << ">> Not exist student " << id << "\n";
	} else {
		ShowStudentInfo(student);
		cout << ">> If you don't want to edit a field, please give it blank and press enter\n\n";
		string first_name = getString("Enter new first name");
		if (first_name != "") student.first_name = first_name;
		string last_name = getString("Enter new last name");
		if (last_name != "") student.last_name = last_name;
		string gender = getString("Enter new gender (\'male\'/\'female\'");
		if (gender != "") student.gender = gender;
		string dob = getString("Enter new DoB (\'dd\'/\'mm\'/\'yyyy\'");
		if (dob != "") student.dob = dob;
		string email = getString("Enter new email:");
		if (email != "") student.email = email;

		if (app->EditStudentFromClass(student)) {
			cout << "\n";
			cout << ">> Edit student " << id << " succesfully\n";
		} else {
			cout << "\n";
			cout << ">> Something wrong when edit student\n";
		}
	}
	cout << "\n";
	cout << "[DONE] Edit an existing student\n";
	PressToContinue();
}


void TestRemoveStudentFromClass() {
	Header();
	cout << "[RUN] Remove student from class\n\n";
	int id;
	id = getInt("Enter ID of student wanna remove");

	Student student;
	bool exist_student = app->GetStudent(id, student);

	if (!exist_student) {
		cout << "\n";
		cout << ">> Not exist student " << id << "\n";
	} else {
		ShowStudentInfo(student);
		if (app->RemoveStudentFromClass(id)) {
			cout << "\n";
			cout << ">> Remove student " << id << " succesfully\n";;
		} else {
			cout << ">> Something wrong when remove student\n";
		}
	}

	cout << "\n";
	cout << "[DONE] TEST REMOVE STUDENT FROM CLASS\n";
	cout << "Press enter to continue";
	cin.ignore();
}

// TEST OK
void TestChangeStudent() {
	Header();
	cout << "[RUN] Change student between two class\n\n";
	int id;
	id = getInt("Enter ID student you wanna to move");

	cout << ">> Class list\n\n";
	vector<string> class_list = app->GetClassList();
	for (int i = 0; i < class_list.size(); ++i) {
		cout << i + 1 << ". " << class_list[i] << "\n";
	}
	cout << "\n";
	int id_class = getInt("Enter index of class you wanna to move student to");

	if (id_class <= 0 || id_class > class_list.size()) {
		cout << "Something wrong when choose index of class\n";
	} else {
		if (app->ChangeStudentFromClassAToB(id, class_list[id_class - 1])) {
			cout << "\n";
			cout << ">> Change student " << id << " to class " << class_list[id_class - 1] << " successfully\n";
		} else {
			cout << "\n";
			cout << ">> Something wrong when move student " << id << " to class " << class_list[id_class - 1];
		}
	}

	cout << "\n";
	cout << "[DONE] Change student between two class\n\n";
	PressToContinue();
}

// TEST OK
void TestViewListClass() {
	Header();
	cout << "[RUN] View list class\n\n";

	vector<string> class_list;
	class_list = app->GetClassList();
	cout << ">> Class list\n\n";
	for (int i = 0; i < class_list.size(); ++i) {
		cout <<i + 1 << ". " << class_list[i] << "\n";
	}
	cout << "\n";
	cout << "[DONE] View list class\n";
	cout << "Press enter to continue\n";
	cout << "\n";
	cout << "### TEST VIEW LIST STUDENT\n";

	int id = getInt("Index Class");
	vector<Student> students_list;

	students_list = app->GetStudentListFromClass(class_list[id - 1]);
	cout << ">> List Student Of Class " << class_list[id - 1] << "\n";
	cout << "\n";

	cout << "[OK] View List Student OK\n";
}

// TEST OK
void TestViewListStudentOfAClass() {
	Header();
	cout << "[RUN] View list student of a class\n\n";

	vector<string> class_list;
	class_list = app->GetClassList();

	cout << ">> Class list\n\n";

	for (int i = 0; i < class_list.size(); ++i) {
		cout << i + 1 << ". " << class_list[i] << "\n";
	}
	cout << "\n";
	int id = getInt("Enter index of class wanna view student list");

	if (id <= 0 || id >= class_list.size()) {
		cout << "\n";
		cout << ">> Something wrong when choose index of class\n";
	} else {
		vector<Student> student_list;

		student_list = app->GetStudentListFromClass(class_list[id - 1]);
		cout << "\n";
		cout << ">> List student of class " << class_list[id - 1] << "\n\n";
		ShowStudentListInfo(student_list);
	}

	cout << "\n";
	cout << "[DONE] View list student of a class\n\n";
	PressToContinue();
}

// TEST OK
void TestImportCourse() {
	Header();
	cout << "[RUN] Import course\n\n";

	vector<string> list_import = app->GetCsvForCourse();
	cout << ">> List of csv file to import\n";
	cout << "\n";

	for (int i = 0; i < list_import.size(); ++i) {
		cout << i + 1 << ". " << list_import[i] << "\n";
	}
	cout << "\n";
	int id = getInt("Enter index csv file you wanna import");

	if (id <= 0 || id > list_import.size()) {
		cout << "\n";
		cout << "Something wrong when choose index file to import\n";
	} else {
		if (app->ImportCourse(list_import[id - 1])) {
			cout << "\n";
			cout << ">> Import course successfully\n";
		} else {
			cout << "\n";
			cout << ">> Something wrong when import course\n";
		}
	}

	cout << "\n";
	cout << "[DONE] Import course\n";
	PressToContinue();
}

// TEST OK
void TestAddNewCourse() {
	Header();
	cout << "[RUN] Manually add new course\n\n";

	Course new_course;
	cout << ">> Get info of new course\n";
	new_course.ID = getString("Enter course ID");
	new_course.name = getString("Enter course name");
	new_course.lecturer = getString("Enter lecturer");
	string class_name = getString("Enter class name");
	new_course.start_date = getString("Enter start date (\'dd\'/\'mm\'/\'yyyy\')");
	new_course.end_date = getString("Enter end date (\'dd\'/\'mm\'/\'yyyy\')");

	int number_period = 2;
	Period period_1, period_2;
	period_1.dow = getInt("Day of week for period 1");
	period_1.shift = getInt("Shift for period 1");
	period_1.room = getString("Room for period 1");
	if (number_period == 2) {
		period_2.dow = getInt("Day of week for period 2");
		period_2.shift = getInt("Shift for period 2");
		period_2.room = getString("Room for period 2");
	}

	if (app->AddNewCourse(new_course, class_name, number_period, period_1, period_2)) {
		cout << "\n";
		cout << ">> Add new course " << new_course.ID << " successfully\n";
	} else {
		cout << "\n";
		cout << ">> Something wrong when add new course " << new_course.ID << "\n";
	}

	cout << "\n";
	cout << "[DONE] Manually add new course\n";
	PressToContinue();
}


void TestEditCourses() {
	Header();
	cout << "[RUN] Edit an exist course\n\n";

	vector<string> course_list;
	course_list = app->GetCourseList();

	cout << ">> Course list\n\n";
	for (int i = 0; i < course_list.size(); ++i) {
		cout << i + 1 << ". " << course_list[i] << "\n";
	}
	cout << "\n";

	int id = getInt("Enter index course wanna edit");

	if (id < 0 || id > course_list.size()) {
		cout << "\n";
		cout << ">> Something wrong when choose index of course to edit\n";
	} else {
		Course course = app->GetCourseInfo(course_list[id - 1]);
		cout << "\n";
		ShowCourseInfo(course);

		cout << ">> If you don't want to edit a field, please give it blank and press enter\n\n";
		string name = getString("Enter new course name");
		if (name != "") course.name = name;
		string start_date = getString("Enter new start date");
		if (start_date != "") course.start_date = start_date;
		string end_date = getString("Enter new end date");
		if (end_date != "") course.end_date = end_date;

		if (app->EditCourse(course)) {
			cout << "\n";
			cout << ">> Edit course " << course.ID << " successfully\n";
		} else {
			cout << "\n";
			cout << ">> Something wrong when edit " << course.ID << "\n";
		}
	}

	cout << "\n";
	cout << "[DONE] Test Edit an exist course\n";
	PressToContinue();
}

// TEST OK
void TestRemoveCourse() {
	Header();
	cout << "[RUN] Remove a course\n\n";

	vector<string> course_list;
	course_list = app->GetCourseList();
	cout << ">> Course list\n\n";
	for (int i = 0; i < course_list.size(); ++i) {
		cout << i + 1 << ". " << course_list[i] << "\n";
	}
	cout << "\n";

	int id = getInt("Enter index course wanna remove");

	if (id < 0 || id > course_list.size()) {
		cout << "\n";
		cout << "Something wrong when choose index course to remove\n";
	} else {
		if (app->RemoveCourse(course_list[id - 1])) {
			cout << "\n";
			cout << ">> Remove course " << course_list[id - 1] << " successfully\n";
		} else {
			cout << "\n";
			cout << ">> Something wrong when remove course " << course_list[id - 1] << "\n";
		}
	}

	cout << "\n";
	cout << "[DONE] Remove a course\n";
	PressToContinue();
}

// TEST OK
void TestRemoveStudentFromCourse() {
	Header();
	cout << "[RUN] Remove student from course\n\n";

	int del_student = getInt("Enter student ID wanna to remove");

	vector<string> course_list = app->GetCourseListOfStudent(del_student);
	
	for (int i = 0; i < course_list.size(); ++i) {
		cout << i + 1 << ". " << course_list[i] << "\n";
	}
	cout << "\n";

	int id = getInt("Enter index course wanna to remove student in this");
	
	if (id < 0 || id > course_list.size()) {
		cout << "\n";
		cout << "Something wrong when choose index course\n";
	} else {
		if (app->RemoveStudentFromCourse(course_list[id - 1], del_student)) {
			cout << "\n";
			cout << ">> Remove student id " << del_student << " from course " << course_list[id - 1] << " sucessfully\n";
		} else {
			cout << "\n";
			cout << ">> Something wrong when remove studnent id " << del_student << " in course " << course_list[id - 1] << "\n";
		}
	}

	cout << "\n";
	cout << "[DONE] Remove student from course\n";
	PressToContinue();
}

// TEST OK
void TestAddStudentToCourse() {
	Header();
	cout << "[RUN] Add student to course\n";

	int student_id = getInt("student id");

	Student student;
	bool exist_student = app->GetStudent(student_id, student);

	if (!exist_student) {
		cout << "\n";
		cout << "Not exist student " << student_id << "\n";
	} else {
		ShowStudentInfo(student);

		vector<string> course_list = app->GetCourseList();
		cout << ">> Course list\n\n";
		for (int i = 0; i < course_list.size(); ++i) {
			cout << i + 1 << ". " << course_list[i] << "\n";
		}
		cout << "\n";

		int id = getInt("Enter index course wannto to add new student");

		if (id <= 0 || id > course_list.size()) {
			cout << "\n";
			cout << "Something wrong when choose index course";
		} else {
			if (app->AddStudentToCourse(course_list[id - 1], student_id)) {
				cout << "\n";
				cout << ">> Add student " << student_id << " to course " << course_list[id - 1] << " successfully\n";
			} else {
				cout << "\n";
				cout << ">> Something wrong when add new student " << student_id << " to course " << course_list[id - 1] << "\n";
			}
		}
	PressToContinue();	}
		cout << "\n";
		cout << "[DONE] Add student to course\n";

}

// TEST OK
void TestStaffViewCourseList() {
	Header();
	cout << "[RUN] View course list\n\n";
	vector<string> course_list;
	course_list = app->GetCourseList();
	cout << ">> Course list \n\n";
	for (int i = 0; i < course_list.size(); ++i) {
		cout << i + 1 << ". " << course_list[i] << "\n";
	}
	cout << "\n";
	cout << "[DONE] View course list\n\n";
	PressToContinue();
}

// TEST OK
void TestStaffViewListStudentOfACourse() {
	Header();
	cout << "[RUN] View list student of a coures\n\n";
	vector<string> course_list;
	course_list = app->GetCourseList();
	cout << ">> Course list \n\n";
	for (int i = 0; i < course_list.size(); ++i) {
		cout << i + 1 << ". " << course_list[i] << "\n";
	}
	cout << "\n";

	int id = getInt("Enter index course wanna to view list student");

	if (id <= 0 || id > course_list.size()) {
		cout << "\n";
		cout << "Something wrong when choose index course";
	} else {
		vector<Student> students_list;
		students_list = app->GetStudentListFromCourse(course_list[id - 1]);
		cout << "\n";
		cout << ">> List Student Of Course " << course_list[id - 1] << "\n\n";
		ShowStudentListInfo(students_list);
	}

	cout << "\n";
	cout << "[DONE] View list student of a course\n";
	PressToContinue();
}

// TEST OK
void TestStaffViewAttendanceListOfACourse() {
	Header();
	cout << "[RUN] View attendacne list of a coures\n\n";
	vector<string> course_list;
	course_list = app->GetCourseList();
	cout << ">> Course list \n\n";
	for (int i = 0; i < course_list.size(); ++i) {
		cout << i + 1 << ". " << course_list[i] << "\n";
	}
	cout << "\n";

	int id = getInt("Enter index course wanna to view attendance list");

	if (id <= 0 || id > course_list.size()) {
		cout << "\n";
		cout << "Something wrong when choose index course";
	} else {

	vector<Attendance> Attendance_list;

	Attendance_list = app->GetAttendanceList(course_list[id - 1]);
	cout << "\n";
	cout << ">> Attendance List Of Course " << course_list[id - 1] << "\n\n";
	ShowAttendanceList(Attendance_list);
	}
	cout << "\n";
	cout << "[DONE] View attendance list of a course\n";
	PressToContinue();

}

// TEST OK
void TestSearchAndViewScoreboard() {
	Header();
	cout << "[RUN] Search and view scoreboard\n\n";

	string find_id = getString("Enter ID wanna search");

	vector<string> course_list;

	course_list = app->SearchCourse(find_id);

	if (course_list.size() == 0) {
		cout << "\n";
		cout << ">> No Course Match!!!\n";
	} else {
		cout << ">> List Of Course Impossible\n\n";
		for (int i = 0; i < course_list.size(); ++i) {
			cout << i + 1 << ". " << course_list[i] << "\n";
		}
		cout << "\n";
		int id = getInt("Enter index course Wanna to view scoreboard");
		
		if (id <= 0 || id > course_list.size()) {
			cout << "\n";
			cout << ">> Something wrong when choose index course\n";
		} else {
			vector<Score> scoreboard = app->Getscoreboard(course_list[id - 1]);
			ShowScoreboard(scoreboard);
		}
	}

	cout << "\n";
	cout << "[DONE] Search and view scoreboard\n";
	PressToContinue();
}

// TEST OK
void TestExportScoreboard() {
	Header();
	cout << "[RUN] Export scoreboard\n\n";

	cout << ">> List of course\n\n";

	vector<string> course_list;

	course_list = app->GetCourseList();

	if (course_list.size() == 0) {
		cout << "\n";
		cout << ">> No course to export scoreboard\n";
	} else {
		for (int i = 0; i < course_list.size(); ++i) {
			cout << i + 1 << ". " << course_list[i] << "\n";
		}
		cout << "\n";
		int id = getInt("Enter index course wanna export scoreboard");
		if (id <= 0 || id > course_list.size()) {
			cout << "\n";
			cout << "Something wrong when choose index course";
		} else {
			if (app->ExportScoreboard(course_list[id - 1])) {
				cout << "\n";
				cout << ">> Export file save to \\export\\" << course_list[id - 1] << "_scoreboard.txt" << "\n";
				cout << ">> Export scoreboard of course " << course_list[id - 1] << " successfully\n";
			} else {
				cout << "\n";
				cout << ">> Something wrong when export\n";
			}
		}
	}

	cout << "\n";
	cout << "[DONE] Export scoreboard\n";
	PressToContinue();
}

// TEST OK
void TestSearchAndViewAttendance() {
	Header();
	cout << "[RUN] Search and view attendance list\n\n";

	string find_id = getString("Enter ID wanna search");

	vector<string> course_list;

	course_list = app->SearchCourse(find_id);

	if (course_list.size() == 0) {
		cout << "\n";
		cout << "No Course Match!!!\n";
	} else {
		cout << ">> List of courses match\n\n";
		for (int i = 0; i < course_list.size(); ++i) {
			cout << i + 1 << ". " << course_list[i] << "\n";
		}
		cout << "\n";
		int id = getInt("Enter index course wanna to view attendance");

		vector<Attendance> Attendance_list;

		Attendance_list = app->GetAttendanceList(course_list[id - 1]);
		cout << ">> Attendance List Of Course\n\n";

		ShowAttendanceList(Attendance_list);
	}
	cout << "\n";
	cout << "[DONE] Search and view attendance list\n";
	PressToContinue();
}

// TEST OK
void TestExportAttendance() {
	Header();
	cout << "[RUN] Export attendance\n\n";

	cout << ">> List of course\n\n";

	vector<string> course_list;

	course_list = app->GetCourseList();

	if (course_list.size() == 0) {
		cout << "No course to export attendance\n";
	} else {
		for (int i = 0; i < course_list.size(); ++i) {
			cout << i + 1 << ". " << course_list[i] << "\n";
		}
		cout << "\n";
		int id = getInt("Index course wanna export attendance");
		if (app->ExportAttendance(course_list[id - 1])) {
			cout << "\n";
			cout << ">> Export file save to \\export\\" << course_list[id - 1] << "_attendance.csv" << "\n";
			cout << ">> Export attendace of course " << course_list[id - 1] << " OK\n";
		} else {
			cout << "\n";
			cout << ">> Something wrong when export\n";
		}
	}

	cout << "\n";
	cout << "[DONE] Export attendance\n";
	PressToContinue();
}

// TEST OK
void TestLecturerViewCoursesList() {
	Header();
	cout << "[RUN] Lecture view course list\n\n";

	cout << ">> Courses list\n";

	vector<string> list;
	
	list = app->LecturerGetCoursesList();

	for (int i = 0; i < list.size(); ++i) {
		cout << i + 1 << ". " << list[i] << "\n";
	}
	
	cout << "\n";
	cout << "[DONE] Lecture view course list\n";
	PressToContinue();
}

void TestLecturerViewListOfStudentOfACourse() {
	cout <<"[RUN] Lecturer view list student of a course\n\n";

	vector<string> list = app->LecturerGetCoursesList();

	cout << ">> Course list\n\n";
	for (int i = 0; i < list.size(); ++i) {
		cout << i + 1 << ". " << list[i] << "\n";
	}
	cout << "\n";
	int id = getInt("Enter index course wanna view list of student");

	if (id <= 0 || id > list.size()) {
		cout << "\n";
		cout << "Something wrong when choose index of course\n";
	} else {
		vector<Student> students_list;

		students_list = app->GetStudentListFromCourse(list[id - 1]);
		cout << ">> List Student Of Course " << list[id - 1] << "\n\n";
		ShowStudentListInfo(students_list);
	}

	cout << "\n";
	cout << "[DONE] Lecturer view list student of a course\n";
	PressToContinue();
}

void TestLecturerViewAttendanceListOfACourse() {
	cout << "[RUN] Lecturer view attendance list of a course\n\n";

	vector<string> list = app->LecturerGetCoursesList();

	cout << ">> Course list\n\n";
	for (int i = 0; i < list.size(); ++i) {
		cout << i + 1 << ". " << list[i] << "\n";
	}

	int id = getInt("Enter index course wanna view attendance list");

	if (id <= 0 || id > list.size()) {
		cout << "\n";
		cout << "Something wrong when choose index course\n";
	} else {

		vector<Attendance> Attendance_list;

		Attendance_list = app->GetAttendanceList(list[id - 1]);

	cout << ">> Attendance List Of Course " << list[id - 1] << "\n";
	cout << "\n";
		ShowAttendanceList(Attendance_list);

	}
	cout << "[DONE] Lecturer view attendance list of a course\n";
	PressToContinue();
}

void TestLecturerEditAttendance() {
	cout << "[RUN] Lecturer edit attendance\n\n";
	
	vector<string> list = app->LecturerGetCoursesList();

	cout << ">> Course list\n\n";

	for (int i = 0; i < list.size(); ++i) {
		cout << i + 1 << ". " << list[i] << "\n";
	}

	cout << "\n";
	int id = getInt("Enter index course  wanna edit attendance");

	if (id <= 0 || id >list.size()) {
		cout << "\n";
		cout << "Something wrong when choose index of course\n";
	} else {
		vector<Attendance> Attendance_list;
		while (1) {
			Attendance_list = app->GetAttendanceList(list[id - 1]);
			cout << setw(7) << left << "Index" << setw(12) << left << "ID" << setw(25) << left <<  "Full Name";
			for (int i = 1; i <= 10; ++i) {
				string week = "";
				if (i <= 9) week = "Week-0" + std::to_string(i); else week = "Week-10";
				cout << setw(10) << left << week;
			}
			cout << "\n";
			cout << setfill('-') << setw(142) << "-" << "\n";
			cout << setfill(' ');
			for (int i = 0; i < Attendance_list.size(); ++i) {
				cout << setw(7) << left << i + 1;
				cout << setw(12) << left << Attendance_list[i].ID;
				cout << setw(25) << left << Helper::GetFullName(Attendance_list[i].first_name, Attendance_list[i].last_name);
				for (int k = 0; k < Attendance_list[i].week.size(); k++)
				{
					string tmp = std::to_string(Attendance_list[i].week[k]) + "/2";
					cout << setw(10) << left << tmp;
				}
				cout << "\n";
			}
			cout << setfill('-') << setw(142) << "-" << "\n";
			cout << setfill(' ');
			cout << "\n";
			int ID = getInt("Index student you wanna edit (0 to exit)");
			if (ID == 0) break;
			int week = getInt("Week you wanna edit for student " + std::to_string(Attendance_list[ID - 1].ID));
			int shift = getInt("You wanna edit for the first day or the second day (1 or 2)");
			if (app->LecturerEditAttendance(Attendance_list[ID - 1].ID, list[id - 1], week, shift)) {
				cout << ">> Edit Successfully\n";
			} else {
				cout << ">> Edit Fail\n";
			}
		}
		cout << "Press any key to continue edit";
		cin.ignore();
		Attendance_list.clear();
	}

	cout << "\n";
	cout << "[DONE] Lecturer edit attendance\n";
	PressToContinue();
}

void TestImportScore() {
	Header();
	cout << "[RUN] TEST IMPORT SCORE\n\n";

	cout << ">> Import file\n\n";

	vector<string> list = app->GetCsvForScore();

	for (int i = 0; i < list.size(); ++i) {
		cout << i + 1 << ". " << list[i] << "\n";
	}

	int id = getInt("Index file you wanna import");

	vector<string> list2 = app->LecturerGetCoursesList();

	cout << "\n Course list\n";
	for (int i = 0; i < list2.size(); ++i) {
		cout << i + 1 << ". " << list2[i] << "\n";
	}

	int id2 = getInt("Index cousre you wanna import score");

	if (app->ImportScore(list2[id2 - 1], list[id - 1])) {
		cout << ">> Import Score OK\n";
	} else {
		cout << ">> Import Score FAIL\n";
	}

	cout << "[DONE] TEST IMPORT SCORE\n";
	PressToContinue();
}

void TestEditGrade() {
	Header();
	cout << "[RUN] TEST EDIT GRADE\n\n";

	vector<string> list = app->LecturerGetCoursesList();
	cout << ">> Course list \n\n";

	for (int i = 0; i < list.size(); ++i) {
		cout << i + 1 << ". " << list[i] << "\n";
	}

	int id = getInt("Index course you wanna edit score of student");

	vector<Score> scoreboard = app->Getscoreboard(list[id - 1]);
	cout << "| " << setw(10) << left << "No";
	cout << "| " << setw(13) << left << "Student ID";
	cout << "| " << setw(35) << left << "Full Name";
	cout << "| " << setw(10) << left << "MIDTERM";
	cout << "| " << setw(10) << left << "LAB";
	cout << "| " << setw(10) << left << "BONUS";
	cout << "| " << setw(10) << left << "FINAL";
	cout << "| " << setw(10) << left << "ABCF";
	cout << "| " << setw(10) << left << "GPA";
	cout << "|\n"; 
	cout << setfill('-') << setw(134) << "";
	cout << setfill(' ') << "\n";
	for (int i = 0; i < scoreboard.size(); ++i) {
		cout << "| " << setw(10) << left << i + 1;
		cout << "| " << setw(13) << left << scoreboard[i].ID;
		cout << "| " << setw(35) << left << Helper::GetFullName(scoreboard[i].first_name, scoreboard[i].last_name);
		cout << "| " << setw(10) << left << scoreboard[i].mid_term;
		cout << "| " << setw(10) << left << scoreboard[i].lab;
		cout << "| " << setw(10) << left << scoreboard[i].bonus;
		cout << "| " << setw(10) << left << scoreboard[i].final_term;
		cout << "| " << setw(10) << left << scoreboard[i].ABCF;
		cout << "| " << setw(10) << left << scoreboard[i].GPA;
		cout << "|\n";
		cout << setfill('-') << setw(124) << "";
		cout << setfill(' ') << "\n";
	}

	cout << "\n";
	int id2 = getInt("Index student you wanna to edit score");

	scoreboard[id2 - 1].mid_term = 5.0;
	scoreboard[id2 - 1].lab = 9.0;
	scoreboard[id2 - 1].final_term = 8.0;
	scoreboard[id2 - 1].bonus = 0.5;

	app->LecturerEditGrade(list[id - 1], scoreboard[id2 - 1]);

	cout << "[DONE] TEST EDIT GRADE\n";
	PressToContinue();

}

void TestViewAScoreboard() {
	Header();
	cout << "[RUN] TEST VIEW A SCOREBOARD\n\n";

	vector<string> list = app->LecturerGetCoursesList();
	cout << ">> Course list \n\n";

	for (int i = 0; i < list.size(); ++i) {
		cout << i + 1 << ". " << list[i] << "\n";
	}

	int id = getInt("Index course you wanna view score of student");

	vector<Score> scoreboard = app->Getscoreboard(list[id - 1]);
	cout << "| " << setw(13) << left << "Student ID";
	cout << "| " << setw(35) << left << "Full Name";
	cout << "| " << setw(10) << left << "MIDTERM";
	cout << "| " << setw(10) << left << "LAB";
	cout << "| " << setw(10) << left << "BONUS";
	cout << "| " << setw(10) << left << "FINAL";
	cout << "| " << setw(10) << left << "ABCF";
	cout << "| " << setw(10) << left << "GPA";
	cout << "|\n"; 
	cout << setfill('-') << setw(124) << "";
	cout << setfill(' ') << "\n";
	for (int i = 0; i < scoreboard.size(); ++i) {
		cout << "| " << setw(13) << left << scoreboard[i].ID;
		cout << "| " << setw(35) << left << Helper::GetFullName(scoreboard[i].first_name, scoreboard[i].last_name);
		cout << "| " << setw(10) << left << scoreboard[i].mid_term;
		cout << "| " << setw(10) << left << scoreboard[i].lab;
		cout << "| " << setw(10) << left << scoreboard[i].bonus;
		cout << "| " << setw(10) << left << scoreboard[i].final_term;
		cout << "| " << setw(10) << left << scoreboard[i].ABCF;
		cout << "| " << setw(10) << left << scoreboard[i].GPA;
		cout << "|\n";
		cout << setfill('-') << setw(124) << "";
		cout << setfill(' ') << "\n";
	}	cout << "\n";

	cout << "[DONE] TEST VIEW A SCOREBOARD\n";
	PressToContinue();
}

void TestCheckIn() {
	cout << "[RUN] CHECKIN\n\n";
		
	string check_in_status = app->StudentCheckIn();
	cout << ">> " << check_in_status << "\n\n";

	cout << "[DONE] CHECK-IN\n";
	cout << "Press Enter";
	PressToContinue();
}

void TestViewCheckInResult() {
	Header();
	cout << "[RUN] VIEW CHECK-IN RESULT\n\n";

	vector<Attendance> Attendance_list = app->StudentViewCheckInResult(); 
		cout << "| " << setw(12) << left << "Course ID";
	for (int i = 1; i <= 10; ++i) {
		string week = "";
		if (i <= 9) week = "Week-0" + std::to_string(i); else week = "Week-10";
		cout << "| " << setw(10) << left << week;
	}
	cout << "|\n";
	cout << setfill('-') << setw(135) << "-" << "\n";
	cout << setfill(' ');
	for (int i = 0; i < Attendance_list.size(); ++i) {
		cout << "| " << setw(12) << left << Attendance_list[i].course_id;
		for (int k = 0; k < Attendance_list[i].week.size(); k++)
		{
			string tmp = std::to_string(Attendance_list[i].week[k]) + "/2";
			cout << "| " <<  setw(10) << left << tmp;
		}
		cout << "|\n";
	}
	cout << setfill('-') << setw(135) << "-" << "\n";
	cout << setfill(' ');

	cout << "\n";
	cout << "[DONE] VIEW CHECK-IN RESULT\n";
	PressToContinue();
}

void TestViewSchedules() {
	cout <<"[RUN] STUDENT VIEW SCHEDULE\n\n";

		cout << setw(7) << left << " ";
		for (int i = 2; i <= 7; ++i) {
			cout << "| " << setw(14) << left << i;
		}
		cout << "|\n";
		vector<Schedule> schedule;
		schedule = app->StudentGetSchedule();
		for (int j = 1; j <= 4; ++j) {
			cout << setfill('-') << setw(105) << "\n";
			cout << setfill(' ') << "\n";
			for (int i = 1; i <= 7; ++i) {
				if (i == 1) {
					string tmp = "Shift " + std::to_string(j);
					cout << setw(7) << left << tmp;
				} else {
					bool found_period = false;
					for (int k = 0; k < schedule.size(); ++k) {
						if (schedule[k].dow == i && schedule[k].shift == j) {
							string tmp  = schedule[k].course_id + "--" + schedule[k].room;
							cout << "| " << setw(14) << left << tmp;
							found_period = true;
							break;
						}
					}
					if (!found_period) cout <<"| " << setw(14) << left << " ";
				}
			}
			cout << "|\n";
		}
		cout << setfill('-') << setw(105) << "\n";
		cout << setfill(' ') << "\n";

	cout << "\n";
	cout << "[DONE] STUDENT VIEW SCHEDULE\n";
	PressToContinue();
}

void TestViewScoresOfACourse() {
	cout << "[RUN] VIEW HIS/HER SCORES OF A COURSE\n\n";

	 	vector<Score> scoreboard;

		scoreboard = app->StudentViewScoreboard();

		cout << "| " << setw(15) << left << "COURSE_ID";
		cout << "| " << setw(10) << left << "MIDTERM";
		cout << "| " << setw(10) << left << "LAB";
		cout << "| " << setw(10) << left << "BONUS";
		cout << "| " << setw(10) << left << "FINAL";
		cout << "| " << setw(10) << left << "ABCF";
		cout << "| " << setw(10) << left << "GPA";
		cout << "|\n"; 
		cout << setfill('-') << setw(87) << "";
		cout << setfill(' ') << "\n";
		for (int i = 0; i < scoreboard.size(); ++i) {
			cout << "| " << setw(15) << left << scoreboard[i].course_id;
			cout << "| " << setw(10) << left << scoreboard[i].mid_term;
			cout << "| " << setw(10) << left << scoreboard[i].lab;
			cout << "| " << setw(10) << left << scoreboard[i].bonus;
			cout << "| " << setw(10) << left << scoreboard[i].final_term;
			cout << "| " << setw(10) << left << scoreboard[i].ABCF;
			cout << "| " << setw(10) << left << scoreboard[i].GPA;
			cout << "|\n";
			cout << setfill('-') << setw(87) << "";
			cout << setfill(' ') << "\n";
		}

	cout << "\n";
	cout << "[DONE] VIEW HIS/HER SCORES OF A COURSE\n";
	PressToContinue();
}

void Notyet() {
	cout << "Feature Will Coming Soon...\n";
	cout << "Press Enter";
	cin.ignore();
}

int main() {
	// string username = "admin";
	// app->CreateAccount(username, username);
	vector<pair<int, string>> main_menu;
	vector<pair<int, string>> staff_menu;
	vector<pair<int, string>> courses_menu;
	vector<pair<int, string>> class_menu;
	vector<pair<int, string>> scoreboard_menu;
	vector<pair<int, string>> attendance_menu;
	vector<pair<int, string>> lecturer_menu;
	vector<pair<int, string>> student_menu;

	// all role
	main_menu.push_back(make_pair(2, "Show menu"));
	main_menu.push_back(make_pair(3, "View profile info"));
	main_menu.push_back(make_pair(4, "Change password"));
	main_menu.push_back(make_pair(5, "Logout"));

	staff_menu.push_back(make_pair(1, "Class"));
	staff_menu.push_back(make_pair(2, "Courses"));
	staff_menu.push_back(make_pair(3, "Scoreboard"));
	staff_menu.push_back(make_pair(4, "Attendance list"));

	class_menu.push_back(make_pair(6, "Import class"));
	class_menu.push_back(make_pair(7, "Add new student"));
	class_menu.push_back(make_pair(8, "Edit student"));
	class_menu.push_back(make_pair(9, "Remove student"));
	class_menu.push_back(make_pair(10, "Change student between two class"));
	class_menu.push_back(make_pair(11, "View list class"));
	class_menu.push_back(make_pair(12, "View list student of a class"));

	courses_menu.push_back(make_pair(14, "Import course"));
	courses_menu.push_back(make_pair(15, "Add new course"));
	courses_menu.push_back(make_pair(16, "Edit course"));
	courses_menu.push_back(make_pair(17, "Remove course"));
	courses_menu.push_back(make_pair(18, "Remove student from course"));
	courses_menu.push_back(make_pair(19, "Add student to course"));
	courses_menu.push_back(make_pair(20, "View course list"));
	courses_menu.push_back(make_pair(21, "View list student of a course"));
	courses_menu.push_back(make_pair(22, "View attendance list of a course"));

	scoreboard_menu.push_back(make_pair(24, "Search and view scoreboard of a course"));
	scoreboard_menu.push_back(make_pair(25, "Export scoreboard"));

	attendance_menu.push_back(make_pair(26, "Search and view attendance of a course"));
	attendance_menu.push_back(make_pair(27, "Export attendance"));
	
	lecturer_menu.push_back(make_pair(28, "View list of courses in the current semester"));
	lecturer_menu.push_back(make_pair(29, "View list of students of a course"));
	lecturer_menu.push_back(make_pair(30, "View Attendance list of a course"));
	lecturer_menu.push_back(make_pair(31, "Edit an attendance"));
	lecturer_menu.push_back(make_pair(32, "Import scoreboard"));
	lecturer_menu.push_back(make_pair(33, "Edit grade of a student"));
	lecturer_menu.push_back(make_pair(34, "View a scoreboard"));

	student_menu.push_back(make_pair(35, "Check-in"));
	student_menu.push_back(make_pair(36, "View check-in result"));
	student_menu.push_back(make_pair(37, "View Schedules"));
	student_menu.push_back(make_pair(38, "View his/her scores of a course"));

	bool show_menu = true;
	int show_submenu = 0;
	while (1) {
		Header();
		cout << "                               DEMO STUDENT MANAGER SYSTEM\n";

		if (!app->IsAuthenticated()) {
			TestLogin();
		} else {
			int option = -1;
			if (!show_menu) {
				cout << "### Main menu\n\n";
				for (int i = 0; i < main_menu.size(); ++i) {
					cout << i + 1 << ". " << main_menu[i].second << "\n";
				}
				cout << "0. Exit\n";
				cout << "\n";
				int opt = getInt("Enter option");
				if (opt < 0 || opt > main_menu.size()) break; 
				if (opt == 0) option = 0; else option =  main_menu[opt - 1].first;
			} else {
				UserRole role;
				int opt;
				role = app->GetUserRole();
				switch (role) {
					case UserRole::STAFF:
						if (show_submenu == 0) {
							cout << "### Academic staff menu\n\n";
							for (int i = 0; i < staff_menu.size(); ++i) {
								cout << i + 1 << ". " << staff_menu[i].second << "\n";
							}
							cout << "0. Back\n";
							cout << "\n";
							int opt = getInt("Enter sub-menu option");
							if (opt < 0 || opt > staff_menu.size()) break;
							if (opt == 0) {
								show_menu = false;
								break;
							} else {
								show_submenu = opt;
								break;
							}
						}
						if (show_submenu == 1) {
							cout << "@@@ Class menu\n\n";
							for (int i = 0; i < class_menu.size(); ++i) {
								cout << i + 1 << ". " << class_menu[i].second << "\n";
							}
							cout << "0. Back\n";
							cout << "\n";
							int opt = getInt("Enter option");
							if (opt < 0 || opt > class_menu.size()) break;
							if (opt == 0) {
								show_submenu = 0;
								break;
							} else {
								option = class_menu[opt - 1].first;
							}
						}
						if (show_submenu == 2) {
							cout << "@@@ Courses menu\n\n";
							for (int i = 0; i < courses_menu.size(); ++i) {
								cout << i + 1 << ". " << courses_menu[i].second << "\n";
							}
							cout << "0. Back\n";
							cout << "\n";
							int opt = getInt("Enter option");
							if (opt < 0 || opt > courses_menu.size()) break;
							if (opt == 0) {
								show_submenu = false;
								break;
							} else {
								option = courses_menu[opt - 1].first;
							}
						}
						if (show_submenu == 3) {
							cout << "@@@ Scoreboard menu\n\n";
							for (int i = 0; i < scoreboard_menu.size(); ++i) {
								cout << i + 1 << ". " << scoreboard_menu[i].second << "\n";
							}
							cout << "0. Back\n";
							cout << "\n";
							int opt = getInt("Enter option");
							if (opt < 0 || opt > scoreboard_menu.size()) break;
							if (opt == 0) {
								show_submenu = false;
								break;
							} else {
								option = scoreboard_menu[opt - 1].first;
							}
						}
						if (show_submenu == 4) {
							cout << "@@@ Attendance list menu\n\n";
							for (int i = 0; i < attendance_menu.size(); ++i) {
								cout << i + 1 << ". " << attendance_menu[i].second << "\n";
							}
							cout << "0. Back\n";
							cout << "\n";
							int opt = getInt("Enter option");
							if (opt < 0 || opt > attendance_menu.size()) break;
							if (opt == 0) {
								show_submenu = false;
								break;
							} else {
								option = attendance_menu[opt - 1].first;
							}
						}
						break;
					case UserRole::LECTURER:
						for (int i = 0; i < lecturer_menu.size(); ++i) {
							cout << i + 1 << ". " << lecturer_menu[i].second << "\n";
						}

						cout << "0. Exit\n";
						cout << "\n";
						opt = getInt("Enter option");
						if (opt < 0 || opt > lecturer_menu.size()) break; 
						if (opt == 0) option = 0; else option =  lecturer_menu[opt - 1].first;
						break;

					case UserRole::STUDENT:
						for (int i = 0; i < student_menu.size(); ++i) {
							cout << i + 1 << ". " << student_menu[i].second << "\n";
						}
						cout << "0. Exit\n";
						cout << "\n";

						opt = getInt("Enter option");
						if (opt < 0 || opt > student_menu.size()) break; 
						if (opt == 0) option = 0; else option =  student_menu[opt - 1].first;
						break;
					default:
						break;
				}
			}

			if (option == 0) break;
			switch(option) {
				case 2:
					show_menu = true;
					break;
				case 3:
					TestViewProfile();
					break;
				case 4:
					TestChangePassword();
					break;
				case 5:
					TestLogout();
					break;
				case 6:
					TestImportClass();
					break;
				case 7:
					TestAddNewStudentToClass();
					break;
				case 8:
					TestEditStudentFromClass();
					break;
				case 9:
					TestRemoveStudentFromClass();
					break;
				case 10:
					TestChangeStudent();
					break;
				case 11:
					TestViewListClass();
					break;
				case 12:
					TestViewListStudentOfAClass();
					break;
				case 13:
					Notyet();
				case 14:
					TestImportCourse();
					break;
				case 15:
					TestAddNewCourse();
					break;
				case 16:
					TestEditCourses();
					break;
				case 17:
					TestRemoveCourse();
					break;
				case 18:
					TestRemoveStudentFromCourse();
					break;
				case 19:
					TestAddStudentToCourse();
					break;
				case 20:
					TestStaffViewCourseList();
					break;
				case 21:
					TestStaffViewListStudentOfACourse();
					break;
				case 22:
					TestStaffViewAttendanceListOfACourse();
					break;
				case 23:
					Notyet();
					break;
				case 24:
					TestSearchAndViewScoreboard();
					break;
				case 25:
					TestExportScoreboard();
					break;
				case 26:
					TestSearchAndViewAttendance();
					break;
				case 27:
					TestExportAttendance();
					break;
				case 28:
					TestLecturerViewCoursesList();
					break;
				case 29:
					TestLecturerViewListOfStudentOfACourse();
					break;
				case 30:
					TestLecturerViewAttendanceListOfACourse();
					break;
				case 31:
					TestLecturerEditAttendance();
					break;
				case 32:
					TestImportScore();
					break;
				case 33:
					TestEditGrade();
					break;
				case 34:
					TestViewAScoreboard();
					break;
				case 35:
					TestCheckIn();
					break;
				case 36:
					TestViewCheckInResult();
					break;
				case 37:
					TestViewSchedules();
					break;
				case 38:
					TestViewScoresOfACourse();
					break;
				default:
					continue;
			}
		}
	}
}
