#include "helper.h"
#include <sys/types.h>
#include <sys/stat.h>

string Helper::StringToUpper(const string &str) {
    string new_string = str;

    for (int i = 0; i < str.length(); ++i) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            new_string[i] = str[i] - 'a' + 'A';
        }
    }

    return new_string;
}

void Helper::ConvertLastNameToDash(string &str) { // "ha duc minh thao" >> "ha-duc-minh-thao"
    for (int i = 0; i < str.length(); ++i) {
        if (str[i] == ' ') str[i] = '-';
    }
}

void Helper::ConvertLastNameToSpace(string &str) { // "ha-duc-minh-thao" >> "ha duc minh thao"
    for (int i = 0; i < str.length(); ++i) {
        if (str[i] == '-') str[i] = ' ';
    }
}
void Helper::MakeClassDir(const string &new_class_name) {
    #if defined(_WIN32) || defined(WIN32)
        _mkdir(new_class_name.c_str());
    #else
        mkdir(new_class_name.c_str(), 0733);
    #endif
}
