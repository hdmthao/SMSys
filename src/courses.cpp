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


bool Courses::ImportCourse(const string &csv_name) {

    // Load Course info
    ifstream fi(Path::IMPORT_COURSE + csv_name);
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

    const string COURSE_ID = new_course.ID;
    const string path_to_course_dir = Path::COURSE + COURSE_ID;
    const string path_to_course = path_to_course_dir + "/course_info.txt";

    // if course not exist so make a new database for this course and save to database
    if (!ExistedCourse(COURSE_ID)) {
        Helper::MakeDir(path_to_course_dir);
        AddNewCourseToDatabase(COURSE_ID);
    } else {
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

    // Save student info And init scoreboard && attendance
    class_name = Helper::StringToUpper(class_name);
    fi.open(Path::CLASS + class_name + "/student.txt");
    if (fi.is_open()) {
        fo.open(path_to_course_dir + "/student_info.txt");
        ofstream fo_score(path_to_course_dir + "/scoreboard.txt");
        ofstream fo_attendance(path_to_course_dir + "/attendance.txt");
        string id, first_name, last_name, line;
        while (!fi.eof()) {
            getline(fi, id, ' ');
            if (id == "") break;
            getline(fi, first_name, ' ');
            getline(fi, last_name, ' ');
            getline(fi, line);
            fo << id << " " << first_name << " "<< last_name << " " << line << "\n";
            fo_score << id << " " << first_name << " " << last_name << " " << "0 0 0 0 NULL 0\n";
            fo_attendance << id << " " << first_name << " " << last_name << " " << "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n";
        }
        fo.close();
        fo_score.close();
        fo_attendance.close();
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


bool Courses::AddStudentToCourse(const string & course_id, const int student_id) {
    // Check student existed in class
    if (!IsExistedStudent(student_id)) {
        return false;
    }

    const string COURSE_ID = Helper::StringToUpper(course_id);
	Student NewStudent = GetStudent(student_id);
	string SBoardPath = Path::COURSE + COURSE_ID + "/scoreboard.txt";
	string SInfoPath = Path::COURSE + COURSE_ID + "/student_info.txt";
	
    // Check studnet existed in course
    ifstream fi(SInfoPath);
    Student tmp_student;
    while (fi >> tmp_student.ID >> tmp_student.first_name >> tmp_student.last_name >> tmp_student.gender >> 
            tmp_student.dob >> tmp_student.email) {
                if (tmp_student.ID == student_id) {
                    fi.close();
                    return false;
                }
            }
    fi.close();
	ofstream fout;
    // Add to Score Board, scoreboard.txt
	fout.open(SBoardPath, ios::app);
	fout << NewStudent.ID << " " << NewStudent.first_name << " " << NewStudent.last_name << " 0 0 0 0 NULL 0\n";
	fout.close();
    // Add to Attendance, attendace.txt
    fout.open(Path::COURSE + COURSE_ID + "/attendance.txt", ios::app);
    fout << NewStudent.ID << " " << NewStudent.first_name << " " << NewStudent.last_name << " 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n";
    fout.close(); 
    // Add to Student List, student_info.txt
	fout.open(SInfoPath, ios::app);
	fout << NewStudent.ID << " " << NewStudent.first_name << " " << NewStudent.last_name << " " << NewStudent.gender << " " << NewStudent.dob << " " << NewStudent.email << "\n";
	fout.close();
	return true;
}

bool Courses::EditCourse(Course &course) {
    Helper::UpperFirstCharOfLetter(course.name);
    Helper::ConvertStringToDash(course.name);
    Helper::FormatDay(course.start_date);
    Helper::FormatDay(course.end_date);

    string path_to_course = Path::COURSE + course.ID + "/course_info.txt";
    cout << path_to_course << "\n";
    ofstream fo(path_to_course);

    fo << course.ID << " " << course.name << " " << course.lecturer << " " << course.start_date << " " << course.end_date;
    
    fo.close();
    return true;
}


bool Courses::RemoveStudentFromCourse(const string & course_id, const int del_student){
    const string COURSE_ID  = Helper::StringToUpper(course_id);
	string SBoardPath = Path::COURSE + COURSE_ID + "/scoreboard.txt";
	string SInfoPath = Path::COURSE + COURSE_ID + "/student_info.txt";

	ifstream fin;
	ofstream fout;

    // Check existed studnent in course && Get student list student_info.txt
	vector <Student> StudentList;
	Student TmpStudent;
    bool existed_del_student = false;

	fin.open(SInfoPath);
	while (fin >> TmpStudent.ID >> TmpStudent.first_name >> TmpStudent.last_name >> TmpStudent.gender >> TmpStudent.dob >> TmpStudent.email) {
		if (TmpStudent.ID != del_student) {
			StudentList.push_back(TmpStudent);
        } else {
            existed_del_student = true;
        }
	}
	fin.close();

    if (!existed_del_student) {
        StudentList.clear();
        return false;
    }

    // Rewrite student list to student_info.txt
	fout.open(SInfoPath);
	for (int i = 0; i < StudentList.size(); i++) {
		fout << StudentList[i].ID << " " << StudentList[i].first_name << " " << StudentList[i].last_name << " " << StudentList[i].gender << " " << StudentList[i].dob << " " << StudentList[i].email << "\n";
	}
	fout.close();
	StudentList.clear();

    // Get from Score Board, scoreboard.txt;
	vector <Score> ScoreList;
	Score TmpScore;

	fin.open(SBoardPath);
	while (fin >> TmpScore.ID >> TmpScore.first_name >> TmpScore.last_name >> TmpScore.mid_term >> TmpScore.lab >>
        TmpScore.bonus >> TmpScore.final_term >> TmpScore.ABCF >> TmpScore.GPA) {
		if (TmpScore.ID != del_student) {
			ScoreList.push_back(TmpScore);
		}
	}
	fin.close();

    // Rewrite Score Board, scoreboard.txt
	fout.open(SBoardPath);
	for (int i = 0; i < ScoreList.size(); i++) {
		fout << ScoreList[i].ID << " " << ScoreList[i].first_name << " " << ScoreList[i].last_name << " " << ScoreList[i].mid_term << " " <<
        ScoreList[i].lab << " " << ScoreList[i].bonus << " " << ScoreList[i].final_term << " " << ScoreList[i].ABCF << " " << ScoreList[i].GPA << "\n";
	}
	fout.close();
	ScoreList.clear();

    // Get from attendance, attendance.txt
    vector<string> AttenList;
    fin.open(Path::COURSE + COURSE_ID + "/attendance.txt");
    string line;
    while (getline(fin, line)) {
        if (line == "") break;
        int id = 0;
        for (int i = 0; i < line.length(); ++i) {
            if (line[i] == ' ') break;
            id = id * 10 + line[i] - '0';
        }
        if (id != del_student) {
            AttenList.push_back(line);
        }
    }
    fin.close();
    
    fout.open(Path::COURSE + COURSE_ID + "/attendance.txt");
    for (int i = 0; i < AttenList.size(); ++i) {
        fout << AttenList[i] << "\n";
    }
    fout.close();
    AttenList.clear();
    return true;
}


bool Courses::RemoveCourse(string &course_id) {
    course_id = Helper::StringToUpper(course_id);

    if (!ExistedCourse(course_id)) {
        return false;
    }

    vector<string> course_list = GetCourselist();

    ofstream fo(Path::COURSES_LIST);
    for (int i = 0; i < course_list.size(); ++i) {
        if (course_list[i] != course_id) {
            fo << course_list[i] << "\n";
        }
    }
    fo.close();
    course_list.clear();

    Helper::RemoveDir(course_id);

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


Course Courses::GetCourseInfo(string &course_id) {
    Course course;

    ifstream fi(Path::COURSE + course_id + "/course_info.txt");
    fi >> course.ID >> course.name >> course.lecturer >> course.start_date >> course.end_date;
    fi.close();
    Helper::ConvertStringToSpace(course.name);
    return course;
}


vector<string> Courses::SearchCourse(string &find_id) {
    find_id = Helper::StringToUpper(find_id);

    vector<string> course_list;
    ifstream fi(Path::COURSES_LIST);

    if (!fi.is_open()) {
        return course_list;
    }

    string course_id;

    while (fi >> course_id) {
        if (course_id.find(find_id) != string::npos) {
            course_list.push_back(course_id);
        }
    }
    fi.close();

    return course_list;
}


bool Courses::ExportScoreboard(string &course_id) {
    course_id = Helper::StringToUpper(course_id);

    ifstream fi(Path::COURSE + course_id + "/scoreboard.txt");
    if (!fi.is_open()) {
        return false;
    }

    ofstream fo(Path::EXPORT + course_id + "_scoreboard.csv");

    string id, first_name, last_name, midterm, lab, bonus, Final, ABCF, GPA;
    // Write Header
    
    fo << "No,Student ID,Last Name,First Name,Midterm,Lab,Bonus,Final,ABCF,GPA\n";
    int count = 1;
    while (fi >> id) {
        fi >> first_name >> last_name >> midterm >> lab >> bonus >> Final >> ABCF >> GPA;
        Helper::ConvertStringToSpace(last_name);
        fo <<count << "," << id << "," << last_name << "," << first_name << "," << midterm <<
            "," << lab << "," << bonus << "," << Final << "," << ABCF << "," << GPA << "\n";
        count++;
    }
    fi.close();
    fo.close();
    return true;
}


bool Courses::ExportAttendance(string &course_id) {
    course_id = Helper::StringToUpper(course_id);

    ifstream fi(Path::COURSE + course_id + "/attendance.txt");
    if (!fi.is_open()) {
        return false;
    }

    ofstream fo(Path::EXPORT + course_id + "_attendance.csv");

    string id, first_name, last_name;
    // Write Header
    
    fo << "No,Student ID,Last Name,First Name";
    for (int i = 1; i <= 10; ++i) {
        fo << ",Week_" << i;
    }
    fo << "\n";
    int count = 1;
    while (fi >> id) {
        fi >> first_name >> last_name;
        Helper::ConvertStringToSpace(last_name);
        fo <<count << "," << id << "," << last_name;
        string x;
        int cnt = 0;
        for (int i = 1; i <= 10; ++i) {
            fi >> x;
            if (x == "1") cnt++;
            fi >> x;
            if (x == "1") cnt++;
            fo << "," << cnt << "/2";
            cnt = 0;
        }
        count++;
        fo << "\n";
    }
    fi.close();
    fo.close();
    return true;
}

