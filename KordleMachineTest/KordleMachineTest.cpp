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
#include <ctime>
#include <chrono>
#include <format>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace KordleMachineTest
{
	TEST_CLASS(KordleMachineTest)
	{
	public:
		TEST_METHOD(kordleMachineTest1)
		{
			KordleMachine machine = KordleMachine(L"���̤�������"s);
			KordleResult result1 = machine.queryKordle(L"���ä����ä�"s);
			KordleResult result2 = machine.queryKordle(L"���ŤӤ�����"s);
			KordleResult result3 = machine.queryKordle(L"���̤����̤�"s);

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
			KordleMachine machine = KordleMachine(L"���̤����̤�"s);
			KordleResult result1 = machine.queryKordle(L"���Ť����Ť�"s);
			KordleResult result2 = machine.queryKordle(L"������������"s);
			KordleResult result3 = machine.queryKordle(L"������������"s);

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
			KordleMachine machine = KordleMachine(L"������������"s);
			KordleResult result1 = machine.queryKordle(L"������������"s);
			KordleResult result2 = machine.queryKordle(L"������������"s);
			KordleResult result3 = machine.queryKordle(L"������������"s);

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
			KordleMachine machine = KordleMachine(L"������������"s);
			KordleResult result1 = machine.queryKordle(L"������������"s);
			KordleResult result2 = machine.queryKordle(L"������������"s);
			KordleResult result3 = machine.queryKordle(L"������������"s);

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
			KordleMachine machine = KordleMachine(L"������������"s);
			KordleResult result1 = machine.queryKordle(L"������������"s);

			Assert::IsTrue(result1.result[0] == KordleColor::GREEN);
			Assert::IsTrue(result1.result[1] == KordleColor::YELLOW);
			Assert::IsTrue(result1.result[2] == KordleColor::YELLOW);
			Assert::IsTrue(result1.result[3] == KordleColor::BLACK);
			Assert::IsTrue(result1.result[4] == KordleColor::GREEN);
			Assert::IsTrue(result1.result[5] == KordleColor::GREEN);
		}

		TEST_METHOD(kordleMachinePerformanceTest)
		{
			auto start = std::chrono::system_clock::now();
			for (int i = 0; i < 10000; i++)
			{
				KordleMachine machine = KordleMachine(L"������������"s);
				KordleResult result1 = machine.queryKordle(L"������������"s);
			}
			auto end = std::chrono::system_clock::now();

			chrono::duration<double> elapsed_seconds = end - start;
			Logger::WriteMessage(to_string(elapsed_seconds.count()).c_str());
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
			expected.push(L"������������"s);
			expected.push(L"������������"s);
			expected.push(L"������������"s);
			expected.push(L"������������"s);
			expected.push(L"������������"s);
			expected.push(L"������������"s);

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

			wstring queried = L"���Ӥ����̤�"s;
			array<KordleColor, KordleMachine::KORDLE_LENGTH> greens;
			for (int i = 0; i < KordleMachine::KORDLE_LENGTH; i++)
			{
				greens[i] = KordleColor::GREEN;
			}
			KordleResult result(greens, queried);
			solver.inputResult(result);

			Assert::AreEqual(queried, solver.calculateNextWord());
		}
	};
}
