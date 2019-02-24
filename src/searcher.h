#ifndef SEARCHER_H
#define SEARCHER_H

#include <string>
#include <iostream>

#define ALPHABET_SIZE 10
using std::string;
using std::cout;

class TrieNode {
public:
	TrieNode * children[ALPHABET_SIZE];
	bool isEndOfWord;
	string className;
	TrieNode() {
		isEndOfWord = false;
		className = "";
		for (int i = 0; i < ALPHABET_SIZE; ++i) {
			children[i] = nullptr;
		}
	}
};

class Searcher {
private:
	string fileName;
	TrieNode *pNode;

public:
	Searcher(string fileName);
	~Searcher();
	void insert(string key, string className);
	bool search(string key);
	string searchClass(string key);
	virtual void load();
};
#endif

