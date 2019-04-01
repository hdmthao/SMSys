#ifndef DATA_LECTURER_H
#define DATA_LECTURER_H

#include <string>
#include <vector>
using std::string;
using std::vector;
class Lecturer {
public:
	string ID;
	string first_name;
	string last_name;
	int numOfCourse;
	vector<string> courses;

	Lecturer();
	~Lecturer();
	vector<string> GetLecturerList(string ID);
};

#endif
