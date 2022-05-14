#include <iostream>
#include <string>
#include "KordleMachine.h"
#include "KordleSolver.h"
#include "KordleEntropyStrategy.h"
#include "KordleFirstWordStrategy.h"

using namespace std;

void printResult(KordleResult result);

int main()
{
	wcin.imbue(locale("korean"));
	wcout.imbue(locale("korean"));

	cout << "init.." << endl;
	KordleMachine machine(L"¤¡¤Ì¤¤¤§¤¿¤Ó"s);
	cout << "machine init completed" << endl;
	KordleSolver solver(new KordleEntropyStrategy());
	cout << "solver init completed" << endl;

	KordleResult* result;

	array<bool, KordleMachine::KORDLE_LENGTH> yellows1({ false, false, true, false, false, false });
	array<bool, KordleMachine::KORDLE_LENGTH> greens1({true, false, false, false, true, false});
	KordleResult first = KordleMachine::makeKordleResult(greens1, yellows1, L"¤¡¤¡¤Ó¤·¤¿¤±");
	solver.inputResult(first);

	wstring best = solver.calculateNextWord();
	wcout << best << endl;
	result = new KordleResult(machine.queryKordle(best));
	printResult(*result);
	solver.inputResult(*result);
	delete result;

	best = solver.calculateNextWord();
	wcout << best << endl;
	result = new KordleResult(machine.queryKordle(best));
	printResult(*result);
	solver.inputResult(*result);
	delete result;

	best = solver.calculateNextWord();
	wcout << best << endl;
	result = new KordleResult(machine.queryKordle(best));
	printResult(*result);
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