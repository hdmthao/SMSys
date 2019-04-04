#ifndef LECTURERS_H
#define LECTURERS_H

#include "data_score.h"

#include <string>
#include <vector>

using std::string;
using std::vector;

class Lecturers {
public:
    static bool EditGrade(string &coures_id, Score &score);
    static bool EditAttendance(int ID, string &course_id, int week, int count);
    static void AddNewCourse(string &lecturer_name, string &course_id);
    static void RemoveCourse(string &course_id);
    static vector<string> GetCoursesList(string &name);
    static void CreateAccountForLecturer(string &user_name, string &password);
    static bool ImportScoreboard(string &course_id, string &csv_file);
    static vector<string> GetCsvForScore();
};

#endif