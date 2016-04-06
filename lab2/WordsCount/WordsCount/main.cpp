#include "stdafx.h"
#include "WordsCount.h"

int main()
{
	std::map<std::string, unsigned> wordsCount;
	std::string str;
	std::getline(std::cin, str);
	AddWordsFromStringToStringsCountMap(str, wordsCount);
	PutMapToOutStream(std::cout, wordsCount);

	return 0;
}