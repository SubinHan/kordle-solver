#pragma once
#include "KordleStrategy.h"

class KordleEntropyStrategy : public KordleStrategy
{
private:
	const wstring FIRST_BEST = L"したいぁっび"s;

public:
	virtual wstring calculateNextWord(vector<wstring> validWords, vector<wstring> queryableWords, int countQueried);
	virtual Cloneable* clone() override;
};