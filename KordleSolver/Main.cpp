#include <iostream>
#include <string>
#include "KordleMachine.h"
#include "KordleSolver.h"
#include "KordleEntropyStrategy.h"
#include "KordleFirstWordStrategy.h"

using namespace std;

void printResult(KordleResult result);
bool isCorrect(KordleResult result);

int main()
{
	wcin.imbue(locale("korean"));
	wcout.imbue(locale("korean"));

	cout << "init.." << endl;
	KordleMachine machine(L"しでびずぬぉ"s);
	cout << "machine init completed" << endl;
	KordleSolver solver(new KordleEntropyStrategy());
	cout << "solver init completed" << endl;

	KordleResult* result;

	while (true)
	{
		wstring best = solver.calculateNextWord();
		wcout << best << endl;
		result = new KordleResult(machine.queryKordle(best));
		printResult(*result);
		solver.inputResult(*result);

		if (isCorrect(*result))
			break;

		delete result;
	}

	delete result;
	
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