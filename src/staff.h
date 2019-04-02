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
    bool ClassExisted(const string &);
    bool AddNewClass(const string &); // them 1 class vo database
    string FindClassWithID(const int &);
	void CreateStudent(ofstream &fo_class_student, ofstream &fo_all_student, Student &student, const string &class_name);
    void CreateAccount(ofstream &fo_account, const int &id, const string &user_name, const string &password, const UserRole &role);
    void DeleteAccount(const int &id);

public:
    Staff();
    ~Staff();

    //For class
    bool ImportClass(const string &class_name, const string &csv);
    bool AddNewStudentToClass(const string &class_name, Student &new_student);
    bool ChangeStudentFromClassAToB(const int &id, string &class_b);
    bool RemoveStudentFromClass(const int &ID);
    bool EditStudentFromClass(Student &student);
    Student GetStudent(const int &ID);
    vector<string> GetClassList();
	vector<Student> GetStudentListFromClass(string &class_name);
    bool IsExistedStudent(const int &);
    vector<string> GetCsvForClass();
    vector<string> GetCsvForCourse();
    vector<string> GetCourselist();
	vector<Student> GetStudentListFromCourse(string &course_id);
	vector<Attendance> GetAttendanceList(string &course_id);
    vector<Score> GetScoreBoard(string &course_id);
};

#endif