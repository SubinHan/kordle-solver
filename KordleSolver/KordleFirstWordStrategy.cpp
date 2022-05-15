#include "KordleFirstWordStrategy.h"

wstring KordleFirstWordStrategy::calculateNextWord(vector<wstring> validWords, vector<wstring> queryableWords, int countQueried)
{
	if (validWords.size() < 1)
		return wstring();
	return validWords.at(0);
}

Cloneable* KordleFirstWordStrategy::clone()
{
	return new KordleFirstWordStrategy();
}
