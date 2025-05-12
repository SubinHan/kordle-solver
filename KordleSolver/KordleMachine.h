#pragma once
#include "Cloneable.h"
#include <array>
#include <string>

using namespace std;

class KordleResult;
enum class KordleColor;

class KordleMachine {
private:
	wstring answer;
	int count;
public:
	static const int KORDLE_LENGTH = 6;

public:
	KordleMachine() = delete;
	KordleMachine(wstring answer) : answer(answer), count(0) {}
	KordleResult queryKordle(wstring queryString);
	static KordleResult queryKordle(wstring answer, wstring queryString);
	int getCount();
};

class KordleResult {
public:
	const array<KordleColor, KordleMachine::KORDLE_LENGTH> result;
	const wstring queriedString;

public:
	KordleResult() = delete;
	KordleResult(array<KordleColor, KordleMachine::KORDLE_LENGTH> const& result, wstring queriedString) : result(result), queriedString(queriedString) {}
};

enum class KordleColor {
	GREEN,
	YELLOW,
	BLACK
};