#pragma once
#ifndef _APP_H
#define _APP_H

#include "data_student.h"

#include <fstream>
#include <string>
#include <vector>

using namespace std;

class App {

public:
	bool EditStudent(string class_name, const Student &student);
	bool RemoveStudent(string class_name, const int &ID);
};

#endif
