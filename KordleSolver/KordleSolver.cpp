#include "KordleSolver.h"
#include "WordBank.h"
#include <vector>
#include <set>

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

/**
 * @brief 
 * It removes the words that contains duplicated characters, in queryable words list. (for performance)
*/
void KordleSolver::optimizeQueryableWords()
{
	for (vector<wstring>::iterator iter = this->queryableWords.begin(); iter != queryableWords.end();)
	{
		bool erased = false;
		set<wchar_t> visited;
		for (int i = 0; i < KordleMachine::KORDLE_LENGTH; i++)
		{
			if (visited.find(iter->at(i)) == visited.end())
			{
				visited.insert(iter->at(i));
			}
			else
			{
				iter = queryableWords.erase(iter);
				erased = true;
				break;
			}
		}
		if(!erased)
			iter++;
	}
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

void KordleSolver::setStrategy(KordleStrategy* strategy)
{
	delete this->strategy;
	this->strategy = strategy;
}

Cloneable* KordleSolver::clone()
{
	KordleSolver* cloned = new KordleSolver(static_cast<KordleStrategy*>(this->strategy->clone()));
	cloned->queryableWords = this->queryableWords;
	cloned->validWords = this->validWords;
	cloned->countQueried = this->countQueried;
	return cloned;
}

bool KordleSolver::isValid(wstring target, KordleResult result)
{
	array<bool, KordleMachine::KORDLE_LENGTH> visited;

	for (int i = 0; i < KordleMachine::KORDLE_LENGTH; i++)
		visited[i] = false;

	for (int i = 0; i < KordleMachine::KORDLE_LENGTH; i++)
	{
		if (result.result.at(i) == KordleColor::GREEN)
		{
			if (result.queriedString.at(i) != target.at(i))
			{
				return false;
			}
			visited[i] = true;
		}
	}

	for (int i = 0; i < KordleMachine::KORDLE_LENGTH; i++)
	{
		if (result.result.at(i) == KordleColor::YELLOW)
		{
			if (result.queriedString.at(i) == target.at(i))
				return false;
			bool flag = false;
			for (int j = 0; j < KordleMachine::KORDLE_LENGTH; j++)
			{
				if (target.at(j) == result.queriedString.at(i) && !visited[j])
				{
					flag = true;
					visited[j] = true;
					break;
				}
			}
			if (!flag)
				return false;
		}

		if (result.result.at(i) == KordleColor::BLACK)
		{
			for (int j = 0; j < KordleMachine::KORDLE_LENGTH; j++)
			{
				if (result.queriedString.at(i) == target.at(j) && !visited[j])
					return false;
			}
		}
	}
	return true;
}