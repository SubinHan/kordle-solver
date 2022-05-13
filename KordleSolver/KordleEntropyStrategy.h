#pragma once
#include "KordleStrategy.h"

class KordleEntropyStrategy : public KordleStrategy
{
	virtual wstring calculateNextWord(vector<wstring> validWords, vector<wstring> queryableWords);
};