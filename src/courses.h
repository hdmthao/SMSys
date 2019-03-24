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
    bool AddNewCourse(Course &new_course, string &class_name, int number_period, Period &period_1, Period &period_2);
};

#endif