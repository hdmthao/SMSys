#include "searcher.h"
#include "helper.h"
#include "reader.h"

#include <fstream>
#include <vector>
#include <iostream>

using std::vector;
using std::ifstream;

Searcher::Searcher(string fileName) :
	fileName(fileName)
{
	pNode = new TrieNode();
	Searcher::load();
}

Searcher::~Searcher() {
	SAFE_DELETE(pNode);
}

void Searcher::load() {
	Reader *reader = new Reader(fileName);
	vector<vector<string> > dataList = reader->getData();

	for (int i = 0; i < dataList.size(); ++i) {
		string id = dataList[i][0];
		string className = dataList[i][1];
		insert(id, className);
	}

	SAFE_DELETE(reader);
}

void Searcher::insert(string key, string className) {
	TrieNode *pCur = pNode;

	for (int i = 0; i < key.size(); ++i) {
		int index = key[i] - '0';
		if (pCur->children[index] == nullptr) {
			pCur->children[index] = new TrieNode();
		}
		pCur = pCur->children[index];
	}
	pCur->className = className;
	pCur->isEndOfWord = true;
}

bool Searcher::search(string key) {
	TrieNode * pCur = pNode;
	for (int i = 0; i < key.size(); ++i) {
		int index = key[i] - '0';
		if (!pCur->children[index]) {
			return false;
		}
		pCur = pCur->children[index];	
	}
	
	return (pCur != nullptr && pCur->isEndOfWord == true);
}

string Searcher::searchClass(string key) {
	TrieNode* pCur = pNode;
	for (int i = 0; i < key.size(); ++i) {
		int index = key[i] - '0';
		if (!pCur->children[index]) {
			return "";
		}
		pCur = pCur->children[index];
	}
	return pCur->className;
}
