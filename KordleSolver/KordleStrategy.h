#pragma once
#include "Cloneable.h"
#include <string>
#include <vector>

using namespace std;

class KordleStrategy : public Cloneable
{
public:
	virtual wstring calculateNextWord(vector<wstring> validWords, vector<wstring> queryableWords, int countQueried) abstract;
};