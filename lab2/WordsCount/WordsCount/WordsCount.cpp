// WordsCount.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "WordsCount.h"

void PutMapToOutStream(std::ostream & stream, std::map<std::string, unsigned> const& map,
	std::string const& delimBeneathPairMembers, std::string const& delimBeneathMapMembers)
{
	for (auto it = map.cbegin(); it != map.cend(); it++)
		stream << it->first << delimBeneathPairMembers << it->second << delimBeneathMapMembers;
}

void AddWordsFromStringToStringsCountMap(std::string const& str, std::map<std::string, unsigned> &wordsCount)
{
	std::string notAllowedChars = " \n\t";

	size_t allowedCharPos = 0;
	size_t notAllowedCharPos = 0;
	while (notAllowedCharPos != std::string::npos)
	{
		allowedCharPos = str.find_first_not_of(notAllowedChars, notAllowedCharPos);
		notAllowedCharPos = str.find_first_of(notAllowedChars, allowedCharPos);
		if (allowedCharPos != std::string::npos)
			wordsCount[str.substr(allowedCharPos, notAllowedCharPos - allowedCharPos)] += 1;
	}
}


