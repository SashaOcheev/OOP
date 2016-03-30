#pragma once
#include <iostream>
#include <map>
#include <algorithm>
#include <string>
#include <iterator>
#include <set>
#include <functional>

class CStringsCount
{
public:
	CStringsCount() = default;
	
	std::map<std::string, size_t>::iterator Begin();
	std::map<std::string, size_t>::iterator End();

	void IncOrAdd(std::string word);
	void PutToOutStream(std::ostream & stream, std::string const& delimBeneathPairMembers = " - ", std::string const& delimBeneathMapMembers = "\n") const;

private:
	std::map<std::string, size_t> m_map;
};

void AddWordsFromStringToCStringsCount(std::string const& str, CStringsCount &wordsCount);