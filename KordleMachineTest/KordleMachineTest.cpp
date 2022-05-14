#include "pch.h"
#include "CppUnitTest.h"
#include "../KordleSolver/KordleMachine.cpp"
#include "../KordleSolver/WordBank.cpp"
#include "../KordleSolver/KordleSolver.cpp"
#include "../KordleSolver/KordleEntropyStrategy.cpp"
#include "../KordleSolver/KordleFirstWordStrategy.cpp"
#include "../Luna.Tools/Utils.cpp"
#include <string>
#include <queue>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace KordleMachineTest
{
	TEST_CLASS(KordleMachineTest)
	{
	public:
		TEST_METHOD(kordleMachineTest1)
		{
			KordleMachine machine = KordleMachine(L"丑厄中之凶太"s);
			KordleResult result1 = machine.queryKordle(L"元勻予元勻仄"s);
			KordleResult result2 = machine.queryKordle(L"丑勿太之凶中"s);
			KordleResult result3 = machine.queryKordle(L"丑厄丑丑厄中"s);

			Assert::IsTrue(result1.result[0] == KordleColor::BLACK);
			Assert::IsTrue(result2.result[0] == KordleColor::GREEN);
			Assert::IsTrue(result2.result[2] == KordleColor::YELLOW);
			Assert::IsFalse(result2.result[2] == KordleColor::GREEN);
			Assert::IsTrue(result3.result[0] == KordleColor::GREEN);
			Assert::IsTrue(result3.result[2] == KordleColor::BLACK);
			Assert::IsTrue(result3.result[3] == KordleColor::BLACK);
		}

		TEST_METHOD(kordleMachineTest2)
		{
			KordleMachine machine = KordleMachine(L"丑厄丑丑厄中"s);
			KordleResult result1 = machine.queryKordle(L"丑勿仄丑勿太"s);
			KordleResult result2 = machine.queryKordle(L"丑丑凶丑丑太"s);
			KordleResult result3 = machine.queryKordle(L"丑丑丑丑丑丑"s);

			Assert::IsTrue(result1.result[0] == KordleColor::GREEN);
			Assert::IsTrue(result1.result[1] == KordleColor::BLACK);
			Assert::IsTrue(result1.result[2] == KordleColor::BLACK);
			Assert::IsTrue(result1.result[3] == KordleColor::GREEN);
			Assert::IsTrue(result1.result[4] == KordleColor::BLACK);
			Assert::IsTrue(result1.result[5] == KordleColor::BLACK);

			Assert::IsTrue(result2.result[0] == KordleColor::GREEN);
			Assert::IsTrue(result2.result[1] == KordleColor::YELLOW);
			Assert::IsTrue(result2.result[2] == KordleColor::BLACK);
			Assert::IsTrue(result2.result[3] == KordleColor::GREEN);
			Assert::IsTrue(result2.result[4] == KordleColor::BLACK);
			Assert::IsTrue(result2.result[5] == KordleColor::BLACK);

			Assert::IsTrue(result3.result[0] == KordleColor::GREEN);
			Assert::IsTrue(result3.result[1] == KordleColor::BLACK);
			Assert::IsTrue(result3.result[2] == KordleColor::GREEN);
			Assert::IsTrue(result3.result[3] == KordleColor::GREEN);
			Assert::IsTrue(result3.result[4] == KordleColor::BLACK);
			Assert::IsTrue(result3.result[5] == KordleColor::BLACK);
		}

		TEST_METHOD(kordleMachineTest3)
		{
			KordleMachine machine = KordleMachine(L"丑丑中中丑丑"s);
			KordleResult result1 = machine.queryKordle(L"中中丑丑中中"s);
			KordleResult result2 = machine.queryKordle(L"中中中中中中"s);
			KordleResult result3 = machine.queryKordle(L"丑丑丑丑丑丑"s);

			Assert::IsTrue(result1.result[0] == KordleColor::YELLOW);
			Assert::IsTrue(result1.result[1] == KordleColor::YELLOW);
			Assert::IsTrue(result1.result[2] == KordleColor::YELLOW);
			Assert::IsTrue(result1.result[3] == KordleColor::YELLOW);
			Assert::IsTrue(result1.result[4] == KordleColor::BLACK);
			Assert::IsTrue(result1.result[5] == KordleColor::BLACK);

			Assert::IsTrue(result2.result[0] == KordleColor::BLACK);
			Assert::IsTrue(result2.result[1] == KordleColor::BLACK);
			Assert::IsTrue(result2.result[2] == KordleColor::GREEN);
			Assert::IsTrue(result2.result[3] == KordleColor::GREEN);
			Assert::IsTrue(result2.result[4] == KordleColor::BLACK);
			Assert::IsTrue(result2.result[5] == KordleColor::BLACK);

			Assert::IsTrue(result3.result[0] == KordleColor::GREEN);
			Assert::IsTrue(result3.result[1] == KordleColor::GREEN);
			Assert::IsTrue(result3.result[2] == KordleColor::BLACK);
			Assert::IsTrue(result3.result[3] == KordleColor::BLACK);
			Assert::IsTrue(result3.result[4] == KordleColor::GREEN);
			Assert::IsTrue(result3.result[5] == KordleColor::GREEN);
		}

		TEST_METHOD(kordleMachineTest4)
		{
			KordleMachine machine = KordleMachine(L"丑中丑中丑中"s);
			KordleResult result1 = machine.queryKordle(L"丑丑中丑中中"s);
			KordleResult result2 = machine.queryKordle(L"中中丑中丑丑"s);
			KordleResult result3 = machine.queryKordle(L"丑丑丑中中中"s);

			Assert::IsTrue(result1.result[0] == KordleColor::GREEN);
			Assert::IsTrue(result1.result[1] == KordleColor::YELLOW);
			Assert::IsTrue(result1.result[2] == KordleColor::YELLOW);
			Assert::IsTrue(result1.result[3] == KordleColor::YELLOW);
			Assert::IsTrue(result1.result[4] == KordleColor::YELLOW);
			Assert::IsTrue(result1.result[5] == KordleColor::GREEN);

			Assert::IsTrue(result2.result[0] == KordleColor::YELLOW);
			Assert::IsTrue(result2.result[1] == KordleColor::GREEN);
			Assert::IsTrue(result2.result[2] == KordleColor::GREEN);
			Assert::IsTrue(result2.result[3] == KordleColor::GREEN);
			Assert::IsTrue(result2.result[4] == KordleColor::GREEN);
			Assert::IsTrue(result2.result[5] == KordleColor::YELLOW);

			Assert::IsTrue(result3.result[0] == KordleColor::GREEN);
			Assert::IsTrue(result3.result[1] == KordleColor::YELLOW);
			Assert::IsTrue(result3.result[2] == KordleColor::GREEN);
			Assert::IsTrue(result3.result[3] == KordleColor::GREEN);
			Assert::IsTrue(result3.result[4] == KordleColor::YELLOW);
			Assert::IsTrue(result3.result[5] == KordleColor::GREEN);
		}

		TEST_METHOD(kordleMachineTest5)
		{
			KordleMachine machine = KordleMachine(L"中丑中中中中"s);
			KordleResult result1 = machine.queryKordle(L"中中丑丑中中"s);

			Assert::IsTrue(result1.result[0] == KordleColor::GREEN);
			Assert::IsTrue(result1.result[1] == KordleColor::YELLOW);
			Assert::IsTrue(result1.result[2] == KordleColor::YELLOW);
			Assert::IsTrue(result1.result[3] == KordleColor::BLACK);
			Assert::IsTrue(result1.result[4] == KordleColor::GREEN);
			Assert::IsTrue(result1.result[5] == KordleColor::GREEN);
		}
	};

	TEST_CLASS(InitTest)
	{
	public:

		TEST_METHOD(initTest)
		{
			WordBank* wordBank = WordBank::getInstance();
			vector<wstring> queryableWords = wordBank->getQueryableWords();

			queue<wstring> expected;
			queue<wstring> actual;
			expected.push(L"丑丑凶丑丑凶"s);
			expected.push(L"丑丑凶丑丑厄"s);
			expected.push(L"丑丑凶丑丑太"s);
			expected.push(L"丑丑凶丑之太"s);
			expected.push(L"丑丑凶丑今太"s);
			expected.push(L"丑丑凶丑元太"s);

			for (int i = 0; i < expected.size(); i++)
			{
				actual.push(queryableWords.at(i));
			}

			while (!expected.empty())
			{
				Assert::AreEqual(peekAndPop(expected), peekAndPop(actual));
			}
		}
	};

	TEST_CLASS(KordleSolverTest)
	{
	public:
		TEST_METHOD(kordleSolverTest)
		{
			KordleSolver solver(new KordleFirstWordStrategy());

			wstring queried = L"仄太仆今厄予"s;
			array<bool, KordleMachine::KORDLE_LENGTH> yellows;
			for (int i = 0; i < KordleMachine::KORDLE_LENGTH; i++)
			{
				yellows[i] = false;
			}
			array<bool, KordleMachine::KORDLE_LENGTH> greens;
			for (int i = 0; i < KordleMachine::KORDLE_LENGTH; i++)
			{
				greens[i] = true;
			}
			KordleResult result = KordleMachine::makeKordleResult(greens, yellows, queried);
			solver.inputResult(result);

			Assert::AreEqual(queried, solver.calculateNextWord());
		}
	};
}
