#ifndef HELPER_H
#define HELPER_H

#include <string>
#include "data_student.h"
#include "data_account.h"

using std::string;

class Helper {
public:
    static string StringToUpper(const string &);
    static void ConvertLastNameToDash(string &);
    static void ConvertLastNameToSpace(string &);
    static void MakeClassDir(const string &);
    static void NormalizeStudent(Student &student);
    static void UpperFirstCharOfLetter(string &str);
    static void FormatDay(string &str);
    static UserRole FormatIntToRole(int &role);
};
#endif