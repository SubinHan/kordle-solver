#include "KordleFirstWordStrategy.h"

wstring KordleFirstWordStrategy::calculateNextWord(vector<wstring> validWords, vector<wstring> queryableWords)
{
	if (validWords.size() < 1)
		return wstring();
	return validWords.at(0);
}
