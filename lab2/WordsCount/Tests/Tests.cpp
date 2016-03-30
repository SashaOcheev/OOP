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

	BOOST_AUTO_TEST_CASE(ordinary_string)
	{
		StringSizeTMap ethalonMap = 
		{
			{ "aww", 2 },
			{ "down", 1 },
			{ "drive", 1 },
			{ "gonna", 1 },
			{ "heat", 1 },
			{ "heat,", 1 },
			{ "insane", 1 },
			{ "it", 1 },
			{ "its", 1 },
			{ "light", 1 },
			{ "light,", 1 },
			{ "me", 2 },
			{ "my", 1 },
			{ "tickle", 1 },
			{ "to", 1 },
			{ "toes", 1 },
			{ "white", 4 },
		};
		std::string str = "white    light,\taww white light its gonna drive me insane ";
		str.append("white heat, aww white \t\t heat it tickle me down to my toes");
		CStringsCount testStringCount;
		AddWordsFromStringToCStringsCount(str, testStringCount);
		BOOST_CHECK(ethalonMap == StringSizeTMap(testStringCount.Begin(), testStringCount.End()));

		testStringCount.Clear();
		str = "   white    light,\taww white light its gonna drive me insane ";
		str.append("white heat, aww white \t\t heat it tickle me down to my toes \t\t");
		AddWordsFromStringToCStringsCount(str, testStringCount);
		BOOST_CHECK(ethalonMap == StringSizeTMap(testStringCount.Begin(), testStringCount.End()));
	}

BOOST_AUTO_TEST_SUITE_END()
