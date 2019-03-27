#if defined(_WIN32) || defined(WIN32)
    #include <windows.h>
    #include <dirent.h>
#else
    #include <sys/types.h>
    #include <sys/stat.h>
	#include <dirent.h>
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

void Helper::ConvertStringToDash(string &str) { // "ha duc minh thao" >> "ha-duc-minh-thao"
    for (int i = 0; i < str.length(); ++i) {
        if (str[i] == ' ') str[i] = '-';
    }
}

void Helper::ConvertStringToSpace(string &str) { // "ha-duc-minh-thao" >> "ha duc minh thao"
    for (int i = 0; i < str.length(); ++i) {
        if (str[i] == '-') str[i] = ' ';
    }
}

void Helper::MakeDir(const string &new_dir) {
    #if defined(_WIN32) || defined(WIN32)
        CreateDirectory(new_dir.c_str(), NULL);
    #else
        mkdir(new_dir.c_str(), 0733);
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
		ConvertStringToSpace(x.last_name);
		return x;
	}
	else
	{
		Student x;
		x.ID = 0;
		return x;
	}
}


void Helper::GetFileInFolder(vector<string> &lists, string &path) {
    DIR* dir;

    dir = opendir(path.c_str());
    struct dirent* ent;
    while ((ent = readdir(dir))) {
        std::string s = ent->d_name;
        if (s == "." || s == "..") continue;
        lists.push_back(s);
    }
    closedir(dir);
}