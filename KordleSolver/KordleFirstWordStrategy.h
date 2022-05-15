#pragma once
#include "KordleStrategy.h"

class KordleFirstWordStrategy : public KordleStrategy
{
	virtual wstring calculateNextWord(vector<wstring> validWords, vector<wstring> queryableWords, int countQueried);
	virtual Cloneable* clone() override;
};