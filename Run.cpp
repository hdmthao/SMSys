#include "app.h"

#include <iostream>

int main() {
	App app;
	Student student_test;
	student_test.ID = 18125123;
	student_test.last_name = "a-b";
	student_test.first_name = "b";
	student_test.gender = "male";
	student_test.dob = "01/01/2000";
	student_test.email = "abb18@apcs.vn";
	//cout << app.EditStudent("18CTT1", student_test);
	//cout << app.RemoveStudent("18CTT1", 18125123);
	cin.get();
}