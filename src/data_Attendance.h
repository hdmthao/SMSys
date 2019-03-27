#ifndef DATA_ATTENDANCE_H
#define DATA_ATTENDANCE_H

#include <string>
#include <vector>
using std::string;
using std::vector;

struct Attendance {
	string StudentID;
	vector<int> week;
};

#endif
