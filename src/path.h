#ifndef PATH_H
#define PATH_H

#include <string>

using std::string;

class Path {
public:
    // Account
    static const string ACCOUNT;

    // Class
    static const string CLASS_LIST;
    static const string CLASS;
    static const string ALL_STUDENT;
    static const string IMPORT_STUDENT;

    // Course
    static string ACADEMIC_YEAR;
    static string SEMESTER;
    static string COURSE; 
    static string COURSES_LIST;
    static string STUDENTS_LIST;
    static const string IMPORT_COURSE;
    static const string EXPORT;
};

#endif