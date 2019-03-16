#ifndef HELPER_H
#define HELPER_H

#include <string>

using std::string;

class Helper {
public:
    static string StringToUpper(const string &);
    static void ConvertLastNameToDash(string &);
    static void ConvertLastNameToSpace(string &);
    static void MakeClassDir(const string &);
};
#endif