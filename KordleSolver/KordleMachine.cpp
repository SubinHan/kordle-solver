#include "KordleMachine.h"

array<bool, KordleMachine::KORDLE_LENGTH> checkGreens(wstring answer, wstring queryString, array<int, KordleMachine::KORDLE_LENGTH>& visited)
{
	array<bool, KordleMachine::KORDLE_LENGTH> result;
	for (int i = 0; i < KordleMachine::KORDLE_LENGTH; i++)
	{
		result[i] = false;
		if (visited[i] == -1)
			continue;
		if (answer[i] == queryString[i])
		{
			result[i] = true;
			visited[i] = -1;
		}
	}

	return result;
}

array<bool, KordleMachine::KORDLE_LENGTH> checkYellows(wstring answer, wstring queryString, array<int, 6>& visited)
{
	array<bool, KordleMachine::KORDLE_LENGTH> result;
	for (int i = 0; i < KordleMachine::KORDLE_LENGTH; i++)
	{
		result[i] = false;
		if (visited[i] == -1)
			continue;
		for (int j = 0; j < KordleMachine::KORDLE_LENGTH; j++)
		{
			if (visited[j] == -1)
				continue;
			if (i == j)
				continue;
			if (answer[j] == queryString[i])
			{
				result[i] = true;
				visited[j] = -1;
			}
		}
	}

	return result;
}

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
	return KordleMachine::queryKordle(answer, queryString);
}

KordleResult KordleMachine::queryKordle(wstring answer, wstring queryString)
{
	array<int, KordleMachine::KORDLE_LENGTH> visited;

	for (int i = 0; i < KordleMachine::KORDLE_LENGTH; i++) 
	{
		visited[i] = i;
	}

	array<bool, KordleMachine::KORDLE_LENGTH> resultGreen = checkGreens(answer, queryString, visited);

	array<bool, KordleMachine::KORDLE_LENGTH> resultYellow = checkYellows(answer, queryString, visited);

	return makeKordleResult(resultGreen, resultYellow, queryString);
}

int KordleMachine::getCount()
{
	return count;
}
