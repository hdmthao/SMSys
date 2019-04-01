#include "data_lecturer.h"
#include "path.h"
#include <fstream>
#include "helper.h"
using std::ifstream;
using std::string;

Lecturer::Lecturer() {

}

Lecturer::~Lecturer() {

}

vector<string> Lecturer::GetLecturerList(string ID)
{
	ifstream fin;
	fin.open(Path::LECTURER_LIST);
	Lecturer tmp;
	if (fin.is_open())
	{
		while (fin >> tmp.ID >> tmp.first_name >> tmp.last_name >> tmp.numOfCourse)
		{
			Helper::ConvertStringToSpace(tmp.last_name);
			for (int i = 0; i < tmp.numOfCourse; i++)
			{
				string a;
				fin >> a;
				tmp.courses.push_back(a);
			}
			if (tmp.ID == ID) {
				break;
			}
			else
			{
				tmp.courses.clear();
			}
		}
	}
	fin.close();
	return tmp.courses;
}