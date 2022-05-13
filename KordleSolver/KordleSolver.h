#pragma once
#include "KordleMachine.h"
#include "KordleStrategy.h"
#include <vector>
#include <string>

using namespace std;

class KordleSolver
{
private:
	KordleMachine* machine;
	KordleStrategy* strategy;
	vector<wstring> validWords;
	vector<wstring> queryableWords;

private:
	bool isValid(wstring target, KordleResult result);

public:
	KordleSolver() = delete;
	KordleSolver(KordleStrategy* strategy);
	~KordleSolver();
	
	wstring calculateNextWord();
	void inputResult(KordleResult result);
};