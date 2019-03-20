#if defined(_WIN32) || defined(WIN32)
    #include <windows.h>
#else
    #include <sys/types.h>
    #include <sys/stat.h>
#endif

#include "helper.h"


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
        CreateDirectory(new_class_name.c_str(), NULL);
    #else
        mkdir(new_class_name.c_str(), 0733);
    #endif
}

void Helper::NormalizeStudent(Student& student) {
    UpperFirstCharOfLetter(student.first_name);
    UpperFirstCharOfLetter(student.last_name);
    UpperFirstCharOfLetter(student.gender);
    FormatDay(student.dob);
}

void Helper::UpperFirstCharOfLetter(string &str) {
    for (int i = 0; i < str.length(); ++i) {
        
        if ((str[i] >= 'a' && str[i] <= 'z') && (i == 0 || str[i - 1] == ' ')) {
            str[i] = str[i] - 'a' + 'A';
        }
    }
}

void Helper::FormatDay(string &str) {
    for (int i = 0; i < str.length(); ++i) {
        if (str[i] >= '0' && str[i] <= '9') {
            continue;
        } else {
            str[i] = '/';
        }
    }
}

UserRole Helper::FormatIntToRole(int &role){
	switch (role) {
	case UserRole::LECTURER:
		return UserRole::LECTURER;

	case UserRole::STAFF:
		return UserRole::STAFF;

	case UserRole::STUDENT:
		return UserRole::STUDENT;

	default:
		break;
	}
}

Student Helper::stringToStudent(string a, string classname)
{
	if (!a.empty())
	{
		string id;
		Student x;
		int count = 0;
		for (int i = 0; i < a.length(); i++)
		{
			if (a.at(i) == ' ') count++;
			else
			{
				if (count == 0) id.push_back(a.at(i));
				if (count == 1) x.first_name.push_back(a.at(i));
				if (count == 2) x.last_name.push_back(a.at(i));
				if (count == 3) x.gender.push_back(a.at(i));
				if (count == 4) x.dob.push_back(a.at(i));
				if (count == 5) x.email.push_back(a.at(i));
			}
		}
		x.ID = stoi(id);
		x.class_name = classname;
		ConvertLastNameToSpace(x.last_name);
		return x;
	}
	else
	{
		Student x;
		x.ID = 0;
		return x;
	}
}