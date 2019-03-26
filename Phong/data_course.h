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

struct Score {
	int ID;
	string first_name, last_name, GPA;
	float Score1, Score2, Score3, midTerm, Final;
};
#endif
