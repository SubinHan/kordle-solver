#include "KordleSolver.h"
#include "WordBank.h"
#include <vector>
#include <iterator>

using namespace std;

KordleSolver::KordleSolver(KordleStrategy* strategy)
{
	this->strategy = strategy;
	WordBank* bank = WordBank::getInstance();
	this->queryableWords = bank->getQueryableWords();
	this->validWords = bank->getValidWords();
}

KordleSolver::~KordleSolver()
{
	delete strategy;
}

wstring KordleSolver::calculateNextWord()
{
	return strategy->calculateNextWord(this->validWords, this->queryableWords);
}

void KordleSolver::inputResult(KordleResult result)
{
	for (vector<wstring>::iterator iter = this->validWords.begin(); iter != this->validWords.end();)
	{
		if (!isValid(*iter, result))
		{
			iter = this->validWords.erase(iter);
		}
		else
		{
			iter++;
		}
	}
}

bool KordleSolver::isValid(wstring target, KordleResult result)
{
	for (int i = 0; i < KordleMachine::KORDLE_LENGTH; i++)
	{
		if (result.result.at(i) == KordleColor::GREEN)
		{
			if (result.queriedString.at(i) != target.at(i))
			{
				return false;
			}
		}

		if (result.result.at(i) == KordleColor::YELLOW)
		{
			bool flag = false;
			for (int j = 0; j < KordleMachine::KORDLE_LENGTH; j++)
			{
				if (target.at(j) == result.queriedString.at(i))
				{
					flag = true;
				}
			}
			if (!flag)
				return false;
		}
	}
	return true;
}