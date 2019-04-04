#ifndef SCORE_H
#define SCORE_H

#include <string>

using std::string;

struct Score {
	int ID;
    string course_id;
	string first_name;
    string last_name;
	float mid_term;
    float lab;
    float bonus;
    float final_term;
    string ABCF;
    float GPA;

    Score() : ID(0), course_id(""), first_name(""), last_name(""), mid_term(0), lab(0), bonus(0), final_term(0), ABCF(""), GPA(0) { }

};

#endif
