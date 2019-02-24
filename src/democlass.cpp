#include <string>
#include <iostream>
#include <unistd.h>
#include <vector>
#include "class.h"
#include "helper.h"

using std::cout;
using std::vector;


int main() {
	system("clear");
	string fileName = "18CTT1-Students.csv";
	string className ="18CTT1";

	Class *classRoom = new Class();

	vector<string> importLogs = classRoom->importStudent(fileName, className);
	
	for (int i = 0; i < importLogs.size(); ++i) {
		cout << importLogs[i] << "\n";
	}

	SAFE_DELETE(classRoom);
	return 0;
}
