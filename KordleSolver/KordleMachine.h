#pragma once
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

private:
	KordleResult static calculateResult(wstring answer, wstring queryString);

public:
	KordleMachine() = delete;
	KordleMachine(wstring answer) : answer(answer), count(0) {}
	KordleResult queryKordle(wstring queryString);
	static KordleResult queryKordle(wstring answer, wstring queryString);
	static KordleResult makeKordleResult(array<bool, KordleMachine::KORDLE_LENGTH> resultGreen, array<bool, KordleMachine::KORDLE_LENGTH> resultYellow, wstring queryString);
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