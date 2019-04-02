#ifndef STUDENTS_H
#define STUDNETS_H

#include "data_period.h"
#include "data_score.h"
#include "data_course.h"
#include "data_attendance.h"

#include <string>
#include <vector>

using std::string;
using std::vector;


class Students {
private:
    static bool MarkAttendance(int ID, string &course_id, int cur_week, int cur_count);
public:
    static string CheckIn(int ID);
    static vector<Schedule> GetSchedule(int ID);
    static vector<Score> ViewScore(int ID);
    static vector<Attendance> ViewCheckInResult(int ID);
    static vector<string> GetCourseList(int ID);

};
#endif