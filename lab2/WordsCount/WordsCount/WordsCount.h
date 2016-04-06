#pragma once
#include <iostream>
#include <map>
#include <algorithm>
#include <string>
#include <functional>

void PutMapToOutStream(std::ostream & stream, std::map<std::string, unsigned> const& wordsCount,
	std::string const& delimBeneathPairMembers = " - ", std::string const& delimBeneathMapMembers = "\n");

void AddWordsFromStringToStringsCountMap(std::string const& str, std::map<std::string, unsigned> &wordsCount);