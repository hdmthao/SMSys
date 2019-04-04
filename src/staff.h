#ifndef STAFF_H
#define STAFF_H

#include "data_student.h"
#include "data_account.h"
#include "data_attendance.h"
#include "data_score.h"

#include <vector>
#include <string>
#include <fstream>

using std::string;
using std::ofstream;
using std::vector;

class Staff {
private:
    static bool ClassExisted(const string &);
    static bool AddNewClass(const string &); // them 1 class vo database
    static bool FindClassWithID(const int &, string &class_name);
	static void CreateStudent(ofstream &fo_class_student, ofstream &fo_all_student, Student &student, const string &class_name);
    static void CreateAccount(ofstream &fo_account, const int &id, const string &user_name, const string &password, const UserRole &role);
    static void DeleteAccount(const int &id);

public:
    Staff();
    ~Staff();

    //For class
    static bool ImportClass(string &class_name, const string &csv);
    static bool AddNewStudentToClass(const string &class_name, Student &new_student);
    static bool EditStudentFromClass(Student &student);
    static bool RemoveStudentFromClass(const int &ID);
    static bool ChangeStudentFromClassAToB(const int &id, string &class_b);
    static vector<string> GetClassList();
	static vector<Student> GetStudentListFromClass(string &class_name);
    static bool GetStudent(const int &ID, Student &student);
    bool IsExistedStudent(const int &);
    static vector<string> GetCsvForClass();
    static vector<string> GetCsvForCourse();
	static vector<Student> GetStudentListFromCourse(string &course_id);
	static vector<Attendance> GetAttendanceList(string &course_id);
    static vector<Score> GetScoreBoard(string &course_id);
};

#endif