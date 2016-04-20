// FindAndReplace.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "FindAndReplace.h"

std::string FindAndReplace(std::string const& subject, std::string const& search, std::string const& replace)
{
	if (search.empty())
		return subject;

	auto result = subject;
	size_t startForSearch = 0;
	while ((startForSearch = result.find(search, startForSearch)) != std::string::npos)
	{
		result.replace(startForSearch, search.length(), replace);
		startForSearch += replace.length();
	}

	return result;
}

