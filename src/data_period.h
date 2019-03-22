#ifndef DATA_PERIOD_H
#define DATA_PERIOD_H

#include <string>

using std::string;

struct Period {
    int dow;
    int shift;
    string room;
};
#endif