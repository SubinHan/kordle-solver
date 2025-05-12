#pragma once
#include <string>
#include <vector>

using namespace std;

class WordBank {
private:
	static WordBank* instance;
	vector<wstring>* validWords;
	vector<wstring>* queryableWords;

public:
	static WordBank* getInstance();
	vector<wstring> getValidWords();
	vector<wstring> getQueryableWords();

private:
	WordBank();
};