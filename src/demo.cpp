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

	if (app->ChangeStudentFromClassAToB(id, class_b)) {
		cout << "Chuyen thanh cong id " << id << " sang lop " << class_b << "\n";
	} else {
		cout << "Khong ton tai id " << id << " hoac lop " << class_b << "\n";
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

int main() {
	
	// TestLogin();
	// TestImportClass();
	// TestAddNewStudent();
	// TestChangeStudent();
	// TestRemoveStudent();
	TestEditStudent();
}
