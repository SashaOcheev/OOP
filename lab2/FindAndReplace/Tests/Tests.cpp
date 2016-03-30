// Tests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <boost/test/output/compiler_log_formatter.hpp>
#include "../FindAndReplace/FindAndReplace.h"


BOOST_AUTO_TEST_SUITE(FindAndReplace_test)

BOOST_AUTO_TEST_CASE(with_empty_strings)
{
	std::string sourceString = "sometimes happy, sometimes sad";
	std::string ethalonString = sourceString;

	auto resString = FindAndReplace(sourceString, "", "asd");
	BOOST_CHECK_EQUAL_COLLECTIONS(ethalonString.begin(), ethalonString.end(), resString.begin(), resString.end());

	resString = FindAndReplace(sourceString, "", "");
	BOOST_CHECK_EQUAL_COLLECTIONS(ethalonString.begin(), ethalonString.end(), resString.begin(), resString.end());

	ethalonString = "soimes happy, soimes sad";
	resString = FindAndReplace(sourceString, "met", "");
	BOOST_CHECK_EQUAL_COLLECTIONS(ethalonString.begin(), ethalonString.end(), resString.begin(), resString.end());

	ethalonString = "";
	sourceString = "";
	resString = FindAndReplace(sourceString, "met", "asd");
	BOOST_CHECK_EQUAL_COLLECTIONS(ethalonString.begin(), ethalonString.end(), resString.begin(), resString.end());
}

BOOST_AUTO_TEST_CASE(without_empty_strings)
{
	std::string sourceString = "12312312345";
	std::string ethalonString = "123paste5";
	auto resString = FindAndReplace("12312312345", "1231234", "paste");
	BOOST_CHECK_EQUAL_COLLECTIONS(ethalonString.begin(), ethalonString.end(), resString.begin(), resString.end());

	sourceString = "mamampapa";
	ethalonString = "pastepastempapa";
	resString = FindAndReplace("mamampapa", "ma", "paste");
	BOOST_CHECK_EQUAL_COLLECTIONS(ethalonString.begin(), ethalonString.end(), resString.begin(), resString.end());
}

BOOST_AUTO_TEST_SUITE_END()


