#include <iostream>
#include <string>
#include "KordleMachine.h"
#include "KordleSolver.h"
#include "KordleEntropyStrategy.h"
#include "KordleFirstWordStrategy.h"
#include "WordBank.h"

using namespace std;

int testAllValid();
int interaction();
void printResult(KordleResult result);
bool isCorrect(KordleResult result);

int main()
{
	return interaction();
}

int interaction()
{
	cout << "init.." << endl;
	KordleSolver optimized(new KordleEntropyStrategy());
	cout << "solver init completed" << endl;

	while (true)
	{
		cout << endl;
		cout << "==NEW GAME==" << endl;
		KordleSolver* solver = static_cast<KordleSolver*>(optimized.clone());
		while (true)
		{
			wstring best = solver->calculateNextWord();
			wcout << "The best word to query: " << best << endl;

			array<KordleColor, KordleMachine::KORDLE_LENGTH> kordleResult;
			while (true)
			{
				string result;
				bool isInvalid = false;
				cout << "Please enter the result: ";
				cin >> result;

				if (result.size() != 6)
					isInvalid = true;

				for (int i = 0; i < KordleMachine::KORDLE_LENGTH; i++)
				{
					switch (result[i])
					{
					case 'G':
						kordleResult[i] = KordleColor::GREEN;
						break;
					case 'Y':
						kordleResult[i] = KordleColor::YELLOW;
						break;
					case 'B':
						kordleResult[i] = KordleColor::BLACK;
						break;
					default:
						isInvalid = true;
						break;
					}
				}

				if (isInvalid)
					cout << "Invalid input, please enter again" << endl;
				else
					break;
			}

			bool completed = true;
			for (int i = 0; i < KordleMachine::KORDLE_LENGTH; i++)
			{
				if (kordleResult[i] != KordleColor::GREEN)
					completed = false;
			}

			if (completed)
				break;

			KordleResult result(kordleResult, best);
			solver->inputResult(result);
		}
	}

	return 0;
}

int testAllValid()
{
	wcin.imbue(locale("korean"));
	wcout.imbue(locale("korean"));

	cout << "init.." << endl;
	KordleSolver optimized(new KordleEntropyStrategy());
	cout << "solver init completed" << endl;
	//cout << "optimizing solver.. it takes for minutes" << endl;
	//optimized.optimizeQueryableWords();
	//cout << "solver optimizing completed" << endl;

	WordBank* bank = WordBank::getInstance();
	vector<wstring> validWords = bank->getValidWords();

	int sumCount = 0;
	int maxCount = 0;

	for (vector<wstring>::iterator iter = validWords.begin(); iter != validWords.end(); iter++)
	{
		KordleSolver *solver = static_cast<KordleSolver*>(optimized.clone());

		KordleMachine machine(*iter);
		wcout << L"solution word: "s << *iter << endl;
		KordleResult* result;

		while (true)
		{
			wstring best = solver->calculateNextWord();
			wcout << best << endl;
			result = new KordleResult(machine.queryKordle(best));
			printResult(*result);
			solver->inputResult(*result);

			if (isCorrect(*result))
			{
				cout << "count: " << machine.getCount() << endl;
				sumCount += machine.getCount();
				break;
			}

			delete result;
		}

		int numSolved = distance(validWords.begin(), iter);
		double average = (double)sumCount / (double)(numSolved + 1);
		cout << "solved: " << numSolved << "/" << distance(validWords.begin(), validWords.end()) << endl;
		cout << "now average: " << average << endl;
		if (machine.getCount() > maxCount)
			maxCount = machine.getCount();
		cout << "max query count: " << maxCount << endl;;

		delete result;
		delete solver;
	}
	
	return 0;
}

void printResult(KordleResult result)
{
	for (KordleColor color : result.result)
	{
		if (color == KordleColor::BLACK)
			cout << "B";
		if (color == KordleColor::YELLOW)
			cout << "Y";
		if (color == KordleColor::GREEN)
			cout << "G";
	}
	cout << endl;
}

bool isCorrect(KordleResult result)
{
	for (KordleColor color : result.result)
	{
		if (color != KordleColor::GREEN)
			return false;
	}
	return true;
}