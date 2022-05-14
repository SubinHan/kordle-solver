#pragma once
#include <string>
#include <vector>

using namespace std;

class KordleStrategy
{
public:
	virtual wstring calculateNextWord(vector<wstring> validWords, vector<wstring> queryableWords, int countQueried) abstract;
};