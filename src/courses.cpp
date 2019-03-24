#include "courses.h"
#include "helper.h"
#include "path.h"

#include <fstream>
#include <iostream>

using std::ifstream;
using std::ofstream;
using std::cout;
using std::ios;

Courses::Courses() {
}


Courses::~Courses() {
}


bool Courses::ImportCourse(const string &course_id, const string &csv_name) {
    const string COURSE_ID = Helper::StringToUpper(course_id);
    const string path_to_course_dir = Path::COURSE + COURSE_ID;
    const string path_to_csv_file = Path::IMPORT_COURSE + csv_name;
    const string path_to_course = path_to_course_dir + "/course_info.txt";

    // if course not exist so make a new database for this course and save to database
    if (!ExistedCourse(COURSE_ID)) {
        Helper::MakeDir(path_to_course_dir);
        AddNewCourseToDatabase(COURSE_ID);
    } else {
        return false;
    }

    // Load Course info
    ifstream fi(path_to_csv_file);
    if (!fi.is_open()) {
        return false;
    }
    
    Course new_course;
    string class_name;
    string number_period;
    Period period_1, period_2;
    string rash;
    // Get header of csv
    getline(fi, rash);
    // Get course info
    getline(fi, new_course.ID, ',');
    getline(fi, new_course.name, ',');
    getline(fi, class_name, ',');
    getline(fi, new_course.lecturer, ',');
    getline(fi, new_course.start_date, ',');
    getline(fi, new_course.end_date, ',');
    getline(fi, number_period, ',');
    
    string dow, shift, room;
    getline(fi, dow, ',');
    getline(fi, shift, ',');

    period_1.dow = std::stoi(dow);
    period_1.shift = std::stoi(shift);
    if (number_period == "1") {
        getline(fi, room);
        period_1.room = room;
    }
    if (number_period == "2") {\
        getline(fi, room, ',');
        period_1.room = room;
        getline(fi, dow, ',');
        getline(fi, shift, ',');
        getline(fi, room);
        period_2.dow = std::stoi(dow);
        period_2.shift = std::stoi(shift);
        period_2.room = room;
    }
    fi.close();

    new_course.ID = Helper::StringToUpper(new_course.ID);

    // check course id is same
    if (new_course.ID != COURSE_ID) {
        return false;
    }
    // Save Course info
    ofstream fo(path_to_course_dir + "/course_info.txt");
    Helper::UpperFirstCharOfLetter(new_course.name);
    Helper::ConvertStringToDash(new_course.name);
    Helper::FormatDay(new_course.start_date);
    Helper::FormatDay(new_course.end_date);
    fo << new_course.ID << " " << new_course.name << " " <<  new_course.lecturer << " " <<
        new_course.start_date << " " << new_course.end_date;
    fo.close();

    // Save schedule
    fo.open(path_to_course_dir + "/schedule.txt");
    fo << number_period << "\n";
    fo << period_1.dow << " " << period_1.shift << " " << period_1.room;
    if (number_period == "2") {
        fo << "\n";
        fo << period_2.dow << " " << period_2.shift << " " << period_2.room;
    }
    fo.close();

    // Save student info And init scoreboard
    class_name = Helper::StringToUpper(class_name);
    fi.open(Path::CLASS + class_name + "/student.txt");
    if (fi.is_open()) {
        fo.open(path_to_course_dir + "/student_info.txt");
        ofstream fo_score(path_to_course_dir + "/scoreboard.txt");
        string id, first_name, last_name, line;
        while (!fi.eof()) {
            getline(fi, id, ' ');
            if (id == "") break;
            getline(fi, first_name, ' ');
            getline(fi, last_name, ' ');
            getline(fi, line);
            fo << id << " " << first_name << " "<< last_name << " " << line << "\n";
            fo_score << id << " " << first_name << " " << last_name << " " << "0 0 0 0 NULL 0\n"; 
        }
        fo.close();
        fo_score.close();
    }
    fi.close();

    return true;
}


bool Courses::AddNewCourse(Course &new_course, string &class_name, int number_period, Period &period_1, Period &period_2) {
    new_course.ID = Helper::StringToUpper(new_course.ID);
    class_name = Helper::StringToUpper(class_name);
    Helper::FormatDay(new_course.start_date);
    Helper::FormatDay(new_course.end_date);
    period_1.room = Helper::StringToUpper(period_1.room);
    period_2.room = Helper::StringToUpper(period_2.room);
    Helper::ConvertStringToDash(new_course.name);

    const string path_to_course_dir = Path::COURSE + new_course.ID;

    if (!ExistedCourse(new_course.ID)) {
        AddNewCourseToDatabase(new_course.ID);
        Helper::MakeDir(path_to_course_dir);
    } else {
        return false;
    }

    // Save info course
    ofstream fo(path_to_course_dir + "/course_info.txt");  
    fo << new_course.ID << " " << new_course.name << " " << new_course.lecturer <<
    " " << new_course.start_date << " " << new_course.end_date;
    fo.close();
    
    // Save Schedule
    fo.open(path_to_course_dir + "/schedule.txt");
    fo << number_period << "\n";
    fo << period_1.dow << " " << period_1.shift << " " << period_1.room;
    if (number_period == 2) {
        fo << "\n";
        fo << period_2.dow << " " << period_2.shift << " " << period_2.room;
    }

    // Save info student && init scoreboard
    ifstream fi(Path::CLASS + class_name + "/student.txt");
    if (fi.is_open()) {
        fo.open(path_to_course_dir + "/student_info.txt");
        ofstream fo_score(path_to_course_dir + "/scoreboard.txt");
        string id, first_name, last_name, line;
        while (!fi.eof()) {
            getline(fi, id, ' ');
            if (id == "") break;
            getline(fi, first_name, ' ');
            getline(fi, last_name, ' ');
            getline(fi, line);
            fo << id << " " << first_name << " "<< last_name << " " << line << "\n";
            fo_score << id << " " << first_name << " " << last_name << " " << "0 0 0 0 NULL 0\n"; 
        }
        fo.close();
        fo_score.close();
    }
    fi.close();
    return true;
}

bool Courses::ExistedCourse(const string &course_id) {
    ifstream fi(Path::COURSES_LIST);
    if (!fi.is_open()) {
        return false;
    }
    string tmp_id;
    while (fi >> tmp_id) {
        if (tmp_id == course_id) {
            fi.close();
            return true;
        }
    }
    fi.close();
    return false;
}


void Courses::AddNewCourseToDatabase(const string &course_id) {
    ofstream fo(Path::COURSES_LIST, ios::app);

    fo << course_id << "\n";

    fo.close();
}