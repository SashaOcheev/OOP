// Test-Driven-Development.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <boost/test/output/compiler_log_formatter.hpp>
#include "../PrimeNumbers/PrimeNumbers.h"

typedef std::set<int> intSet;

BOOST_AUTO_TEST_SUITE(PrimeNumbersTest)

	BOOST_AUTO_TEST_CASE(LessThan2)
	{
		intSet emptySet;
		BOOST_CHECK(GeneratePrimeNumbersSet(-1) == emptySet);
		BOOST_CHECK(GeneratePrimeNumbersSet(0) == emptySet);
		BOOST_CHECK(GeneratePrimeNumbersSet(1) == emptySet);
	}

	BOOST_AUTO_TEST_CASE(MoreOrEqual2)
	{
		BOOST_CHECK(GeneratePrimeNumbersSet(2) == intSet({ 2 }));
		BOOST_CHECK(GeneratePrimeNumbersSet(3) == intSet({ 2, 3 }));
		BOOST_CHECK(GeneratePrimeNumbersSet(10) == intSet({ 2, 3, 5, 7 }));
		BOOST_CHECK(GeneratePrimeNumbersSet(17) == intSet({ 2, 3, 5, 7, 11, 13, 15 }));
	}

	BOOST_AUTO_TEST_CASE(IsCountEqual)
	{
		BOOST_CHECK_EQUAL(GeneratePrimeNumbersSet(100'000'000), 5'761'455);
	}

BOOST_AUTO_TEST_SUITE_END()