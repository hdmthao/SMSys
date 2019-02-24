#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>
#include <string>

using std::cerr;
using std::cout;
using std::string;

namespace Debug {

	void logs(string msg) {
		cout << msg << "\n";
	}

}
#endif

