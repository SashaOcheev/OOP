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

BOOST_AUTO_TEST_SUITE(IsEqualDoubleVectors_test)
	BOOST_AUTO_TEST_CASE(is_equal_double)
	{
		BOOST_CHECK(IsEqualDouble(3.0, 3.0));
		BOOST_CHECK(!IsEqualDouble(3.0, 2.0));
	}

	BOOST_AUTO_TEST_CASE(is_equal_vectors)
	{
		BOOST_CHECK(IsEqualDoubleVectors({ 1, 2, 3 }, { 1, 2, 3 }));
		BOOST_CHECK(IsEqualDoubleVectors({}, {}));
		BOOST_CHECK(!IsEqualDoubleVectors({ 1, 2, 3 }, { 1, 3, 2 }));
		BOOST_CHECK(!IsEqualDoubleVectors({ 1, 2, 3 }, { 1, 2 }));
		BOOST_CHECK(!IsEqualDoubleVectors({}, { 1, 2 }));
	}
BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(ProcessVector_test)
	BOOST_AUTO_TEST_CASE(without_divided_by_3)
	{
		std::vector<double> numbers = { 1, 2, 2, 4, 5 };
		ProcessVector(numbers);
		BOOST_CHECK(IsEqualDoubleVectors(numbers, { 1, 2, 2, 4, 5 }));
	}

	BOOST_AUTO_TEST_CASE(without_divided_by_2)
	{
		std::vector<double> numbers = { 1, 3, 9, 7, 5, 15 };
		ProcessVector(numbers);
		BOOST_CHECK(IsEqualDoubleVectors(numbers, { 1, 0, 0, 7, 5, 0 }));
	}

	BOOST_AUTO_TEST_CASE(normal_test)
	{
		std::vector<double> numbers = { 1, 2, 3, 4, 5, 6 };
		ProcessVector(numbers);
		BOOST_CHECK(IsEqualDoubleVectors(numbers, { 1, 2, 12, 4, 5, 24 }));
	}
BOOST_AUTO_TEST_SUITE_END()