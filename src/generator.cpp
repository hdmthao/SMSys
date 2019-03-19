#include "generator.h"


string Generator::generatePassword(const string  &pass) {
	const long long cbase = 127;
	const long long cbase2 = 912;
	const long long cmod = 812948195347;
	long long cur_hash = 0;
	long long cur_hash2 = 0;
    string result = "";

	for (int i = 0; i < pass.length(); i++) {
		cur_hash = (cur_hash * cbase + pass[i] - '0' + 1) % cmod;
		cur_hash2 = (cur_hash2 * cbase2 + pass[i] - '0' + 1) % cmod;

	}
	while (cur_hash) {
		if (cur_hash % 16 < 10)
			result += (cur_hash % 16 + '0');
		else
			result += (cur_hash % 16 - 10 + 'A');
		cur_hash /= 16;
	}
	while (cur_hash2) {
		if (cur_hash2 % 16 < 10)
			result += (cur_hash2 % 16 + '0');
		else
			result += (cur_hash2 % 16 - 10 + 'A');
		cur_hash2 /= 16;
	}
	return result;
}


string Generator::generateEmail(const string &lastName, const string &firstName) {
	string result = "";
	string last_name = lastName;
	for (int i = 0; i < last_name.length(); ++i) {
		if (last_name[i] >= 'A' && last_name[i] <= 'Z') last_name[i] = last_name[i] - 'A' + 'a';
	}
	for (int i = 0; i < last_name.length(); i++){
		if (i == 0 || last_name[i - 1] == ' ') 
			result += lastName[i];
	}
	string first_name = firstName;
	for (int i = 0; i < first_name.length(); ++i) {
		if (first_name[i] >= 'A' && first_name[i] <= 'Z') first_name[i] = first_name[i] - 'A' + 'a';
	}
	first_name[0] = first_name[0] - 'a' + 'A';
	result += firstName + "18@apcs.vn";
	return result;
}