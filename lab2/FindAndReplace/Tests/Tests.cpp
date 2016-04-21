// Tests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <boost/test/output/compiler_log_formatter.hpp>
#include "../FindAndReplace/FindAndReplace.h"


BOOST_AUTO_TEST_SUITE(FindAndReplace_test)

	struct Fixture
	{
		std::string source = "sometimes happy, sometimes sad";
		std::string expected;
	};

	BOOST_FIXTURE_TEST_CASE(replace_empty_to_not_empty, Fixture)
	{
		expected = source;
		auto result = FindAndReplace(source, "", "asd");
		BOOST_CHECK_EQUAL_COLLECTIONS(expected.begin(), expected.end(), result.begin(), result.end());
	}

	BOOST_FIXTURE_TEST_CASE(replace_empty_to_empty, Fixture)
	{
		expected = source;
		auto result = FindAndReplace(source, "", "");
		BOOST_CHECK_EQUAL_COLLECTIONS(expected.begin(), expected.end(), result.begin(), result.end());
	}

	BOOST_FIXTURE_TEST_CASE(replace_existed_to_empty, Fixture)
	{
		expected = "soimes happy, soimes sad";
		auto result = FindAndReplace(source, "met", "");
		BOOST_CHECK_EQUAL_COLLECTIONS(expected.begin(), expected.end(), result.begin(), result.end());
	}


	BOOST_FIXTURE_TEST_CASE(replace_not_existed_to_empty, Fixture)
	{
		expected = source;
		auto result = FindAndReplace(source, "merch", "");
		BOOST_CHECK_EQUAL_COLLECTIONS(expected.begin(), expected.end(), result.begin(), result.end());
	}

	BOOST_FIXTURE_TEST_CASE(replace_not_existed_to_not_empty, Fixture)
	{
		expected = source;
		auto result = FindAndReplace(source, "merch", "asd");
		BOOST_CHECK_EQUAL_COLLECTIONS(expected.begin(), expected.end(), result.begin(), result.end());
	}

	BOOST_FIXTURE_TEST_CASE(replace_existed_to_equalSize, Fixture)
	{
		expected = "soremimes happy, soremimes sad";
		auto result = FindAndReplace(source, "met", "rem");
		BOOST_CHECK_EQUAL_COLLECTIONS(expected.begin(), expected.end(), result.begin(), result.end());
	}

	BOOST_FIXTURE_TEST_CASE(replace_existed_to_lessSize, Fixture)
	{
		expected = "soreimes happy, soreimes sad";
		auto result = FindAndReplace(source, "met", "re");
		BOOST_CHECK_EQUAL_COLLECTIONS(expected.begin(), expected.end(), result.begin(), result.end());
	}

	BOOST_FIXTURE_TEST_CASE(replace_existed_to_moreSize, Fixture)
	{
		expected = "soremmimes happy, soremmimes sad";
		auto result = FindAndReplace(source, "met", "remm");
		BOOST_CHECK_EQUAL_COLLECTIONS(expected.begin(), expected.end(), result.begin(), result.end());
	}

	BOOST_FIXTURE_TEST_CASE(replace_in_empty, Fixture)
	{
		source = "";
		expected = source;
		auto result = FindAndReplace(source, "met", "remm");
		BOOST_CHECK_EQUAL_COLLECTIONS(expected.begin(), expected.end(), result.begin(), result.end());
	}


	BOOST_FIXTURE_TEST_CASE(replace_1231234_in_12312312345, Fixture)
	{
		source = "12312312345";
		expected = "123paste5";
		auto result = FindAndReplace(source,"1231234", "paste");
		BOOST_CHECK_EQUAL_COLLECTIONS(expected.begin(), expected.end(), result.begin(), result.end());
	}

	BOOST_FIXTURE_TEST_CASE(replace_ma_in_mama, Fixture)
	{
		source = "mamampapa";
		expected = "pastepastempapa";
		auto result = FindAndReplace(source, "ma", "paste");
		BOOST_CHECK_EQUAL_COLLECTIONS(expected.begin(), expected.end(), result.begin(), result.end());
	}

BOOST_AUTO_TEST_SUITE_END()
