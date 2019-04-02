#include "app.h"
#include "helper.h"

#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include <chrono>
#include <ctime>
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
	cout << "### TEST IMPORT CLASS\n\n";

	vector<string> list_import = app->GetCsvForClass();
	cout << "List Of CSV file\n";
	for (int i = 0; i < list_import.size(); ++i) {
		cout << i + 1 << ". " << list_import[i] << "\n";
	}
	cout << "\n";
	int id = getInt("Index CSV file you wanna import");
	string new_class_name = getString("Ten Lop Moi");

	cout << "\n";
	if (app->ImportClass(new_class_name, list_import[id - 1])) {
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
	cout << "[RUN] TEST REMOVE STUDENT FROM CLASS\n\n";
	int id;
	id = getInt(">> Remove ID");
	cout << "\n";
	if (app->RemoveStudentFromClass(id)) {
		cout << ">> Remove OK\n";
	} else {
		cout << ">> Remove FAIL\n";
	}

	cout << "[DONE] TEST REMOVE STUDENT FROM CLASS\n";
	cout << "Press Enter";
	cin.ignore();
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
	cout << "[RUN] TEST IMPORT COURSE\n\n";

	vector<string> list_import = app->GetCsvForCourse();

	cout << ">> List Of CSV file\n";
	for (int i = 0; i < list_import.size(); ++i) {
		cout << i + 1 << ". " << list_import[i] << "\n";
	}
	cout << "\n";
	int id = getInt("Index CSV file you wanna import");

	if (app->ImportCourse(list_import[id - 1])) {
		cout << "[OK] Import Course OK\n";
	} else {
		cout << "[X]  Import Course FAIL\n";
	}
	cout << "\n";
	cout << "[DONE] TEST IMPORT COURSE\n";
	cout << "Press Enter";
	cin.ignore();
}

void TestAddNewCourse() {
	cout << "[RUN] TEST ADD NEW COURSE\n\n";

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
	cout << "\n";
	cout << "[DONE] TEST ADD NEW COURSE\n";
	cout << "Press Enter";
	cin.ignore();
}

void TestAddStudentToCourse() {
	cout << "[RUN] TEST ADD STUDENT TO COURSE\n";

	int student_id = getInt("student id");
	string course_id = getString("course id");

	if (app->AddStudentToCourse(course_id, student_id)) {
		cout << ">> Add student id " << student_id << " to course " << course_id << "\n";
	} else {
		cout << ">> Student not existed or existed in course\n";
	}
	cout << "\n";
	cout << "[DONE] TEST ADD STUDENT TO COURSE\n";
	cout << "Press Enter";
	cin.ignore();
}

void TestRemoveStudentFromCourse() {
	cout << "[RUN] TEST REMOVE STUDENT FROM COURSE\n";

	int del_student = getInt("Student ID");
	string course_id = getString("Coures ID");

	if (app->RemoveStudentFromCourse(course_id, del_student)) {
		cout << ">> Remove stunde id " << del_student << " from course " << course_id << "\n";
	} else {
		cout << ">> Student not existed\n";
	}

	cout << "\n";
	cout << "[DONE] TEST REMOVE STUDENT FROM COURSE\n";
	cout << "Press Enter";
	cin.ignore();
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


void TestRemoveCourse() {
	cout << "[RUN] TEST REMOVE COURSE\n\n";

	vector<string> course_list;
	course_list = app->GetCourselist();
	cout << ">> List of course\n";
	for (int i = 0; i < course_list.size(); ++i) {
		cout << i + 1 << ". " << course_list[i] << "\n";
	}
	cout << "\n";

	int id = getInt("Index Course Wanna Remove");

	if (app->RemoveCourse(course_list[id - 1])) {
		cout << ">> Remove Course " << course_list[id - 1] << " OK\n";
	} else {
		cout << ">> Remove Course " << course_list[id - 1] << " FAILD\n";
	}

	cout << "\n";
	cout << "[DONE] REMOVE COURSE\n";
	cout << "Press Enter";
	cin.ignore();
}


void TestEditCourses() {
	cout << "### TEST EDIT COURSE\n";

	vector<string> course_list;
	course_list = app->GetCourselist();
	cout << ">> List Of Course\n";
	for (int i = 0; i < course_list.size(); ++i) {
		cout << i + 1 << ". " << course_list[i] << "\n";
	}
	cout << "\n";

	int id = getInt("Index Course Wanna edit");
	Course course = app->GetCourseInfo(course_list[id - 1]);
	cout << "\n";
	cout << "Course Info\n";
	cout << course.ID << " " << course.name << " " << course.lecturer << " " << course.start_date << " " << course.end_date << "\n\n";
	int option = getInt("Do you want edit name of course (\'yes\' enter 1, \'no\' enter 0)");
	if (option) {
		course.name = getString("New course name");
	}

	option = getInt("Do you want edit start date of course");
	if (option) {
		course.start_date = getString("New start date");
	}

	option = getInt("Do you want edit end date of course");
	if (option) {
		course.end_date = getString("New end date");
	}

	if (app->EditCourse(course)) {
		cout << ">> Edit course OK\n";
	} else {
		cout << ">> Edit course Fail\n";
	}

	cout << "\n";
	cout << "[OK] Test Edit Course OK\n";
}


void TestSearchAndViewCourse() {
	cout << "### TEST SEARCH AND VIEW COURSE\n\n";

	string find_id = getString("Enter ID wanna search");

	vector<string> course_list;

	course_list = app->SearchCourse(find_id);

	if (course_list.size() == 0) {
		cout << "\n";
		cout << "No Course Match!!!\n";
	} else {
		cout << ">> List Of Course Impossible\n";
		for (int i = 0; i < course_list.size(); ++i) {
			cout << i + 1 << ". " << course_list[i] << "\n";
		}
		cout << "\n";
		int id = getInt("Select ID Wanna to view Scoreboard");
		cout << "\n";
	}

	// view list scoreboard
	cout << "\n";
	cout << "[OK] Test Search and View Course OK\n";
	cout << "PRESS ENTER";
	cin.ignore();
}


void TestSearchAndViewAttendance() {
	cout << "[RUN] TEST SEARCH AND VIEW ATTENDANCE\n\n";

	string find_id = getString("Enter ID wanna search");

	vector<string> course_list;

	course_list = app->SearchCourse(find_id);

	if (course_list.size() == 0) {
		cout << "\n";
		cout << "No Course Match!!!\n";
	} else {
		cout << ">> List of courses match\n";
		for (int i = 0; i < course_list.size(); ++i) {
			cout << i + 1 << ". " << course_list[i] << "\n";
		}
		cout << "\n";
		int id = getInt("Select ID wanna to view attendance");

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

	cout << "\n";
	cout << "[DONE] TEST SEARCH AND VIEW ATTENDANCE\n";
	cout << "PRESS ENTER";
	cin.ignore();

}

void TestExportScoreboard() {
	cout << "[RUN] TEST EXPORT SCOREBOARD\n\n";

	cout << ">> List of course\n\n";

	vector<string> course_list;

	course_list = app->GetCourselist();

	if (course_list.size() == 0) {
		cout << "No course to export scoreboard\n";
	} else {
		for (int i = 0; i < course_list.size(); ++i) {
			cout << i + 1 << ". " << course_list[i] << "\n";
		}
		cout << "\n";
		int id = getInt("Index course wanna export scoreboard");
		if (app->ExportScoreboard(course_list[id - 1])) {
			cout << ">> Export file save to \\export\\" << course_list[id - 1] << "_scoreboard.txt" << "\n";
			cout << ">> Export scoreboard of course " << course_list[id - 1] << " OK\n";
		} else {
			cout << ">> Export FAIL!!!\n";
		}
	}
	cout << "\n";
	cout << "[DONE] TEST EXPORT SCOREBOARD\n";
	cout << "Press Enter";
	cin.ignore();
}

void TestExportAttendance() {
	cout << "[RUN] TEST EXPORT ATTENDANCE\n\n";

	cout << ">> List of course\n\n";

	vector<string> course_list;

	course_list = app->GetCourselist();

	if (course_list.size() == 0) {
		cout << "No course to export attendance\n";
	} else {
		for (int i = 0; i < course_list.size(); ++i) {
			cout << i + 1 << ". " << course_list[i] << "\n";
		}
		cout << "\n";
		int id = getInt("Index course wanna export attendance");
		if (app->ExportAttendance(course_list[id - 1])) {
			cout << ">> Export file save to \\export\\" << course_list[id - 1] << "_attendance.csv" << "\n";
			cout << ">> Export attendace of course " << course_list[id - 1] << " OK\n";
		} else {
			cout << ">> Export FAIL!!!\n";
		}
	}
	cout << "\n";
	cout << "[DONE] TEST EXPORT ATTENDACNE\n";
	cout << "Press Enter";
	cin.ignore();
}

void TestCheckIn() {
	cout << "[RUN] TEST CHECKIN\n\n";
	cout << ">> YOU MUST LOGIN FIRST\n";

	string user_name = "18126039";
	string password = "18126039";

	if (app->Login(user_name, password)) {
		cout << ">> Login OK\n\n";
		
		string check_in_status = app->CheckIn();
		cout << ">> " << check_in_status << "\n\n";
	} else {
		cout << ">> Login FAIL\n\n";
	}

	cout << "[DONE] TEST CHECK-IN\n";
	cout << "Press Enter";
	cin.ignore();
}

void TestViewCheckInResult() {
	cout << "[RUN] TEST VIEW CHECK-IN RESULT\n\n";
	cout << ">> YOU MUST LOGIN FIRST\n";

	string user_name = "18126039";
	string password = "18126039";

	if (app->Login(user_name, password)) {
		cout << ">> Login OK\n\n";

		vector<Attendance> Attendance_list = app->ViewCheckInResult(); 
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
	} else {
		cout << ">> Login FAIL\n\n";
	}
	cout << "\n";
	cout << "[DONE] TEST VIEW CHECK-IN RESULT\n";
	cout << "Press Enter";
	cin.ignore();
}

void TestViewSchedules() {
	cout <<"[RUN] TEST STUDENT VIEW SCHEDULE\n\n";
	cout << ">> YOU MUST LOGIN FIRST\n";

	// string user_name = getString("User Name");
	// string password = etString("password");
	string user_name = "18126039";
	string password = "18126039";

	if (app->Login(user_name, password)) {
		cout << ">> Login OK!!!\n\n";
		cout << ">> Schedule of student " << user_name << "\n\n";
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

	} else {
		cout << ">> Login FAIL\n\n";
	}

	cout << "\n";
	cout << "[DONE] TEST STUDENT VIEW SCHEDULE\n";
	cout << "Press Enter";
	cin.ignore();
}

void TestViewScoresOfACourse() {
	cout << "[RUN] TEST VIEW HIS/HER SCORES OF A COURSE\n\n";
	cout << ">> YOU MUST LOGIN FIRST\n";

	// string user_name = getString("User Name");
	// string password = etString("password");
	string user_name = "18126039";
	string password = "18126039";
	if (app->Login(user_name, password)) {
		cout << ">> Login OK\n\n";
		cout << ">> Scoreboard of student " << user_name << "\n\n";
	 	vector<Score> scoreboard;

		scoreboard = app->ViewScoreboard();

		cout << "| " << setw(15) << left << "COURSE_ID";
		cout << "| " << setw(10) << left << "MIDTERM";
		cout << "| " << setw(10) << left << "LAB";
		cout << "| " << setw(10) << left << "ABCF";
		cout << "| " << setw(10) << left << "BONUS";
		cout << "| " << setw(10) << left << "FINAL";
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
	} else {
		cout << ">> Login FAIL\n";
	}

	cout << "\n";
	cout << "[DONE] TEST VIEW HIS/HER SCORES OF A COURSE\n";
	cout << "Press Enter";
	cin.ignore();
}

void Notyet() {
	cout << "Feature Will Coming Soon...\n";
	cout << "Press Enter";
	cin.ignore();
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
	menu.push_back(make_pair(16, "Edit Course"));
	menu.push_back(make_pair(17, "Remove Course"));
	menu.push_back(make_pair(18, "Remove Student From Course"));
	menu.push_back(make_pair(19, "Add Student To Course"));
	menu.push_back(make_pair(20, "View Course List"));
	menu.push_back(make_pair(21, "View List Of Student In A Course"));
	menu.push_back(make_pair(22, "View Attendance List Of A Course"));
	menu.push_back(make_pair(24, "Search and View Scoreboard of a course"));
	menu.push_back(make_pair(25, "Export scoreboard"));
	menu.push_back(make_pair(26, "Search and View Attendance of a course"));
	menu.push_back(make_pair(27, "Export Attendance"));
	menu.push_back(make_pair(35, "Check-in"));
	menu.push_back(make_pair(36, "View check-in result"));
	menu.push_back(make_pair(37, "View Schedules"));
	menu.push_back(make_pair(38, "View his/her scores of a course"));

	while (1) {
	cout << "          DEMO SMSys\n\n";
	for (int i = 0; i < menu.size(); ++i) {
		cout << menu[i].first << ". " << menu[i].second << "\n";
	}
	cout << 0 << ". EXIT\n";
	cout << "\n";

	int opt = getInt("Enter Index Feature Wanna Test");
	cout << "\n";
	if (opt == 0) break;
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
		case 21:
		case 22:
			TestViewCourseList();
			break;
		case 24:
			TestSearchAndViewCourse();
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
			Notyet();
			break;
	}
	}
}
