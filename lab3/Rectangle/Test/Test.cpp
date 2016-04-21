// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include "stdafx.h"
#include <boost/test/output/compiler_log_formatter.hpp>
#include "../Rectangle/CRectangle.h"
#include "../Rectangle/RectangleFromFile.h"


BOOST_AUTO_TEST_SUITE(CRectangle_test)

	struct Fixture
	{
		CRectangle rect;
		CRectangle rect2;
	};

	BOOST_FIXTURE_TEST_CASE(SetLeft_test, Fixture)
	{
		rect.SetLeft(-10);
		BOOST_CHECK_EQUAL(rect.GetLeft(), -10);

		rect.SetLeft(0);
		BOOST_CHECK_EQUAL(rect.GetLeft(), 0);

		rect.SetLeft(10);
		BOOST_CHECK_EQUAL(rect.GetLeft(), 10);
	}

	BOOST_FIXTURE_TEST_CASE(SetTop_test, Fixture)
	{
		rect.SetTop(-10);
		BOOST_CHECK_EQUAL(rect.GetTop(), -10);

		rect.SetTop(0);
		BOOST_CHECK_EQUAL(rect.GetTop(), 0);

		rect.SetTop(10);
		BOOST_CHECK_EQUAL(rect.GetTop(), 10);
	}

	BOOST_FIXTURE_TEST_CASE(SetWidth_test, Fixture)
	{
		rect.Reset(1, 1, 1, 1);
		rect.SetWidth(-10);
		BOOST_CHECK_EQUAL(rect.GetWidth(), 0);
		BOOST_CHECK_EQUAL(rect.GetRight(), 1);

		rect.SetWidth(0);
		BOOST_CHECK_EQUAL(rect.GetWidth(), 0);
		BOOST_CHECK_EQUAL(rect.GetRight(), 1);

		rect.SetWidth(10);
		BOOST_CHECK_EQUAL(rect.GetWidth(), 10);
		BOOST_CHECK_EQUAL(rect.GetRight(), 11);

		rect.SetWidth(-10);
		BOOST_CHECK_EQUAL(rect.GetWidth(), 0);
		BOOST_CHECK_EQUAL(rect.GetRight(), 1);
	}

	BOOST_FIXTURE_TEST_CASE(SetHeight_test, Fixture)
	{
		rect.Reset(1, 1, 1, 1);
		rect.SetHeight(-10);
		BOOST_CHECK_EQUAL(rect.GetHeight(), 0);
		BOOST_CHECK_EQUAL(rect.GetBottom(), 1);

		rect.SetHeight(0);
		BOOST_CHECK_EQUAL(rect.GetHeight(), 0);
		BOOST_CHECK_EQUAL(rect.GetBottom(), 1);

		rect.SetHeight(10);
		BOOST_CHECK_EQUAL(rect.GetHeight(), 10);
		BOOST_CHECK_EQUAL(rect.GetBottom(), 11);

		rect.SetHeight(-10);
		BOOST_CHECK_EQUAL(rect.GetHeight(), 0);
		BOOST_CHECK_EQUAL(rect.GetBottom(), 1);
	}


	BOOST_FIXTURE_TEST_CASE(SetRight_test, Fixture)
	{
		rect.SetLeft(-2);
		rect.SetWidth(10);

		rect.SetRight(-10);
		BOOST_CHECK_EQUAL(rect.GetWidth(), 0);
		BOOST_CHECK_EQUAL(rect.GetRight(), -2);

		rect.SetRight(5);
		BOOST_CHECK_EQUAL(rect.GetWidth(), 7);
		BOOST_CHECK_EQUAL(rect.GetRight(), 5);

		rect.SetRight(-2);
		BOOST_CHECK_EQUAL(rect.GetWidth(), 0);
		BOOST_CHECK_EQUAL(rect.GetRight(), -2);
	}


	BOOST_FIXTURE_TEST_CASE(SetBottom_test, Fixture)
	{
		rect.SetTop(-2);
		rect.SetHeight(10);

		rect.SetBottom(-10);
		BOOST_CHECK_EQUAL(rect.GetHeight(), 0);
		BOOST_CHECK_EQUAL(rect.GetBottom(), -2);

		rect.SetBottom(5);
		BOOST_CHECK_EQUAL(rect.GetHeight(), 7);
		BOOST_CHECK_EQUAL(rect.GetBottom(), 5);

		rect.SetBottom(-2);
		BOOST_CHECK_EQUAL(rect.GetHeight(), 0);
		BOOST_CHECK_EQUAL(rect.GetBottom(), -2);
	}

	BOOST_FIXTURE_TEST_CASE(Perimeter_test, Fixture)
	{
		rect.Reset(-5, -5, 10, 15);
		BOOST_CHECK_EQUAL(rect.Perimeter(), 50);

		rect.Reset(-5, -5, 0, 15);
		BOOST_CHECK_EQUAL(rect.Perimeter(), 15);

		rect.Reset(-5, -5, 10, 0);
		BOOST_CHECK_EQUAL(rect.Perimeter(), 10);
		
		rect.Reset(-5, -5, 0, 0);
		BOOST_CHECK_EQUAL(rect.Perimeter(), 0);
	}

	BOOST_FIXTURE_TEST_CASE(Area_test, Fixture)
	{
		rect.Reset(-5, -5, 10, 15);
		BOOST_CHECK_EQUAL(rect.Area(), 150);

		rect.Reset(-5, -5, 0, 15);
		BOOST_CHECK_EQUAL(rect.Area(), 0);

		rect.Reset(-5, -5, 10, 0);
		BOOST_CHECK_EQUAL(rect.Area(), 0);

		rect.Reset(-5, -5, 0, 0);
		BOOST_CHECK_EQUAL(rect.Area(), 0);
	}


	BOOST_FIXTURE_TEST_CASE(Move_test, Fixture)
	{
		rect.Reset(-5, -6, 10, 15);
		rect.Move(-4, -5);
		BOOST_CHECK_EQUAL(rect.GetLeft(), -9);
		BOOST_CHECK_EQUAL(rect.GetTop(), -11);

		rect.Move(9, 20);
		BOOST_CHECK_EQUAL(rect.GetLeft(), 0);
		BOOST_CHECK_EQUAL(rect.GetTop(), 9);

		rect.Move(0, 0);
		BOOST_CHECK_EQUAL(rect.GetLeft(), 0);
		BOOST_CHECK_EQUAL(rect.GetTop(), 9);
	}


	BOOST_FIXTURE_TEST_CASE(Scale_test, Fixture)
	{
		rect.Reset(-5, -6, 1, 2);
		rect.Scale(-1, 2);
		BOOST_CHECK_EQUAL(rect.GetWidth(), 1);
		BOOST_CHECK_EQUAL(rect.GetHeight(), 2);

		rect.Scale(2, -1);
		BOOST_CHECK_EQUAL(rect.GetWidth(), 1);
		BOOST_CHECK_EQUAL(rect.GetHeight(), 2);

		rect.Scale(2, 3);
		BOOST_CHECK_EQUAL(rect.GetWidth(), 2);
		BOOST_CHECK_EQUAL(rect.GetHeight(), 6);

		rect.Scale(1, 1);
		BOOST_CHECK_EQUAL(rect.GetWidth(), 2);
		BOOST_CHECK_EQUAL(rect.GetHeight(), 6);

		rect.Scale(0, 0);
		BOOST_CHECK_EQUAL(rect.GetWidth(), 0);
		BOOST_CHECK_EQUAL(rect.GetHeight(), 0);
	}

	BOOST_FIXTURE_TEST_CASE(doesnt_intersects_test, Fixture)
	{
		rect.Reset(-5, -3, 10, 15);
		rect2.Reset(6, 13, 20, 30);
		auto isIntersects = rect.Intersect(rect2);
		BOOST_CHECK(!isIntersects);
		BOOST_CHECK_EQUAL(rect.GetLeft(), -5);
		BOOST_CHECK_EQUAL(rect.GetTop(), -3);
		BOOST_CHECK_EQUAL(rect.GetWidth(), 0);
		BOOST_CHECK_EQUAL(rect.GetHeight(), 0);
	}

	BOOST_FIXTURE_TEST_CASE(intersects_test, Fixture)
	{
		rect.Reset(-5, -3, 10, 15);
		rect2.Reset(0, 6, 20, 30);
		auto isIntersects = rect.Intersect(rect2);
		BOOST_CHECK(isIntersects);
		BOOST_CHECK_EQUAL(rect.GetLeft(), 0);
		BOOST_CHECK_EQUAL(rect.GetTop(), 6);
		BOOST_CHECK_EQUAL(rect.GetWidth(), 5);
		BOOST_CHECK_EQUAL(rect.GetHeight(), 6);
	}

	BOOST_FIXTURE_TEST_CASE(one_rectangle_enclude_other_test, Fixture)
	{
		rect.Reset(0, 0, 10, 10);
		rect2.Reset(2, 0, 4, 5);
		auto isIntersects = rect2.Intersect(rect);
		BOOST_CHECK(isIntersects);
		BOOST_CHECK_EQUAL(rect2.GetLeft(), 2);
		BOOST_CHECK_EQUAL(rect2.GetTop(), 0);
		BOOST_CHECK_EQUAL(rect2.GetWidth(), 4);
		BOOST_CHECK_EQUAL(rect2.GetHeight(), 5);
	}

BOOST_AUTO_TEST_SUITE_END()