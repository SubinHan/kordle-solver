#pragma once
#include "Cloneable.h"
#include "KordleMachine.h"
#include "KordleStrategy.h"
#include <vector>
#include <string>

using namespace std;

class KordleSolver : public Cloneable
{
private:
	KordleMachine* machine;
	KordleStrategy* strategy;
	vector<wstring> validWords;
	vector<wstring> queryableWords;
	int countQueried;

private:
	bool isValid(wstring target, KordleResult result);

public:
	KordleSolver() = delete;
	KordleSolver(KordleStrategy* strategy);
	~KordleSolver();

	void optimizeQueryableWords();
	wstring calculateNextWord();
	void inputResult(KordleResult result);
	void setStrategy(KordleStrategy* strategy);

	virtual Cloneable* clone() override;
};