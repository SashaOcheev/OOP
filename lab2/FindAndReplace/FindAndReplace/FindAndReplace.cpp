// FindAndReplace.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "FindAndReplace.h"

std::string FindAndReplace(std::string const& subject, std::string const& search, std::string const& replace)
{
	if (search.empty())
	{
		return subject;
	}
	
	std::string result = "";
	size_t start = 0;
	size_t newStart = 0;
	while ((newStart = subject.find(search, start)) != std::string::npos)
	{
		result.append(subject.substr(start, newStart));
		result.append(replace);
		start = newStart + search.size();
	}
	
	result.append(subject.substr(start, subject.size()));

	return result;
}

