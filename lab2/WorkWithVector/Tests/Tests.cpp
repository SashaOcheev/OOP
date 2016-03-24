// Test-Driven-Development.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <boost/test/output/compiler_log_formatter.hpp>
#include "../WorkWithVector/WorkWithVector.h"


bool IsEqualDoubleVectors(std::vector<double> const& vec1, std::vector<double> const& vec2, double precision = 0.001)
{
	return std::equal(vec1.cbegin(), vec1.cend(), vec2.cbegin(), vec2.cend(),
		std::bind(IsEqualDouble, std::placeholders::_1, std::placeholders::_2, precision));
}

BOOST_AUTO_TEST_SUITE(isEqDoubleVectors)
	BOOST_AUTO_TEST_CASE(isEqDouble)
	{
		BOOST_CHECK_EQUAL(IsEqualDouble(3.0, 3.0), true);
		BOOST_CHECK_EQUAL(IsEqualDouble(3.0, 2.0), false);
	}

	BOOST_AUTO_TEST_CASE(isEqVectors)
	{
		BOOST_CHECK_EQUAL(IsEqualDoubleVectors({ 1, 2, 3 }, { 1, 2, 3 }), true);
		BOOST_CHECK_EQUAL(IsEqualDoubleVectors({ 1, 2, 3 }, { 1, 3, 2 }), false);
		BOOST_CHECK_EQUAL(IsEqualDoubleVectors({ 1, 2, 3 }, { 1, 2 }), false);
		BOOST_CHECK_EQUAL(IsEqualDoubleVectors({ }, { 1, 2 }), false);
	}
BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(FooTest)
	BOOST_AUTO_TEST_CASE(WithoutDividedBy3)
	{
		std::vector<double> numbers = { 1, 2, 2, 4, 5 };
		ProcessVector(numbers);
		BOOST_CHECK(IsEqualDoubleVectors(numbers, { 1, 2, 2, 4, 5 }));
	}

	BOOST_AUTO_TEST_CASE(WithoutDividedBy2)
	{
		std::vector<double> numbers = { 1, 3, 9, 7, 5, 15 };
		ProcessVector(numbers);
		BOOST_CHECK(IsEqualDoubleVectors(numbers, { 1, 0, 0, 7, 5, 0 }));
	}

	BOOST_AUTO_TEST_CASE(NormalTest)
	{
		std::vector<double> numbers = { 1, 2, 3, 4, 5, 6 };
		ProcessVector(numbers);
		BOOST_CHECK(IsEqualDoubleVectors(numbers, { 1, 2, 12, 4, 5, 24 }));
	}
BOOST_AUTO_TEST_SUITE_END()