#include "app.h"

bool App::EditStudent(string class_name, const Student & student){
	bool done = 0;
	//class_name = "18CTT1";
	string tmpPath = "data/class/" + class_name + "/student.txt";
	vector <Student> studentList;
	// Get_data and Edit
	ifstream in;
	in.open(tmpPath);
	Student tmpStu;
	while (in >> tmpStu.ID >> tmpStu.first_name >> tmpStu.last_name >> tmpStu.gender >> tmpStu.dob >> tmpStu.email) {
		studentList.push_back(tmpStu);
		if (studentList.back().ID == student.ID) {
			studentList.back() = student;
			done = 1;
		}
	}
	in.close();

	// Rewrite data
	ofstream out;
	out.open(tmpPath);
	for (int i = 0; i < studentList.size(); i++) {
		out << studentList[i].ID << " " << studentList[i].first_name << " " << studentList[i].last_name << " " << studentList[i].gender << " " << studentList[i].dob << " " << studentList[i].email << "\n";
	}
	studentList.clear();
	out.close();
	return done;
}

bool App::RemoveStudent(string class_name, const int & ID){
	int done = 0;
	vector <Student> studentList;
	Student tmpStu;
// Remove from data/class/ / student.txt	
	//class_name = "18CTT1";
	string tmpPath = "data/class/" + class_name + "/student.txt";
	// Get_data and Delete
	ifstream in;
	in.open(tmpPath);
	while (in >> tmpStu.ID >> tmpStu.first_name >> tmpStu.last_name >> tmpStu.gender >> tmpStu.dob >> tmpStu.email) {
		studentList.push_back(tmpStu);
		if (studentList.back().ID == ID) {
			studentList.pop_back();
			++done;
		}
	}
	in.close();

	// Rewrite data
	ofstream out;
	out.open(tmpPath);
	for (int i = 0; i < studentList.size(); i++) {
		out << studentList[i].ID << " " << studentList[i].first_name << " " << studentList[i].last_name << " " << studentList[i].gender << " " << studentList[i].dob << " " << studentList[i].email << "\n";
	}
	studentList.clear();
	out.close();
// Remove from data/student/student.txt
	//Get data and Delete
	tmpPath = "data/student/students.txt";
	in.open(tmpPath);
	while (in >> tmpStu.ID >> tmpStu.class_name) {
		studentList.push_back(tmpStu);
		if (tmpStu.ID == ID && tmpStu.class_name == class_name) {
			studentList.pop_back();
			++done;
		}
	}
	in.close();
	// Rewrite Data 
	out.open(tmpPath);
	for (int i = 0; i < studentList.size(); i++) {
		out << studentList[i].ID << " " << studentList[i].class_name << "\n";
	}
	studentList.clear();
	out.close();
	return done == 2; // delete from 2 file
}
