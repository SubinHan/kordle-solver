#include <iostream>
#include <string>
#include "KordleMachine.h"

using namespace std;

int main()
{
	wstring a = L"안녕하세요.";
	wstring b = L"ㄱㅜㄴㄷㅏㅣ";
	std::locale::global(std::locale(""));
	wcout << a[0] << a[1] << a[2] << a[3] << a[4] << endl;
	wcout << a << endl;

	wcout << b[0] << b[1] << b[2] << b[3] << b[4] << b[5] << endl;
	wcout << b << endl;

	if (a[0] == '안')
		cout << "atrue" << endl;
	if (b[0] == 'ㄱ')
		cout << "btrue1" << endl;
	if (b[0] == L'ㄱ')
		cout << "btrue2" << endl;

	KordleMachine machine = KordleMachine(L"ㄱㅜㄴㄷㅏㅣ"s);
	KordleResult result1 = machine.queryKordle(L"ㅈㅓㄹㅈㅓㅇ"s);
	KordleResult result2 = machine.queryKordle(L"ㄱㅕㅣㄷㅏㄴ"s);

	if (result1.result[0] == KordleColor::BLACK)
		cout << "rtrue1" << endl;
	return 0;
}