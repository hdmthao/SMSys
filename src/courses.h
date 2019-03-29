#ifndef COURSES_H
#define COURSES_H

#include "data_course.h"
#include "data_period.h"
#include "data_score.h"
#include "staff.h"

#include <string>
#include <vector>

using std::string;
using std::vector;


class Courses : private Staff {
private:
    bool ExistedCourse(const string &course_id);
    void AddNewCourseToDatabase(const string &course_id);

public:
    Courses();
    ~Courses();

    bool ImportCourse(const string &course_id, const string &csv_name);
    bool AddNewCourse(Course &new_course, string &class_name, int number_period, Period &period_1, Period &period_2);
    bool AddStudentToCourse(const string &course_id, const int student_id);
	bool RemoveStudentFromCourse(const string &course_id, const int student_id);
    bool RemoveCourse(string &course_id);
    bool EditCourse(Course &course);
    Course GetCourseInfo(string &course_id);
};

#endif