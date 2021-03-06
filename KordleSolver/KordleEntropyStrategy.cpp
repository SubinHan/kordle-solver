#include "KordleEntropyStrategy.h"
#include "KordleMachine.h"
#include <cmath>

wstring KordleEntropyStrategy::calculateNextWord(vector<wstring> validWords, vector<wstring> queryableWords, int countQueried)
{
	if (validWords.empty())
		return wstring();

	if (countQueried == 0)
	{
		return FIRST_BEST;
	}

	if (validWords.size() < 30)
	{
		queryableWords = validWords;
	}

	double max = 0;
	int maxIndex = -1;
	for (vector<wstring>::iterator iter = queryableWords.begin(); iter != queryableWords.end(); iter++)
	{
		int score = 0;
		for (vector<wstring>::iterator iter2 = validWords.begin(); iter2 != validWords.end(); iter2++)
		{
			KordleResult result = KordleMachine::queryKordle(*iter, *iter2);
			for (KordleColor color : result.result)
			{
				if (color == KordleColor::YELLOW)
				{
					score++;
				}
				if (color == KordleColor::GREEN)
				{
					score += 5;
				}
			}
		}
		double average = score / validWords.size();
		if (average > max)
		{
			max = average;
			maxIndex = distance(queryableWords.begin(), iter);
		}
	}

	return queryableWords.at(maxIndex);
}

Cloneable* KordleEntropyStrategy::clone()
{
	return new KordleEntropyStrategy();
}