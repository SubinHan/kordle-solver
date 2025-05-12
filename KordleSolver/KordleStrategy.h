#pragma once
#include <string>
#include <vector>

#include "Cloneable.h"

using namespace std;

class KordleStrategy : public Cloneable
{
public:
	virtual wstring calculateNextWord(vector<wstring> validWords, vector<wstring> queryableWords, int countQueried) abstract;
};