#include "KordleMachine.h"

KordleResult KordleMachine::makeKordleResult(array<bool, KordleMachine::KORDLE_LENGTH> resultGreen, array<bool, KordleMachine::KORDLE_LENGTH> resultYellow, wstring queryString)
{
	array<KordleColor, KordleMachine::KORDLE_LENGTH> result;

	for (int i = 0; i < KordleMachine::KORDLE_LENGTH; i++)
	{
		if (resultGreen[i])
			result[i] = KordleColor::GREEN;
		else if (resultYellow[i])
			result[i] = KordleColor::YELLOW;
		else
			result[i] = KordleColor::BLACK;
	}

	return KordleResult(result, queryString);
}

KordleResult KordleMachine::queryKordle(wstring queryString)
{
	count++;
	return queryKordle(answer, queryString);
}

KordleResult KordleMachine::queryKordle(wstring answer, wstring queryString)
{
	bool visited[KordleMachine::KORDLE_LENGTH];
	array<KordleColor, KordleMachine::KORDLE_LENGTH> result;

	for (int i = 0; i < KordleMachine::KORDLE_LENGTH; i++)
	{
		result[i] = KordleColor::BLACK;
		visited[i] = false;
	}

	for (int i = 0; i < KordleMachine::KORDLE_LENGTH; i++)
	{
		if (answer[i] == queryString[i])
		{
			result[i] = KordleColor::GREEN;
			visited[i] = true;
		}
	}

	for (int i = 0; i < KordleMachine::KORDLE_LENGTH; i++)
	{
		if (visited[i])
			continue;
		for (int j = 0; j < KordleMachine::KORDLE_LENGTH; j++)
		{
			if (answer[i] == queryString[j] && result[j] == KordleColor::BLACK)
			{
				result[j] = KordleColor::YELLOW;
				visited[i] = true;
				break;
			}
		}
	}

	return KordleResult(result, queryString);
}

int KordleMachine::getCount()
{
	return count;
}
