#include "WordCalculator.h"

const int getLength2D(char** arr) {
	return sizeof(arr) / sizeof(arr[0]);
}

void getResult(char* word, char* test, int* outputGreen, int* outputYellow)
{
	const int length = 6;

	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length; j++)
		{
			if (word[i] == test[j])
			{
				if (i == j)
					outputGreen++;
				else
					outputYellow++;
			}
		}
	}

}

float WordCalculator::calculateExpectedKills(char** possible, char** valid, char* word) {
	const int lengthPossible = getLength2D(possible);
	const int lengthValid = getLength2D(valid);

	return 0;
}

int WordCalculator::getHighestEntropy(char** possible, char** valid) 
{
	const int lengthPossible = getLength2D(possible);
	const int lengthValid = getLength2D(valid);

	for (int i = 0; i < lengthValid; i++) 
	{
		char* word = valid[i];
		for (int j = 0; j < lengthPossible; j++) 
		{
			char* test = possible[j];
			int green(0), yellow(0);
			getResult(word, test, &green, &yellow);
		}
	}

	return 0;
}

