#include "CsvIOStream.h"

CsvReader::CsvReader(string path)
{
	std::locale::global(std::locale("Korean"));
	file = new wifstream();
	file->open(path);
	bHasNext = true;

	if (!file)
	{
		throw std::exception("File not found");
	}
}

wstring CsvReader::readNext()
{
	wostringstream builder;
	bool inQuote = false;

	while (file->good()) 
	{
		wchar_t c = file->get();
		switch (c)
		{
		case '\"':
			inQuote = !inQuote;
			if (inQuote)
			{
				builder.str(LR"()"s);
			}
			break;
		case ',':
		case '\n':
		{
			if (inQuote)
				break;
			return builder.str();
			break;
		}
		case 65535:
			bHasNext = false;
			break;
		default:
			builder << c;
			break;
		}
	}

	if (file->eof())
		bHasNext = false;

	return builder.str();
}

bool CsvReader::hasNext()
{
	return bHasNext;
}

CsvReader::~CsvReader()
{
	file->close();
	delete file;
}

CsvReader& operator>>(CsvReader& inputStream, wstring& s)
{
	s = inputStream.readNext();
	return inputStream;
}