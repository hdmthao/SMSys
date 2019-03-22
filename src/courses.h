#ifndef COURSES_H
#define COURSES_H

#include "data_course.h"
#include "data_period.h"

#include <string>
#include <vector>

using std::string;
using std::vector;


class Courses {
private:
    bool ExistedCourse(const string &course_id);
    void AddNewCourseToDatabase(const string &course_id);

public:
    Courses();
    ~Courses();

    bool ImportCourse(const string &course_id, const string &csv_name);  
};

#endif