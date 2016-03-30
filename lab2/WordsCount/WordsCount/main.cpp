#include "stdafx.h"
#include "WordsCount.h"

int main()
{
	CStringsCount wordsCount;
	std::string str;
	std::getline(std::cin, str);
	AddWordsFromStringToCStringsCount(str, wordsCount);
	wordsCount.PutToOutStream(std::cout);

	return 0;
}