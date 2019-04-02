#ifndef HELPER_H
#define HELPER_H

#include "data_student.h"
#include "data_account.h"
#include "data_attendance.h"
#include "data_period.h"

#include <vector>
#include <string>

using std::string;
using std::vector;


class Helper {
public:
    static string StringToUpper(const string &);
    static void ConvertStringToDash(string &);
    static void ConvertStringToSpace(string &);
    static void MakeDir(const string &);
    static void RemoveDir(const string &);
    static void NormalizeStudent(Student &student);
    static void UpperFirstCharOfLetter(string &str);
    static void FormatDay(string &str);
    static UserRole FormatIntToRole(int &role);
    static Student stringToStudent(string a, string classname);
    static Attendance stringToAttendance(string a);
    static void GetFileInFolder(vector<string> &lists, string &path);
    static string GetFullName(const string &first_name, const string &last_name);

    static Period GetCurrentPeriod();
    static string GetCurrentTime();

private:
	static const int DoM[12];
    static int ConvertDoW(string &Dow_str);
	static int ConvertDoM(string &Dom_str);

public:
	static int GetCurrentShift(string &cur_time);
	static int GetCurrentDoW(string &cur_time);
	static int GetCurrentWeek(string &cur_time, string &start_time);
};
#endif