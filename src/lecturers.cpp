#include "lecturers.h"
#include "helper.h"
#include "path.h"
#include "generator.h"
#include "data_account.h"

#include <fstream>

using std::ifstream;
using std::ofstream;
using std::ios;

vector<string> Lecturers::GetCoursesList(string &name) {
    vector<string> list;

    ifstream fi(Path::LECTURER);
    int count;
    string tmp_name, tmp_course;
    while (fi >> tmp_name) {
        fi >> count;
        for (int i = 0; i < count; ++i) {
            fi >> tmp_course;
            if (tmp_name == name) list.push_back(tmp_course);
        }
    }
    fi.close();
    return list;
}


bool Lecturers::EditAttendance(int ID, string &course_id, int week, int count) {
    if (week > 10 || count > 2) return false;

    ifstream fi(Path::COURSE + course_id + "/attendance.txt");

    vector<string> list;
    int tmp_id;
    string tmp_first_name, tmp_last_name, tmp_data;
    while (fi >> tmp_id) {
        fi >> tmp_first_name >> tmp_last_name;
        tmp_data = "";
        if (tmp_id != ID) {
            getline(fi, tmp_data);
            tmp_data = " " + tmp_data;
        } else {
            int x1, x2;
            for (int i = 1; i <= 10; ++i) {
                fi >> x1 >> x2;
                if (week == i){
                    if (count == 1) x1 = 1 - x1; else x2 = 1 - x2;
                }
                tmp_data += " " + std::to_string(x1) + " " + std::to_string(x2);
            }
        }
        string line = std::to_string(tmp_id) + " " + tmp_first_name + " " + tmp_last_name + tmp_data;
        list.push_back(line);
    }
    fi.close();
    ofstream fo(Path::COURSE + course_id + "/attendance.txt");

    for (int i = 0; i < list.size(); ++i) {
        fo << list[i] << "\n";
    }
    fo.close();
}

bool Lecturers::EditGrade(string &course_id, Score &a) {
	vector<Score> ScoreBoard;
	Helper::StringToUpper(course_id);
	string path = Path::COURSE + course_id + "/scoreboard.txt";
	ifstream fin(path);
	if (fin.is_open()) {
		while (!fin.eof()) {
			string data_line;
			getline(fin, data_line);
			Score score;
			score = Helper::stringToScore(data_line);
			if (score.ID == 0) break;
			if (score.ID == a.ID) {
				score.mid_term = a.mid_term;
				score.final_term = a.final_term;
				score.lab = a.lab;
				score.bonus = a.bonus;
				score.GPA = (score.mid_term * 0.3 + score.bonus * 0.1 + score.lab * 0.2 + score.final_term * 0.4);
				score.ABCF = 'A' + (score.GPA < 8.5) + (score.GPA < 7.0) + (score.GPA < 5.5) + (score.GPA < 4.0);				
			}
			ScoreBoard.push_back(score);
		}
	}
	fin.close();

	// Rewrite data
	ofstream out;
	out.open(path);

	for (int i = 0; i < ScoreBoard.size(); i++) {
		Helper::ConvertStringToDash(ScoreBoard[i].last_name);
		
		out << ScoreBoard[i].ID << " " << ScoreBoard[i].first_name << " " << ScoreBoard[i].last_name << " " << ScoreBoard[i].mid_term
			<< " " << ScoreBoard[i].lab << " " << ScoreBoard[i].bonus << " " << ScoreBoard[i].final_term << " " <<
			Helper::StringToUpper(ScoreBoard[i].ABCF) << " " << ScoreBoard[i].GPA << "\n";
	}
	ScoreBoard.clear();
	out.close();
	return true;

    			// 	ScoB[i].GPA = (ScoB[i].mid_term * 0.3 + ScoB[i].bonus * 0.1 + ScoB[i].lab * 0.2 + ScoB[i].final_term * 0.4);
				// ScoB[i].ABCF = 'A' + (ScoB[i].GPA < 8.5) + (ScoB[i].GPA < 7.0) + (ScoB[i].GPA < 5.5) + (ScoB[i].GPA < 4.0);				

}

void Lecturers::AddNewCourse(string &lecturer_name, string &course_id) {
    bool is_exist = false;

    ifstream fi(Path::LECTURER);

    int tmp_count;
    string tmp_name, tmp_course;
    while (fi >> tmp_name) {
        fi >> tmp_count;
        for (int i = 0; i < tmp_count; ++i) {
            fi >> tmp_course;
        }
        if (tmp_name == lecturer_name) {
            is_exist = true;
            break;
        }
    }
    fi.close();

    if (is_exist) {
        vector<string> list;
        fi.open(Path::LECTURER);
        while (fi >> tmp_name) {
            fi >> tmp_count;
            int tmp_tmp_count = tmp_count;
            if (lecturer_name == tmp_name) tmp_count++;
            string line = tmp_name + " " + std::to_string(tmp_count);
            for (int i = 0; i < tmp_tmp_count; ++i) {
                fi >> tmp_course;
                line += " " + tmp_course;
            }
            if (lecturer_name == tmp_name) {
                line += " " + course_id;
            }
            list.push_back(line);
        }
        ofstream fo(Path::LECTURER);

        for (int i = 0; i < list.size(); ++i) {
            fo << list[i] << "\n";
        }
        fo.close();
        list.clear();
    } else {
        ofstream fo(Path::LECTURER, ios::app);
        fo << lecturer_name << " " << 1 << " " << course_id << "\n";
        fo.close();
    }
}

void Lecturers::RemoveCourse(string &course_id) {
    vector<string> list;
    
    ifstream fi(Path::LECTURER);
    int tmp_count;
    string tmp_name, tmp_course;
    while (fi >> tmp_name) {
        fi >> tmp_count;
        int tmp_tmp_count = tmp_count;
        string line = "";
        for (int i = 0; i < tmp_tmp_count; ++i) {
            fi >> tmp_course;
            if (tmp_course != course_id) line += " " + tmp_course; else tmp_count--;
        }
        list.push_back(tmp_name + " " + std::to_string(tmp_count) + line);
    }
    
    ofstream fo(Path::LECTURER);

    for (int i = 0; i < list.size(); ++i) {
        fo << list[i] << "\n";
    }
    fo.close();
    list.clear();
}

void Lecturers::CreateAccountForLecturer(string &user_name, string &password){
    
    ifstream fi(Path::ACCOUNT);
    int no, role, tmp;
    string tmp_name, tmp_password;
    while (fi >> no) {
        fi >> tmp_name >> tmp_password >> role >> tmp;
        if (tmp_name == user_name) {
            fi.close();
            return;
        };
    }
    fi.close();
    ofstream fo(Path::ACCOUNT, ios::app);
	fo << 11111111 << " " << user_name << " " << Generator::generatePassword(password) <<
                 " " << UserRole::LECTURER << " " << 1 << "\n"; // firsttime is true
    fo.close();
}

bool Lecturers::ImportScoreboard(string &course_id, string &csv_file){
	string csv_path = Path::IMPORT_SCORE + csv_file; // change here
	string txt_path = Path::COURSE + course_id + "/scoreboard.txt"; // change here

	// get from .txt

	vector <Score> ScoB;
	Score tmp;
	ifstream in;
	in.open(txt_path);
	while (in >> tmp.ID >> tmp.first_name >> tmp.last_name >> tmp.mid_term >> tmp.lab >> tmp.bonus >> tmp.final_term >> tmp.ABCF >> tmp.GPA) {
		ScoB.push_back(tmp);
	}
	in.close();
	
	// get from .csv
	
	string data;
	in.open(csv_path);
	in >> data; // first line - not using
 
	while (in >> data) { 
		Score convert_data;
		int space_count = 0;
		bool after_point = 0;
		//convert
		for (int i = 0; i < data.length(); i++) {
			if (data[i] == ',') {
				after_point = 0;
				++space_count;
				continue;
			}
			if (space_count == 0) {
				convert_data.ID = convert_data.ID * 10 + (data[i] - '0');
			}
			if (space_count == 1) {
				if (data[i] == '.')
					after_point = 1;
				else
					if (!after_point)
						convert_data.mid_term = convert_data.mid_term * 10 + (data[i] - '0');
					else
						convert_data.mid_term = convert_data.mid_term + 0.1 * (data[i] - '0');
			}
			if (space_count == 2) {
				if (data[i] == '.')
					after_point = 1;
				else
					if (!after_point)
						convert_data.lab = convert_data.lab * 10 + (data[i] - '0');
					else
						convert_data.lab = convert_data.lab + 0.1 * (data[i] - '0');
			}
			if (space_count == 3) {
				if (data[i] == '.')
					after_point = 1;
				else
					if (!after_point)
						convert_data.bonus = convert_data.bonus * 10 + (data[i] - '0');
					else
						convert_data.bonus = convert_data.bonus + 0.1 * (data[i] - '0');
			}
			if (space_count == 4) {
				if (data[i] == '.')
					after_point = 1;
				else
					if (!after_point)
						convert_data.final_term = convert_data.final_term * 10 + (data[i] - '0');
					else
						convert_data.final_term = convert_data.final_term + 0.1 * (data[i] - '0');
			}

		}
		//cout << convert_data.ID << " " << convert_data.mid_term << " " << convert_data.lab << " " << convert_data.bonus << " " << convert_data.final_term << "\n";
		for (int i = 0; i < ScoB.size(); i++) {
			if (ScoB[i].ID == convert_data.ID) {
				ScoB[i].mid_term = convert_data.mid_term;
				ScoB[i].lab = convert_data.lab;
				ScoB[i].bonus = convert_data.bonus;
				ScoB[i].final_term = convert_data.final_term;
				ScoB[i].GPA = (ScoB[i].mid_term * 0.3 + ScoB[i].bonus * 0.1 + ScoB[i].lab * 0.2 + ScoB[i].final_term * 0.4);
				ScoB[i].ABCF = 'A' + (ScoB[i].GPA < 8.5) + (ScoB[i].GPA < 7.0) + (ScoB[i].GPA < 5.5) + (ScoB[i].GPA < 4.0);				
			}
		}
	}
	in.close();

	// rewrite to .txt

	ofstream out;
	out.open(txt_path);
	for (int i = 0; i < ScoB.size(); i++) {
		out << ScoB[i].ID << " " << ScoB[i].first_name << " " << ScoB[i].last_name << " " << ScoB[i].mid_term << " " << ScoB[i].lab << " " << ScoB[i].bonus << " " << ScoB[i].final_term << " " << ScoB[i].ABCF << " " << ScoB[i].GPA << "\n";
	}
	out.close();

	return true;
}


vector<string> Lecturers::GetCsvForScore() {
    vector<string> list;

    string path = Path::IMPORT_SCORE;
    Helper::GetFileInFolder(list, path);

    return list;
}