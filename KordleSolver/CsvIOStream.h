#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class CsvReader
{
private:
	wifstream* file;
	bool bHasNext;

private:

public:
	CsvReader(string path);
	wstring readNext();
	bool hasNext();
	~CsvReader();
};

CsvReader& operator >>(CsvReader& inputStream, const wstring& s);