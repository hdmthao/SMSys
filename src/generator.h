#ifndef GENERATOR_H
#define GENERATOR_H

#include <string>

using std::string;

class Generator{
public:
	static string generatePassword(const string  &pass);
	static string generateEmail(const string &lastName, const string &firstName);

};

#endif
