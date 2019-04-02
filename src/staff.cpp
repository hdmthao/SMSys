#include "staff.h"
#include "path.h"
#include "generator.h"
#include "helper.h"

#include <fstream>
#include <iostream>
#include <set>
#include <vector>

using std::ios;
using std::vector;
using std::pair;
using std::ofstream;
using std::ifstream;
using std::getline;
using std::set;
using std::cout;


Staff::Staff() {

}


Staff::~Staff() {

}


bool Staff::ImportClass(const string &class_name, const string &csv_name) {
    string new_class_name = Helper::StringToUpper(class_name);
    string path_to_class_dir = Path::CLASS + new_class_name;
    string path_to_class = path_to_class_dir + "/student.txt";
    string path_to_csv = Path::IMPORT_STUDENT + csv_name;

    const bool is_existed_class = AddNewClass(new_class_name);

    if (!is_existed_class) { // if class not existed then make new folder for it
        Helper::MakeDir(path_to_class_dir);
    }

    // get student existed in class to check existed student
    set<int> ID_list;
    
    ifstream fi(Path::ALL_STUDENT);

    if (fi.is_open()) {
        int id;
        string class_name;
        while (fi >> id && fi >> class_name) {
            ID_list.insert(id);
        }
    }
    fi.close();

    // bat dau mo file csv va ghi vao file txt
    fi.open(path_to_csv);
    if (fi.is_open()) {
        ofstream fo_class_student(path_to_class, ios::app);
        ofstream fo_all_student(Path::ALL_STUDENT, ios::app);
        ofstream fo_account(Path::ACCOUNT, ios::app);
        string no, id;
        Student student;

        // Get the header of csv file
        getline(fi, no, ','); getline(fi, id, ','); getline(fi, student.last_name, ',');
        getline(fi, student.first_name, ','); getline(fi, student.gender, ','); getline(fi, student.dob);

        while (getline(fi, no, ',')) {
            getline(fi, id, ',');
            getline(fi, student.last_name, ',');
            getline(fi, student.first_name, ',');
            getline(fi, student.gender, ',');
            getline(fi, student.dob);

            student.dob.pop_back(); // bo ki tu rac
            student.ID = std::stoi(id); // chuyen id tu string sang INT

            const bool is_existed_id = ID_list.find(student.ID) != ID_list.end();  // da co trong danh sach student

            if (is_existed_id == false) {
                student.email = Generator::generateEmail(student.last_name, student.first_name);

                
                // add student to student list of class and list of all student
                CreateStudent(fo_class_student, fo_all_student, student, new_class_name);

                // Create Account -- username : ID -- password defaul : ID
                CreateAccount(fo_account, student.ID, id, id, UserRole::STUDENT);

                cout << ">> Add ID " << student.ID << " OK\n";
            } else {
                cout << ">> ID " << student.ID << " Existed\n";
            }
        }
        fo_class_student.close();
        fo_all_student.close();
        return true;
    } else {
        return false;
    }
    
    fi.close();
}


bool Staff::AddNewStudentToClass(const string &class_name, Student &new_student) {
    string new_class_name = Helper::StringToUpper(class_name);
    string path_to_class = Path::CLASS + new_class_name + "/student.txt";

    // get student existed in class to check existed student
    set<int> ID_list;
    
    ifstream fi(Path::ALL_STUDENT);

    if (fi.is_open()) {
        int id;
        string class_name;
        bool is_existed = false;
        while (fi >> id && fi >> class_name) {
            if (id == new_student.ID) {
                is_existed = true;
                break;
            }
        }
        if (is_existed) {
            cout << ">> ID " << new_student.ID << " Existed.\n";
            return false;
        }
    }
    fi.close();

    ofstream fo_class_student(path_to_class, ios::app);
    ofstream fo_all_student(Path::ALL_STUDENT, ios::app);
    ofstream fo_account(Path::ACCOUNT, ios::app);
    
    new_student.email = Generator::generateEmail(new_student.last_name, new_student.first_name);

    CreateStudent(fo_class_student, fo_all_student, new_student, new_class_name);
    
    string id = std::to_string(new_student.ID); // convert int to string
    CreateAccount(fo_account, new_student.ID, id, id, UserRole::STUDENT);

    fo_class_student.close();
    fo_all_student.close();
    fo_account.close();

    cout << ">> Add ID " << new_student.ID << " OK\n";
    return true;
}


bool Staff::ChangeStudentFromClassAToB(const int &id, string &class_b) {
    const string class_a = FindClassWithID(id);
    class_b = Helper::StringToUpper(class_b);

    if (class_a == "" || class_b == "") {
        cout << ">> Class Not Exist\n";
        return false; // ko ton tai 2 lop nay
    }

    if (class_a == class_b) { // hoc sinh da ton tai trong lop b
        cout << ">> Student Was Existed In " << class_b << "\n";
        return false;
    }

    if (!ClassExisted(class_b)) { // khong ton tai lop can chuyen den
        cout << ClassExisted(class_b) << "\n";
        cout << ">> Class " << class_b << " Not Exist\n";
        return false;
    }
    // change class_a in  file all student to class_b
    vector<pair<int, string>> vec;
    
    ifstream fi_all_student(Path::ALL_STUDENT);

    int ID;
    string class_name;

    while (fi_all_student >> ID >> class_name) {
        if (ID == id) class_name = class_b;
        vec.push_back(std::make_pair(ID, class_name));
    }
    fi_all_student.close();

    // ghi lai vo file all student 
    ofstream fo_all_student(Path::ALL_STUDENT);

    while (!vec.empty()) {
        fo_all_student << vec.back().first << " " << vec.back().second << "\n";
        vec.pop_back();
    }

    fo_all_student.close();

    // xoa student khoi class A
    string tmp_path = Path::CLASS + class_a + "/student.txt";
    ifstream fi_class_student(tmp_path);

    vector<Student> student_list;
    Student tmp_student;
    Student student_will_move;
    while (fi_class_student >> tmp_student.ID >> tmp_student.first_name >> tmp_student.last_name >>
            tmp_student.gender >> tmp_student.dob >> tmp_student.email) {
                if (tmp_student.ID == id) {
                    student_will_move = tmp_student;
                    continue;
                }
                student_list.push_back(tmp_student);
            }
    fi_class_student.close();

    // ghi lai du lieu cua class _ a
    ofstream fo_class_student(tmp_path);

    for (int i = 0; i < student_list.size(); ++i) {
        fo_class_student << student_list[i].ID << " " << student_list[i].first_name << " " << student_list[i].last_name << " " <<
            student_list[i].gender << " " << student_list[i].dob << " " << student_list[i].email << "\n";
    }
    student_list.clear();
    fo_class_student.close();

    tmp_path = Path::CLASS + class_b + "/student.txt";
    fo_class_student.open(tmp_path, ios::app);
    fo_class_student << student_will_move.ID << " " << student_will_move.first_name << " " << student_will_move.last_name << " " <<
        student_will_move.gender << " " <<  student_will_move.dob <<" " <<  student_will_move.email << "\n";
    fo_class_student.close();
    return true;
}


bool Staff::RemoveStudentFromClass(const int &ID){
	int done = 0;
	vector <Student> studentList;
	Student tmp_student;

    // Remove from data/class/ / student.txt	
	const string class_name = FindClassWithID(ID);
	string tmp_path = Path::CLASS + class_name + "/student.txt";

	// Get_data and Delete
	ifstream in(tmp_path);
	while (in >> tmp_student.ID >> tmp_student.first_name >> tmp_student.last_name >>
             tmp_student.gender >> tmp_student.dob >> tmp_student.email) {
		studentList.push_back(tmp_student);
		if (studentList.back().ID == ID) {
			studentList.pop_back();
			++done;
		}
	}
	in.close();

	// Rewrite data
	ofstream out;
	out.open(tmp_path);
	for (int i = 0; i < studentList.size(); i++) {
		out << studentList[i].ID << " " << studentList[i].first_name << " " << studentList[i].last_name << " " << studentList[i].gender << " " << studentList[i].dob << " " << studentList[i].email << "\n";
	}
	studentList.clear();
	out.close();
    // Remove from data/student/student.txt
	//Get data and Delete
	tmp_path = Path::ALL_STUDENT;
	in.open(tmp_path);
	while (in >> tmp_student.ID >> tmp_student.class_name) {
		studentList.push_back(tmp_student);
		if (tmp_student.ID == ID && tmp_student.class_name == class_name) {
			studentList.pop_back();
			++done;
		}
	}
	in.close();
	// Rewrite Data 
	out.open(tmp_path);
	for (int i = 0; i < studentList.size(); i++) {
		out << studentList[i].ID << " " << studentList[i].class_name << "\n";
	}
	studentList.clear();
	out.close();

    DeleteAccount(ID);

    // Students* students;
    // // vector<string> list = students->GetCourseList(ID);
    // delete students;
    // // for (int i = 0; i < list.size(); ++i) {
    // //     courses->RemoveStudentFromCourse(list[i], ID);
    // // }
	return done == 2; // delete from 2 file
}


bool Staff::EditStudentFromClass(Student &student){
	bool done = false;
    Helper::NormalizeStudent(student);
    Helper::ConvertStringToDash(student.last_name);

    const string class_name = FindClassWithID(student.ID);
    if (class_name == "") return false;
	string tmp_path = Path::CLASS + class_name + "/student.txt";
	vector <Student> studentList;
	// Get_data and Edit
	ifstream in;
	in.open(tmp_path);
	Student tmp_student;
	while (in >> tmp_student.ID >> tmp_student.first_name >> tmp_student.last_name >>
             tmp_student.gender >> tmp_student.dob >> tmp_student.email) {
		studentList.push_back(tmp_student);
		if (studentList.back().ID == student.ID) {
			studentList.back() = student;
			done = true;
		}
	}
	in.close();

    if (!done) return false;
	// Rewrite data
	ofstream out;
	out.open(tmp_path);
	for (int i = 0; i < studentList.size(); i++) {
		out << studentList[i].ID << " " << studentList[i].first_name << " " << studentList[i].last_name << " " << studentList[i].gender << " " << studentList[i].dob << " " << studentList[i].email << "\n";
	}
	studentList.clear();
	out.close();
	return true;
}


Student Staff::GetStudent(const int &ID) {
    const string class_name = FindClassWithID(ID);

    const string tmp_path = Path::CLASS + class_name + "/student.txt";

    ifstream fi(tmp_path);
    Student student;

    while (fi >> student.ID >> student.first_name >> student.last_name >>
            student.gender >> student.dob >> student.email) {
                if (student.ID == ID) {
                    fi.close();
                    return student;
                }
            }
}


vector<string> Staff::GetClassList() {
    vector<string> classes;
	ifstream fin(Path::CLASS_LIST);
	string class_name;
	if (fin.is_open()) {
		while (fin >> class_name) {
			classes.push_back(class_name);
		}
    }
	fin.close();
    return classes;
}


vector<Student> Staff::GetStudentListFromClass(string &class_name) {
    vector<Student> students_list;
    Helper::StringToUpper(class_name);
	string path = Path::CLASS + class_name + "/student.txt";
	ifstream fin(path, ios::app);
	if (fin.is_open()) {
		while (!fin.eof()) {
			string data_line;
			getline(fin, data_line);
			Student student;
			student = Helper::stringToStudent(data_line, class_name);
			if (student.ID == 0) break;
			students_list.push_back(student);
		}
    }
	fin.close();
    return students_list;
}

bool Staff::AddNewClass(const string &new_class_name) {

    if (ClassExisted(new_class_name)) {
        cout << "lop ton tai roi!!!\n";
        return true;
    }

    ofstream fo(Path::CLASS_LIST, ios::app);
    
    fo << new_class_name << "\n";
    cout << "Them lop " << new_class_name << " ok!!!\n";

    fo.close();
    return false;
}


bool Staff::ClassExisted(const string &new_class_name) {

    ifstream fi(Path::CLASS_LIST);

    if (!fi.is_open()) {
        return false;
    }

    string existed_class_name;
    bool existed = false;

    while (fi >> existed_class_name) {
        if (existed_class_name == new_class_name) {
            existed = true;
            break;
        } 
    }
    fi.close();

    return existed;
}


bool Staff::IsExistedStudent(const int &id_to_find) {
    ifstream fi(Path::ALL_STUDENT);

    if (!fi.is_open()) {
        return false; // ko ton tai id
    }
    int id;
    string class_name;
    while (fi >> id >> class_name) {
        if (id == id_to_find) {
            fi.close();
            return true;
        }
    }
    fi.close();
    return false; // ko ton tai id
}

string Staff::FindClassWithID(const int &id_to_find) {
    ifstream fi(Path::ALL_STUDENT);

    if (!fi.is_open()) {
        return ""; // ko ton tai id
    }
    int id;
    string class_name;
    while (fi >> id >> class_name) {
        if (id == id_to_find) {
            fi.close();
            return class_name;
        }
    }
    fi.close();
    return ""; // ko ton tai id
}


void Staff::CreateStudent(ofstream &fo_class_student, ofstream &fo_all_student, Student &student, const string &class_name) {
    Helper::NormalizeStudent(student);
    Helper::ConvertStringToDash(student.last_name);

    fo_class_student << student.ID << " " << student.first_name << " " << student.last_name <<
                        " " << student.gender << " " << student.dob << " " << student.email << "\n";
    fo_all_student << student.ID << " " << class_name << "\n";
}


void Staff::CreateAccount(ofstream &fo_account, const int &id, const string &user_name, const string &password, const UserRole &role){

	fo_account << id << " " << user_name << " " << Generator::generatePassword(password) <<
                 " " << role << " " << 1 << "\n"; // firsttime is true

}


void Staff::DeleteAccount(const int &id){
	vector <Account> ListAcc;
	Account cur_acc;
	int cur_role;

	ifstream in;
	in.open(Path::ACCOUNT);

	while (in >> cur_acc.ID >> cur_acc.username >> cur_acc.password >> cur_role >> cur_acc.firstTimeLogin) {
		if (id == cur_acc.ID)
			continue;
		cur_acc.role = Helper::FormatIntToRole(cur_role);
		ListAcc.push_back(cur_acc);
	}

	in.close();

	ofstream out;
	out.open(Path::ACCOUNT);

	while (!ListAcc.empty()) {
		out << ListAcc.back().ID << " " << ListAcc.back().username << " " << ListAcc.back().password << " " << ListAcc.back().role << " " << ListAcc.back().firstTimeLogin << "\n";
		ListAcc.pop_back();
	}

	out.close();
}


vector<string> Staff::GetCsvForClass() {
    vector<string> lists;
    string tmp_path = Path::IMPORT_STUDENT;
    Helper::GetFileInFolder(lists, tmp_path);
    return lists;
}


vector<string> Staff::GetCsvForCourse() {
    vector<string> lists;
    string tmp_path = Path::IMPORT_COURSE;
    Helper::GetFileInFolder(lists, tmp_path);
    return lists;
}


vector<string> Staff::GetCourselist() {
	vector<string> courses;
	ifstream fin(Path::COURSES_LIST);
	string course_name;
	if (fin.is_open()) {
		while (fin >> course_name) {
			courses.push_back(course_name);
		}
	}
	fin.close();
	return courses;
}


vector<Student> Staff::GetStudentListFromCourse(string &course_id) {
	vector<Student> students_list;
	Helper::StringToUpper(course_id);
	string path = Path::COURSE + course_id + "/student_info.txt";
	ifstream fin(path);
	if (fin.is_open()) {
		while (!fin.eof()) {
			string data_line;
			getline(fin, data_line);
			Student student;
			student = Helper::stringToStudent(data_line, "");
			if (student.ID == 0) break;
            Helper::ConvertStringToSpace(student.last_name);
			students_list.push_back(student);
		}
	}
	fin.close();
	return students_list;
}


vector<Attendance> Staff::GetAttendanceList(string &course_id) {
	vector<Attendance> attendance_list;
	Helper::StringToUpper(course_id);
	string path = Path::COURSE + course_id + "/attendance.txt";
	ifstream fin(path, ios::app);
	if (fin.is_open()) {
		while (!fin.eof()) {
			string data_line;
			getline(fin, data_line);
			Attendance attendance;
			attendance = Helper::stringToAttendance(data_line);
			if (attendance.ID == 0) break;
			attendance_list.push_back(attendance);
		}
	}
	fin.close();
	return attendance_list;
}

vector <Score> Staff::GetScoreBoard(string& course_id) {
	Helper::StringToUpper(course_id);
	vector<Score> ScoreBoard;
	string path = Path::COURSE + course_id + "/scoreboard.txt";
	ifstream fin(path);
	if (fin.is_open()) {
		while (!fin.eof()) {
			string data_line;
			getline(fin, data_line);
			Score score;
			score = Helper::stringToScore(data_line);
			if (score.ID == 0) break;
			ScoreBoard.push_back(score);
		}
	}
	fin.close();
	return ScoreBoard;
}