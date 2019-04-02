#ifndef DATA_PERIOD_H
#define DATA_PERIOD_H

#include <string>
#include <vector>


using std::string;
using std::vector;

struct Period {
    int dow;
    int shift;
    string room;
};

struct Schedule {
    int dow;
    int shift;
    string course_id;
    string room;
};


#endif