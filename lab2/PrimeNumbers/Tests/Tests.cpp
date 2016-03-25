// Test-Driven-Development.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <boost/test/output/compiler_log_formatter.hpp>
#include "../PrimeNumbers/PrimeNumbers.h"



typedef std::set<int> IntSet;

BOOST_AUTO_TEST_SUITE(Prime_numbers_test)

	BOOST_AUTO_TEST_CASE(less_than_2)
	{
		IntSet emptySet;
		BOOST_CHECK(GeneratePrimeNumbersSet(-1) == emptySet);
		BOOST_CHECK(GeneratePrimeNumbersSet(0) == emptySet);
		BOOST_CHECK(GeneratePrimeNumbersSet(1) == emptySet);
	}

	BOOST_AUTO_TEST_CASE(more_or_equal_2)
	{
		BOOST_CHECK(GeneratePrimeNumbersSet(2) == IntSet({ 2 }));
		BOOST_CHECK(GeneratePrimeNumbersSet(3) == IntSet({ 2, 3 }));
		BOOST_CHECK(GeneratePrimeNumbersSet(10) == IntSet({ 2, 3, 5, 7 }));
		BOOST_CHECK(GeneratePrimeNumbersSet(17) == IntSet({ 2, 3, 5, 7, 11, 13, 17 }));
	}

	BOOST_AUTO_TEST_CASE(is_count_equal)
	{
		BOOST_CHECK_EQUAL(GeneratePrimeNumbersSet(100'000'000).size(), 5'761'455);
	}

BOOST_AUTO_TEST_SUITE_END()