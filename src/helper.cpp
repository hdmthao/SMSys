#include "helper.h"
#include "reader.h"

bool Helper::isValidFileName(string fileName, string extName) {
	// kiem tra xem duoi file co hop le khong
	// return true neu extName trung voi duoi cua fileName
	//
	int len = fileName.length(), pos = -1;
	for (int i = 0; i < len; ++i) {
		if (fileName[i] == '.') {
			pos = i + 1;
			break;
		}
	}
	if (pos == -1) {
		return false;
	} else {
		string tempExtName = "";
		for (;pos < len; ++pos) {
			tempExtName = tempExtName + fileName[pos];
		}
		return extName == tempExtName;
	}
}

string Helper::getCurrentWorkingDir() {
	// tra ve duong dan dang lam viec
	//
	char buff[255];
	GetCurrentDir(buff, 255);
	string current_working_dir(buff);
	return current_working_dir;
}

vector<vector<string> > Helper::getDataFromFile(string fileName) {
	// lay data tu file va tra ve duoi dang vector 2 chieu
	//
	Reader *reader = new Reader(fileName);
	vector<vector<string> > dataList = reader->getData();

	SAFE_DELETE(reader);
	return dataList;
}

void Helper::writeDataToFile(ofstream &fo, vector<string> data) {
	// viet data vo file
	//
	for (int i = 0; i < data.size(); ++i) {
		fo << data[i];
		if (i < data.size() - 1) fo << ",";
	}
	fo << "\n";
}


