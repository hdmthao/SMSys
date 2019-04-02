#ifndef DATA_ATTENDANCE_H
#define DATA_ATTENDANCE_H

#include <string>
#include <vector>
using std::string;
using std::vector;

struct Attendance {
	int ID;
	string course_id;
	string first_name;
	string last_name;
	vector<int> week;
};

#endif
