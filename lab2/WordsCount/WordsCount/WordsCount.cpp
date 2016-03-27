// WordsCount.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <map>
#include <algorithm>
#include <string>
#include <iterator>

class CWordCount
{
public:
	CWordCount() = default;

	void IncOrAdd(std::string word);
	void PutToStream(std::ostream & stream, std::string const& delimBeneathPairMembers = " - ", std::string const& delimBeneathMapMembers = "\n") const;

private:
	std::map<std::string, size_t> m_map;
};

void CWordCount::IncOrAdd(std::string word)
{
	m_map[word]++;
}

void CWordCount::PutToStream(std::ostream & stream, std::string const& delimBeneathPairMembers, std::string const& delimBeneathMapMembers) const
{
	for (auto it = m_map.cbegin(); it != m_map.cend(); it++)
		stream << it->first << delimBeneathPairMembers << it->second << delimBeneathMapMembers;
}

int main()
{
	CWordCount wordCount;
	wordCount.IncOrAdd("abc");
	wordCount.IncOrAdd("de");
	wordCount.IncOrAdd("abc");
	wordCount.PutToStream(std::cout);
    return 0;
}

