// Test-Driven-Development.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <boost/test/output/compiler_log_formatter.hpp>
#include "../WordsCount/WordsCount.h"

typedef std::map<std::string, size_t> StringSizeTMap;

BOOST_AUTO_TEST_SUITE(AddWordsFromStringToCStringsCount_test)

	BOOST_AUTO_TEST_CASE(string_without_words)
	{
		StringSizeTMap emptyMap;
		CStringsCount testStringCount;
		AddWordsFromStringToCStringsCount("", testStringCount);
		BOOST_CHECK(emptyMap == StringSizeTMap(testStringCount.Begin(), testStringCount.End()));
		AddWordsFromStringToCStringsCount(" ", testStringCount);
		BOOST_CHECK(emptyMap == StringSizeTMap(testStringCount.Begin(), testStringCount.End()));
		AddWordsFromStringToCStringsCount("   ", testStringCount);
		BOOST_CHECK(emptyMap == StringSizeTMap(testStringCount.Begin(), testStringCount.End()));
		AddWordsFromStringToCStringsCount("\t", testStringCount);
		BOOST_CHECK(emptyMap == StringSizeTMap(testStringCount.Begin(), testStringCount.End()));
		AddWordsFromStringToCStringsCount("\t\t\t\t\t", testStringCount);
		BOOST_CHECK(emptyMap == StringSizeTMap(testStringCount.Begin(), testStringCount.End()));
		AddWordsFromStringToCStringsCount("   \t\t  \t \t", testStringCount);
		BOOST_CHECK(emptyMap == StringSizeTMap(testStringCount.Begin(), testStringCount.End()));

	}

	BOOST_AUTO_TEST_CASE(string_with_not_words_in_begin_or_end)
	{

	}

	BOOST_AUTO_TEST_CASE(ordinary_string)
	{

	}

BOOST_AUTO_TEST_SUITE_END()
