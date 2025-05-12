#include "WordBank.h"
#include "CsvIOStream.h"

WordBank* WordBank::instance = nullptr;

WordBank* WordBank::getInstance()
{
	if (instance == nullptr)
	{
		instance = new WordBank();
	}

	return instance;
}

vector<wstring> WordBank::getValidWords()
{
	return *validWords;
}

vector<wstring> WordBank::getQueryableWords()
{
	return *queryableWords;
}

WordBank::WordBank()
{
	validWords = new vector<wstring>();
	queryableWords = new vector<wstring>();

	CsvReader* reader = new CsvReader("./ValidWords.csv");

	while (reader->hasNext())
	{
		validWords->push_back(reader->readNext());
	}

	delete reader;

	reader = new CsvReader("./QueryableWords.csv");

	while (reader->hasNext())
	{
		queryableWords->push_back(reader->readNext());
	}

	delete reader;
}
