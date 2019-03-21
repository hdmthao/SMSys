#ifndef DATA_COURSE_H
#define DATA_COURSE_H

#include <string>

using std::string;

struct Course {
	string ID;
	string name;
	string lecturer;
	string start_date;
	string end_date;
};

#endif
