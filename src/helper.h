#ifndef HELPER_H
#define HELPER_H

#include <string>
#include "data_student.h"
#include "data_account.h"
#include "data_attendance.h"

#include <vector>

using std::string;
using std::vector;


class Helper {
public:
    static string StringToUpper(const string &);
    static void ConvertStringToDash(string &);
    static void ConvertStringToSpace(string &);
    static void MakeDir(const string &);
    static void NormalizeStudent(Student &student);
    static void UpperFirstCharOfLetter(string &str);
    static void FormatDay(string &str);
    static UserRole FormatIntToRole(int &role);
    static Student stringToStudent(string a, string classname);
    static Attendance stringToAttendance(string a);
    static void GetFileInFolder(vector<string> &lists, string &path);
    static string GetFullName(const string &first_name, const string &last_name);
};
#endif