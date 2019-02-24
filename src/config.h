#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include "helper.h"

using std::string;

namespace Config {
	const string currentPath = Helper::getCurrentWorkingDir();
	const string importPath = currentPath + "/data/import/student/";
	const string dataPath = currentPath + "/data/";
	const string classPath = currentPath + "/data/class/";
	const string accountPath = currentPath + "/data/account/account.txt";
}
#endif

