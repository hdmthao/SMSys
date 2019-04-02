#if defined(_WIN32) || defined(WIN32)
    #include <windows.h>
    #include <dirent.h>
#else
    #include <sys/types.h>
    #include <sys/stat.h>
	#include <dirent.h>
#endif

#include "helper.h"
#include "path.h"
#include <string.h>
#include <iostream>
#include <time.h>

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


void Helper::RemoveDir(const string &dir_name) {
	DIR* dir;
	struct dirent* str;
	string path_to_dir = Path::COURSE + dir_name + "/";

	dir = opendir(path_to_dir.c_str());
	while ((str = readdir(dir)) != nullptr) {
		// just . && ..
		if (strcmp(str->d_name, ".") == 0 || strcmp(str->d_name, "..") == 0) continue;
		string path = path_to_dir;
		path += string(str->d_name);
		struct stat s;
		stat(path.c_str(), &s);

		if (s.st_mode & S_IFREG) {
			path = path.substr(0, path.length());
			remove(path.c_str());
		}
	}
	closedir(dir);
	remove(path_to_dir.c_str());
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

Attendance Helper::stringToAttendance(string a) {

	if (!a.empty())
	{
		Attendance x;
		string ID;
		int count = 0;
		for (int i = 0; i < a.length(); i++)
		{
			if (a.at(i) == ' ') count++;
			else
			{
				if (count == 0) ID.push_back(a.at(i));
				if (count == 1) x.first_name.push_back(a.at(i));
				if (count == 2) x.last_name.push_back(a.at(i));
				if (count >= 3)
				{
					if (a.at(i) == '1') x.week.push_back(1);
					if (a.at(i) == '0') x.week.push_back(0);
				}
			}
		}
		Attendance result;
		for (int i = 0; i < 20; i += 2)
		{
			result.week.push_back(x.week.at(i) + x.week.at(i + 1));
		}
		result.ID = stoi(ID);
		result.first_name = x.first_name;
		result.last_name = x.last_name;
		ConvertStringToSpace(result.last_name);
		return result;
	}
	else
	{
		Attendance x;
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


string Helper::GetFullName(const string &first_name, const string &last_name) {
    return last_name + " " + first_name;
}

Period Helper::GetCurrentPeriod() {
	time_t rawtime;
	struct tm * timeinfo;

	time (&rawtime);
	timeinfo = localtime (&rawtime);
    string ti = asctime(timeinfo);

	Period current_period;
	// Get Day of week
	string dow = ti.substr(0, 3);
	std::cout << dow;
	return current_period;
}

string Helper::GetCurrentTime() {
	time_t rawtime;
	struct tm * timeinfo;

	time (&rawtime);
	timeinfo = localtime (&rawtime);
	string cur_time = asctime(timeinfo);
	return cur_time;
}

int Helper::ConvertDoW(string &Dow_str){
	int DoW = 0;
	DoW += 2 * (Dow_str == "Mon");
	DoW += 3 * (Dow_str == "Tue");
	DoW += 4 * (Dow_str == "Wed");
	DoW += 5 * (Dow_str == "Thu");
	DoW += 6 * (Dow_str == "Fri");
	DoW += 7 * (Dow_str == "Sat");
	return DoW;
}

int Helper::ConvertDoM(string &Dom_str){
	int DoM = 0;
	DoM += 1 * (Dom_str == "Jan");
	DoM += 2 * (Dom_str == "Feb");
	DoM += 3 * (Dom_str == "Mar");
	DoM += 4 * (Dom_str == "Apr");
	DoM += 5 * (Dom_str == "May");
	DoM += 6 * (Dom_str == "Jun");
	DoM += 7 * (Dom_str == "Jul");
	DoM += 8 * (Dom_str == "Aug");
	DoM += 9 * (Dom_str == "Sep");
	DoM += 10 * (Dom_str == "Oct");
	DoM += 11 * (Dom_str == "Nov");
	DoM += 12 * (Dom_str == "Dec");
	return DoM;
}

int Helper::GetCurrentShift(string &cur_time){
	string timeGet = "";
	timeGet += cur_time[11];
	timeGet += cur_time[12];
	return ((timeGet > "00") + (timeGet >= "09") + (timeGet >= "13") + (timeGet >= "15"));
}

int Helper::GetCurrentDoW(string &cur_time){
	string getDoW = cur_time;
	getDoW.resize(3);
	return Helper::ConvertDoW(getDoW);
}

int Helper::GetCurrentWeek(string &cur_time, string &start_time){
	// Mon Jan 13 15:16:51 2019
	// 1/1/2019
	string cur_month_str = "";
	int cur_month = 0;
	int cur_day = 0;
	int start_day = 0;
	int start_month = 0;
// convert cur_time	
	cur_month_str += cur_time[4];
	cur_month_str += cur_time[5];
	cur_month_str += cur_time[6];
	cur_month = ConvertDoM(cur_month_str);
	cur_day = 10 * (cur_time[8] != ' ') * (cur_time[8] - '0') + (cur_time[9] - '0');
// convert start_day
	
	int index = 0;
	while (index < start_time.length()) {
		if (start_time[index] == '/') {
			++index;
			break;
		}
		start_day = start_day * 10 + start_time[index] - '0';
		++index;
	}
	while (index < start_time.length()) {
		if (start_time[index] == '/') {
			break;
		}
		start_month = start_month * 10 + start_time[index] - '0';
		++index;
	}
// process
	int cnt_cur = 0;
	int cnt_start = 0;
	int DoM[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // day of month

	for (int i = 0; i < cur_month - 1; i++)
		cnt_cur += DoM[i];
	cnt_cur += cur_day;

	for (int i = 0; i < start_month - 1; i++)
		cnt_start += DoM[i];
	cnt_start += start_day;
	
	return ( cnt_cur - cnt_start) / 7 + 1 ;
}

