#include "app.h"

#include <iostream>
#include <string>
#include <limits>

using std::cerr;
using std::cin;
using std::cout;
using std::string;

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

void TestAddNewStudent() {
	cout << "### TEST ADD NEW STUDENT\n";
	Student new_student;
	string class_name = getString("Lop Muon Add");
	new_student.ID = getInt("ID");
	new_student.first_name = getString("First Name");
	new_student.last_name = getString("Last Name)");
	new_student.gender = getString("Gender (male/female)");
	new_student.dob = getString("dob (dd/mm/yyyy");

	cout << "\n";

	if (app->AddNewStudent(class_name, new_student)) {
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

void TestRemoveStudent() {
	cout << "### TEST REMOVE STUDENT\n";
	int id;
	id = getInt("Remove ID");
	cout << "\n";
	if (app->RemoveStudent(id)) {
		cout << ">> Remove OK\n";
	} else {
		cout << ">> Remove FAIL\n";
	}
}

void TestEditStudent() {
	cout << "### TEST EDIT STUDENT\n";
	Student student;
	int id = getInt("id");
	student = app->GetStudent(id);
	
	cout << "\n";
	if (app->EditStudent(student)) {
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

	students_list = app->GetStudentList(class_list[id - 1]);
	cout << ">> List Student Of Class " << class_list[id - 1] << "\n";
	for (int i = 0; i < students_list.size(); ++i) {
		cout << students_list[i].ID << " " << students_list[i].first_name << " " << students_list[i].last_name << " " <<
			students_list[i].gender << " " << students_list[i].dob << " " << students_list[i].email << "\n";
	}

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

void TestAddStudent() {
	Courses Test;
	Test.AddStudent("CS162", 18125006);
	// Done
	cin.get();
}

void TestRemoveStudentfromCourse() {
	Courses Test;
	Test.RemoveStudent("CS162", 18125006);

}
int main() {
	
	// TestLogin();
	// TestImportClass();
	// TestAddNewStudent();
	// TestChangeStudent();
	// TestRemoveStudent();
	// TestEditStudent();
	// TestViewListClass();
	// TestGetCSVFile();
	// TestImportCourse();
	// TestAddNewCourse();
// New Feature
	// TestAddStudent(); 
	TestRemoveStudentfromCourse();
}
