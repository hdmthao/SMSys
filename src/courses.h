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
    static bool ExistedCourse(const string &course_id);
    static void AddNewCourseToDatabase(const string &course_id);
    static bool AddStudentToStudentList(int ID, string &course_id);
    static bool RemoveStudentFromStudentList(int ID, const string &course_id);
    static bool RemoveCourseFromStudentList(const string &course_id);
public:
    Courses();
    ~Courses();

    static bool ImportCourse(const string &csv_name);
    static bool AddNewCourse(Course &new_course, string &class_name, int number_period, Period &period_1, Period &period_2);
    static bool EditCourse(Course &course);
    static bool RemoveCourse(string &course_id);
	static bool RemoveStudentFromCourse(const string &course_id, const int student_id);
    static bool AddStudentToCourse(const string &course_id, const int student_id);
    static Course GetCourseInfo(string &course_id);
    static vector<string> SearchCourse(string &course_id);
    static vector<string> GetCourseList();
    static bool ExportScoreboard(string &course_id);
    static bool ExportAttendance(string &course_id);
};

#endif