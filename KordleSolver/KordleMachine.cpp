#include "KordleMachine.h"

#include <unordered_map>

KordleResult KordleMachine::queryKordle(wstring queryString)
{
	count++;
	return queryKordle(answer, queryString);
}

KordleResult KordleMachine::queryKordle(wstring answer, wstring queryString)
{
	array<KordleColor, KordleMachine::KORDLE_LENGTH> result;

	unordered_map<wchar_t, int> count;

	for (int i = 0; i < KordleMachine::KORDLE_LENGTH; i++)
	{
		result[i] = KordleColor::BLACK;
	}

	for (int i = 0; i < KordleMachine::KORDLE_LENGTH; i++)
	{
		if (answer[i] == queryString[i])
		{
			result[i] = KordleColor::GREEN;
		}
		else
		{
			if (count.find(answer[i]) != count.end())
			{
				count[answer[i]]++;
			}
			else
			{
				count.insert({answer[i], 1});
			}
		}
	}

	for (int i = 0; i < KordleMachine::KORDLE_LENGTH; i++)
	{
		if (result[i] == KordleColor::GREEN)
		{
			continue;
		}

		if (count.find(queryString[i]) == count.end())
			continue;

		if (count[queryString[i]] > 0)
		{
			result[i] = KordleColor::YELLOW;
			count[queryString[i]]--;
		}
	}

	return KordleResult(result, queryString);
}

int KordleMachine::getCount()
{
	return count;
}
