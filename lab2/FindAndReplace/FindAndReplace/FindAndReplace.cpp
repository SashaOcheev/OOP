// FindAndReplace.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "FindAndReplace.h"

std::string FindAndReplace(std::string const& subject, std::string const& search, std::string const& replace)
{
	auto result = subject;
	boost::replace_all(result, search, replace);

	return result;
}