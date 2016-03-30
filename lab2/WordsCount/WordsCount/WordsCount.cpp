// WordsCount.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "WordsCount.h"

std::map<std::string, size_t>::iterator CStringsCount::Begin()
{
	return m_map.begin();
}

std::map<std::string, size_t>::iterator CStringsCount::End()
{
	return m_map.end();
}

void CStringsCount::Clear()
{
	m_map.clear();
}

void CStringsCount::IncOrAdd(std::string word)
{
	m_map[word]++;
}

void CStringsCount::PutToOutStream(std::ostream & stream, std::string const& delimBeneathPairMembers, std::string const& delimBeneathMapMembers) const
{
	for (auto it = m_map.cbegin(); it != m_map.cend(); it++)
		stream << it->first << delimBeneathPairMembers << it->second << delimBeneathMapMembers;
}

void AddWordsFromStringToCStringsCount(std::string const& str, CStringsCount &wordsCount)
{
	std::string notAllowedChars = " \n\t";

	size_t allowedCharPos = 0;
	size_t notAllowedCharPos = 0;
	while (notAllowedCharPos != std::string::npos)
	{
		allowedCharPos = str.find_first_not_of(notAllowedChars, notAllowedCharPos);
		notAllowedCharPos = str.find_first_of(notAllowedChars, allowedCharPos);
		if (allowedCharPos != std::string::npos)
			wordsCount.IncOrAdd(str.substr(allowedCharPos, notAllowedCharPos - allowedCharPos));
	}
}


