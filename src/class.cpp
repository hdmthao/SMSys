#include "class.h"
#include "config.h"
#include "helper.h"
#include "reader.h"
#include "searcher.h"
#include "debug.h"

vector<string> Class::importStudent(string fileName, string className) {
	// Kiem tra xem file import co phai file csv ko.
	vector<string> logsList;
	if ( Helper::isValidFileName(fileName, "csv") == false ) {
		logsList.push_back("Import fail. You must import a csv file.");
		return logsList;
	}

	// doc du lieu tu file csv vao vector dataList
	vector<vector<string> > dataList = Helper::getDataFromFile(Config::importPath + fileName);
	
	// mo file class.txt 
	ofstream classF(Config::classPath + className + ".txt", ofstream::app);

	// searcher de xem hoc sinh da tung import chua
	Searcher *searcher = new Searcher(Config::accountPath);

	// mo file account de them account neu import thanh cong 1 hoc sinh
	ofstream accountF(Config::accountPath, ofstream::app);

	int countStudent = 0, countExistStudent = 0, countImportedStudent = 0;

	for (int i = 1; i < dataList.size(); ++i) {
		countStudent++;
		string id = dataList[i][1];
		if (searcher->search(id)) { // hoc sinh da ton tai trong mot lop nao do.
			countExistStudent++;
			string classOfCurrentId = searcher->searchClass(id);
			if (classOfCurrentId == className) {
				logsList.push_back("[OK] Student whose id is " + id + ", is already in class."); 
			} else {
				logsList.push_back("[ X] Student Whose id is " + id + ", is already in another class.");
			}
		} else { // import thanh cong. luu hoc sinh vao class database
			countImportedStudent++;
			logsList.push_back("[OK] Student whose id is " + id + ", is successfully added.");
			Helper::writeDataToFile(classF, dataList[i]);
			
			// khoi tao mot account cho hoc sinh va luu account vao account database
			vector<string> accountData = setAccount(dataList[i][1], className, dataList[i][3], "password", false);
			Helper::writeDataToFile(accountF, accountData);
		}
	}
	logsList.push_back("Import done. " + to_string(countStudent) + " students were processed, " + to_string(countImportedStudent) + " added, " + to_string(countExistStudent) + " existed.");
	
	classF.close();
	accountF.close();
	
	SAFE_DELETE(searcher);
	return logsList;
}

vector<string> Class::setAccount(string id, string className, string name, string password, bool firstTimeLogin) {
	vector<string> account;
	account.push_back(id);
	account.push_back(className);
	account.push_back(name);
	account.push_back(password);
	account.push_back(to_string(firstTimeLogin));
	return account;
}
