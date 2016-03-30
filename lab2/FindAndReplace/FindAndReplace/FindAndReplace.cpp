// FindAndReplace.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "FindAndReplace.h"

std::string FindAndReplace(std::string const& subject, std::string const& search, std::string const& replace)
{
	if (search.empty())
		return subject;
	auto resString = subject;
	size_t startForSearch = 0;
	while (true)
	{
		startForSearch = resString.find(search, startForSearch);
		if (startForSearch != std::string::npos)
		{
			resString.replace(startForSearch, search.length(), replace);
			startForSearch += replace.length();
			return resString;
		}
	}
}

