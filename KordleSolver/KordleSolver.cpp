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
	this->countQueried = 0;
}

KordleSolver::~KordleSolver()
{
	delete strategy;
}

wstring KordleSolver::calculateNextWord()
{
	return strategy->calculateNextWord(this->validWords, this->queryableWords, countQueried);
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
	countQueried++;
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
			if (result.queriedString.at(i) == target.at(i))
				return false;
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

		if (result.result.at(i) == KordleColor::BLACK)
		{
			if (result.queriedString.at(i) == target.at(i))
				return false;
		}
	}
	return true;
}