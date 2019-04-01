#include "path.h"

/* Path For Account */

const string Path::ACCOUNT = "data/account/account.txt";    // Path to save account data

/* Path For Class */

// Path to list of all existed class
const string Path::CLASS_LIST = "data/class/classes_list.txt"; 

// Default path class data
const string Path::CLASS = "data/class/";

// Path to folder save all csv file to import class
const string Path::IMPORT_STUDENT = "data/import/class/";

// Path to list of all existed student
const string Path::ALL_STUDENT = "data/student/students_list.txt";

/* Path For Course */

// Default ACADEMIC_YEAR/SEMESTER are current year/semseter
string Path::ACADEMIC_YEAR = "2018-2019";
string Path::SEMESTER = "fall";

// Default path course data is for current year/semeser
string Path::COURSE = "data/course/" + Path::ACADEMIC_YEAR + "/" + Path::SEMESTER + "/";

// Path to list of all existed courses in current year/semester 
string Path::COURSES_LIST = Path::COURSE + "courses_list.txt";

// Path to folder save all csv file to import course
const string Path::IMPORT_COURSE = "data/import/course/";

// Path to folder save all export file
const string Path::EXPORT = "export/";

const string Path::LECTURER_LIST = "data/lecturer/lecturer_list.txt";
