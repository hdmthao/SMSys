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


void TestLogin() {
	cout << "### TEST LOGIN\n";
	string userName = getString("Ten Dang nhap");
	string password = getString("Mat Khau");
	
	cout << "\n";
	if (app->Login(userName, password)) {
		cout << "[OK] Login OK\n";
	} else {
		cout << "[X]  Login FAIL\n";
	}

}

void TestImportClass() {
	cout << "### TEST IMPORT CLASS\n";
	string new_class_name = getString("Ten Lop Moi");
	string csv_name = "18CTT1-Students.csv";

	cout << "\n";
	if (app->ImportClass(new_class_name, csv_name)) {
		cout << "[OK] Import OK\n";
	} else {
		cout << "[X]  Import FAIL\n";
	}
}

void TestAddNewStudentToClass() {
	cout << "### TEST ADD NEW STUDENT TO CLASS\n";
	Student new_student;
	string class_name = getString("Lop Muon Add");
	new_student.ID = getInt("ID");
	new_student.first_name = getString("First Name");
	new_student.last_name = getString("Last Name)");
	new_student.gender = getString("Gender (male/female)");
	new_student.dob = getString("dob (dd/mm/yyyy");

	cout << "\n";

	if (app->AddNewStudentToClass(class_name, new_student)) {
		cout << "[OK] Add OK\n";
	} else {
		cout << "[X]  Add FAIL\n";
	}
}

void TestChangeStudent() {
	cout << "### TEST CHANGE STUDENT\n";
	int id;
	id = getInt("ID");
	string class_b;
	class_b = getString("Lop can chuyen den");

	cout << "\n";
	if (app->ChangeStudentFromClassAToB(id, class_b)) {
		cout << "[OK] Change OK\n";
	} else {
		cout << "[X]  Change FAIL\n";
	}
}

void TestRemoveStudentFromClass() {
	cout << "### TEST REMOVE STUDENT FROM CLASS\n";
	int id;
	id = getInt("Remove ID");
	cout << "\n";
	if (app->RemoveStudentFromClass(id)) {
		cout << ">> Remove OK\n";
	} else {
		cout << ">> Remove FAIL\n";
	}
}

void TestEditStudentFromClass() {
	cout << "### TEST EDIT STUDENT\n";
	Student student;
	int id = getInt("id");
	student = app->GetStudent(id);
	
	cout << "\n";
	if (app->EditStudentFromClass(student)) {
		cout << ">> Edit OK\n";
	} else {
		cout << ">> Edit Fail\n";
	}
}

void TestViewListClass() {
	cout << "### TEST VIEW LIST CLASS\n";
	vector<string> class_list;
	class_list = app->GetClassList();
	for (int i = 0; i < class_list.size(); ++i) {
		cout <<i + 1 << ". " << class_list[i] << "\n";
	}
	cout << "\n";
	cout << "[OK] View List Class OK\n";

	cout << "\n";
	cout << "### TEST VIEW LIST STUDENT\n";

	int id = getInt("Index Class");
	vector<Student> students_list;

	students_list = app->GetStudentListFromClass(class_list[id - 1]);
	cout << ">> List Student Of Class " << class_list[id - 1] << "\n";
	cout << "\n";

	cout << setw(12) << left << "ID" << setw(25) << left <<  "Full Name" << setw(9) << left << "Gender" <<
	setw(15) << left << "Day Of Birth" << setw(25) << left << "Email" << "\n";
	cout << setfill('-') << setw(80) << "-" << "\n";
	cout << setfill(' ');
	for (int i = 0; i < students_list.size(); ++i) {
		cout << setw(12) << left << students_list[i].ID;
		cout << setw(25) << left << Helper::GetFullName(students_list[i].first_name, students_list[i].last_name);
		cout << setw(9) << left << students_list[i].gender;
		cout << setw(15) << left << students_list[i].dob;
		cout << setw(25) << left << students_list[i].email;
		cout << "\n";
	}
	cout << setfill('-') << setw(80) << "-" << "\n";
	cout << setfill(' ');
	cout << "\n";
	cout << "[OK] View List Student OK\n";
}

void TestGetCSVFile() {
	cout << "### TEST GET CSV FILE\n";

	vector<string> lists = app->GetCsvForClass();
	cout << ">> List File In Folder Data/Import/Class\n";

	for (int i = 0; i < lists.size(); ++i) {
		cout << lists[i] << "\n";
	}
	lists.clear();

	lists = app->GetCsvForCourse();

	cout << "\n";
	cout << ">> List File In Folder Data/Import/Course\n";

	for (int i = 0; i < lists.size(); ++i) {
		cout << lists[i] << "\n";
	}
	cout << "\n";
	cout << "[OK] View List Csv OK\n";
}

void TestImportCourse() {
	cout << "### TEST IMPORT COURSE\n";

	string course_id = getString("Course ID");
	string  csv_name = "CS162.csv";

	cout << "\n";

	if (app->ImportCourse(course_id, csv_name)) {
		cout << "[OK] Import Course OK\n";
	} else {
		cout << "[X]  Import Course FAIL\n";
	}
}

void TestAddNewCourse() {
	cout << "### TEST ADD NEW COURSE\n";

	Course new_course;
	new_course.ID = getString("Course ID");
	new_course.name = getString("name");
	new_course.lecturer = getString("lecture");
	string class_name = getString("class name");
	new_course.start_date = getString("start date");
	new_course.end_date = getString("end date");

	int number_period = getInt("number priod");
	Period period_1, period_2;
	period_1.dow = getInt("Day of week of period 1");
	period_1.shift = getInt("Shift of period 1");
	period_1.room = getString("Room of period 1");
	if (number_period == 2) {
		period_2.dow = getInt("Day of week of period 2");
		period_2.shift = getInt("Shift of period 2");
		period_2.room = getString("Room of period 2");
	}

	cout << "\n";

	if (app->AddNewCourse(new_course, class_name, number_period, period_1, period_2)) {
		cout << "[OK] Add New Course OK\n";
	} else {
		cout << "[X]  Add New Course FAIL\n";
	}
}

void TestAddStudentToCourse() {
	cout << "### TEST ADD STUDENT TO COURSE\n";

	int student_id = getInt("student id");
	string course_id = getString("course id");

	if (app->AddStudentToCourse(course_id, student_id)) {
		cout << ">> Add student id " << student_id << " to course " << course_id << "\n";
	} else {
		cout << ">> Student not existed or existed in course\n";
	}
	cout << "\n";
	cout << "[OK] Add Student To Course OK\n";
}

void TestRemoveStudentFromCourse() {
	cout << "TEST REMOVE STUDENT FROM COURSE\n";

	string course_id = getString("Coures ID");
	int del_student = getInt("Student ID");

	if (app->RemoveStudentFromCourse(course_id, del_student)) {
		cout << ">> Remove stunde id " << del_student << " from course " << course_id << "\n";
	} else {
		cout << ">> Student not existed\n";
	}

	cout << "\n";
	cout << "[OK] Remove Student From Course OK\n";
}

void TestViewCourseList() {
	cout << "### TEST VIEW LIST COURSE\n";
	vector<string> course_list;
	course_list = app->GetCourselist();
	cout << ">> List Of Course\n";
	for (int i = 0; i < course_list.size(); ++i) {
		cout << i + 1 << ". " << course_list[i] << "\n";
	}
	cout << "\n";
	cout << "[OK] View List Course OK\n";

	cout << "\n";
	cout << "### TEST VIEW LIST STUDENT\n";
	int id = getInt("Index Course");

	vector<Student> students_list;

	students_list = app->GetStudentListFromCourse(course_list[id - 1]);
	cout << ">> List Student Of Course " << course_list[id - 1] << "\n";
	cout << "\n";

	cout << setw(12) << left << "ID" << setw(25) << left <<  "Full Name" << setw(9) << left << "Gender" <<
	setw(15) << left << "Day Of Birth" << setw(25) << left << "Email" << "\n";
	cout << setfill('-') << setw(80) << "-" << "\n";
	cout << setfill(' ');
	for (int i = 0; i < students_list.size(); ++i) {
		cout << setw(12) << left << students_list[i].ID;
		cout << setw(25) << left << Helper::GetFullName(students_list[i].first_name, students_list[i].last_name);
		cout << setw(9) << left << students_list[i].gender;
		cout << setw(15) << left << students_list[i].dob;
		cout << setw(25) << left << students_list[i].email;
		cout << "\n";
	}
	cout << setfill('-') << setw(80) << "-" << "\n";
	cout << setfill(' ');
	cout << "\n";
	cout << "[OK] View List Student OK\n";
	
	cout << "\n";
	cout << "### TEST VIEW ATTENDANCE LIST\n";

	id = getInt("Index Coures");
	vector<Attendance> Attendance_list;

	Attendance_list = app->GetAttendanceList(course_list[id - 1]);

	cout << ">> Attendance List Of Course " << course_list[id - 1] << "\n";
	cout << "\n";

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
	cout << setfill(' ');
}


void Notyet() {
	cout << "Feature Will Coming Soon...\n";
}
int main() {
	vector<pair<int, string>> menu;
	menu.push_back(make_pair(1, "Login"));
	menu.push_back(make_pair(6, "Import Class"));
	menu.push_back(make_pair(7, "Add New Student To Class"));
	menu.push_back(make_pair(8, "Edit Student From Class"));
	menu.push_back(make_pair(9, "Remove Student From Class"));
	menu.push_back(make_pair(10, "Change Student Between Two Class"));
	menu.push_back(make_pair(11, "View List Class"));
	menu.push_back(make_pair(12, "View List Of Student In A Class"));
	menu.push_back(make_pair(14, "Import Course"));
	menu.push_back(make_pair(15, "Add New Course"));
	menu.push_back(make_pair(18, "Remove Student From Course"));
	menu.push_back(make_pair(19, "Add Student To Course"));
	menu.push_back(make_pair(20, "View Course List"));
	menu.push_back(make_pair(21, "View List Of Student In A Course"));
	menu.push_back(make_pair(22, "View Attendance List Of A Course"));

	cout << "          DEMO SMSys\n\n";
	for (int i = 0; i < menu.size(); ++i) {
		cout << menu[i].first << ". " << menu[i].second << "\n";
	}

	cout << "\n";

	int opt = getInt("Enter Index Feature Wanna Test");
	cout << "\n";
	switch(opt) {
		case 1:
			TestLogin();
			break;
		case 2:
		case 3:
		case 4:
			Notyet();
			break;
		case 5:
			// TestLogout();
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
		case 12:
			TestViewListClass();
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
			Notyet();
			break;
		case 17:
			Notyet();
			break;
		case 18:
			TestRemoveStudentFromCourse();
			break;
		case 19:
			TestAddStudentToCourse();
			break;
		case 20:
		case 21:
		case 22:
			TestViewCourseList();
			break;
		default:
			Notyet();
			break;
	}
}
