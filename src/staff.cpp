#include "staff.h"
#include "path.h"
#include "generator.h"
#include "helper.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <set>

using std::ios;
using std::vector;
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
        Helper::MakeClassDir(path_to_class_dir);
    }

    // get student existed in class to check existed student
    set<int> ID_list;
    
    ifstream fi(Path::STUDENTS);

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
        ofstream fo_all_student(Path::STUDENTS, ios::app);
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

                cout << "Them ID " << student.ID << " ok\n";
            } else {
                cout << "ID " << student.ID << " da ton tai\n";
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

    ifstream* fi = new ifstream(Path::CLASS_LIST);

    if (!fi->is_open()) {
        return false;
    }

    string old_class_name;
    bool existed = false;

    while (!fi->eof()) {
        *fi >> old_class_name;
        if (old_class_name == new_class_name) {
            existed = true;
            break;
        } 
    }
    fi->close();

    return existed;
}

void Staff::CreateStudent(ofstream &fo_class_student, ofstream &fo_all_student, Student &student, const string &class_name) {
    Helper::ConvertLastNameToDash(student.last_name);

    fo_class_student << student.ID << " " << student.first_name << " " << student.last_name <<
                        " " << student.gender << " " << student.dob << " " << student.email << "\n";
    fo_all_student << student.ID << " " << class_name << "\n";
}

void Staff::CreateAccount(ofstream &fo_account, const int &id, const string &user_name, const string &password, const UserRole &role){

	fo_account << id << " " << user_name << " " << Generator::generatePassword(password) <<
                 " " << role << " " << 1 << "\n"; // firsttime is true

}

