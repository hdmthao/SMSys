#include "students.h"
#include "helper.h"
#include "path.h"

#include <iostream>
#include <fstream>


using std::ifstream;
using std::ofstream;

string Students::CheckIn(int ID) {
    string check_in_status = "";

    string cur_time = Helper::GetCurrentTime();

    int cur_dow = Helper::GetCurrentDoW(cur_time);
    int cur_shift = Helper::GetCurrentShift(cur_time);
    string cur_course = "";
    int cur_count = 0;
    vector<string> list = GetCourseList(ID);
    ifstream fi;
    for (int i = 0; i < list.size(); ++i) {
        fi.open(Path::COURSE + list[i] + "/schedule.txt");
        int count, tmp_dow, tmp_shift;
        string tmp_room;
        fi >> count;
        for (int j = 0; j < count; ++j) {
            fi >> tmp_dow >> tmp_shift >> tmp_room;
            if (tmp_dow == cur_dow && tmp_shift == cur_shift) {
                cur_course = list[i];
                cur_count = j + 1;
                break;
            }
        }
        fi.close();
    }

    if (cur_course == "") {
        check_in_status = "No course running for checkin";
        return check_in_status;
    }
    Course course;

    fi.open(Path::COURSE + cur_course + "/course_info.txt");
    fi >> course.ID >> course.name >> course.lecturer >> course.start_date >> course.end_date;
    fi.close();

    int cur_week = Helper::GetCurrentWeek(cur_time, course.start_date);

    bool mark_status = MarkAttendance(ID, cur_course, cur_week, cur_count);
    if (mark_status) {
        check_in_status = "You Were Check-In Course " + cur_course + " FOR WEEK " + std::to_string(cur_week);
    } else {
        check_in_status = "You Already Check-In This Course For This Shift";
    }

    return check_in_status;
}

vector<Schedule> Students::GetSchedule(int ID) {    
    vector<Schedule> schedule;
    vector<string> course_list = GetCourseList(ID);
    ifstream fi;

    for (int i = 0; i < course_list.size(); ++i) {
        fi.open(Path::COURSE + course_list[i] + "/schedule.txt");
        int number_of_week, dow, shift;
        string room;
        Schedule period;
        fi >> number_of_week;
        for (int j = 0; j < number_of_week; ++j) {
            fi >> dow >> shift >> room;
            period.room = room;
            period.course_id = course_list[i];
            period.dow = dow;
            period.shift = shift;
            schedule.push_back(period);
        }
        fi.close();
    }

    return schedule;
}


vector<Score> Students::ViewScore(int ID) {
    vector<string> list = GetCourseList(ID);
    vector<Score> scoreboard;
    ifstream fi;

    for (int i = 0; i < list.size(); ++i) {
        Score score;
        score.course_id = list[i];
        fi.open(Path::COURSE + list[i] + "/scoreboard.txt");
        if (!fi.is_open()) {
            scoreboard.push_back(score);
            continue;
        }

        while (fi >> score.ID) {
            fi >> score.first_name >> score.last_name >> score.mid_term >> score.lab >> score.bonus >>
                score.final_term >> score.ABCF >> score.GPA;
            if (score.ID == ID) {
                scoreboard.push_back(score);
                break;
            }
        }
        fi.close();
    }

    return scoreboard;
}


vector<string> Students::GetCourseList(int ID) {
    vector<string> list;
    int tmp_ID, tmp_count;
    string tmp_course;
    
    ifstream fi(Path::STUDENTS_LIST);

    while (fi >> tmp_ID) {
        fi >> tmp_count;
        for (int i = 0; i < tmp_count; ++i) {
            fi >> tmp_course;
            if (ID == tmp_ID) {
                list.push_back(tmp_course);
            }
        }
    }
    fi.close();

    return list;
}


vector<Attendance> Students::ViewCheckInResult(int ID) {
    vector<string> list = GetCourseList(ID);

    vector<Attendance> atten;
    ifstream fi;
    for (int i = 0; i < list.size(); ++i) {
        fi.open(Path::COURSE + list[i] + "/attendance.txt");
        while (!fi.eof()) {
            string data_line;
            getline(fi, data_line);
            Attendance attendance;
            attendance = Helper::stringToAttendance(data_line);
            if (attendance.ID == 0) break;
            if (attendance.ID == ID) {
                attendance.course_id = list[i];
                atten.push_back(attendance);
            }
        }
        fi.close();
    }

    return atten;
}


bool Students::MarkAttendance(int ID, string &course_id, int cur_week, int cur_count) {
    vector<string> list;

    // Lay danh sach diem danh va cap nhat
    ifstream fi(Path::COURSE + course_id + "/attendance.txt");
    Attendance atten;
    string tmp = "";
    bool mark_status = false;
    while (fi >> atten.ID) {
        fi >> atten.first_name >> atten.last_name;
        tmp = std::to_string(atten.ID) + " "  + atten.first_name + " " + atten.last_name;
        for (int i = 1; i <= 10; ++i) {
            int x1, x2;
            fi >> x1 >> x2;
            if (ID == atten.ID && cur_week == i) {
                if (cur_count == 1 && x1 == 0) {
                    std::cout << x1 << " ";
                    x1++;
                    mark_status = true;
                } else if (cur_count == 2 && x2 == 0) {
                    x2++;
                    mark_status = true;
                }
            }
            tmp += " " + std::to_string(x1) + " " + std::to_string(x2);
        }
        list.push_back(tmp);
    }
    fi.close();

    // Ghi lai danh sach diem danh
    ofstream fo(Path::COURSE + course_id + "/attendance.txt");
    for (int i = 0; i < list.size(); ++i) {
        fo << list[i];
        fo << "\n";
    }
    fo.close();
    return mark_status;

}
