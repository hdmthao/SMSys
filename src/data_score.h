#ifndef SCORE_H
#define SCORE_H

#include <string>

using std::string;

struct Score {
	int ID;
	string first_name;
    string last_name;
	float mid_term;
    float lab;
    float bonus;
    float final_term;
    string ABCF;
    float GPA;
};

#endif
