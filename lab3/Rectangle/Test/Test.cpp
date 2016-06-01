// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include "stdafx.h"
#include <boost/test/output/compiler_log_formatter.hpp>
#include "../Rectangle/CRectangle.h"
#include "../Rectangle/RectangleFromFile.h"


bool IsRectangleFieldsEqualToExpected(const CRectangle &rect, int expectedLeft, int expectedTop, int expectedWidth, int expectedHeigth)
{
	return rect.GetLeft() == expectedLeft && rect.GetTop() == expectedTop
		&& rect.GetWidth == expectedWidth && rect.GetHeight() == expectedHeigth;
}

bool IsRectangleRightBottomDotEqualToExpected(const CRectangle &rect, int expectedRight, int expectedBottom)
{
	return rect.GetRight() == expectedRight && rect.GetBottom() == expectedBottom;
}

struct RectangleFixture
{
	CRectangle rect;
};


BOOST_FIXTURE_TEST_SUITE(Rectangle, RectangleFixture)
	
	//изначально все поля равны 0
	BOOST_AUTO_TEST_CASE(is_fields_0_by_default)
	{
		BOOST_CHECK(IsRectangleFieldsEqualToExpected(rect, 0, 0, 0, 0));
	}

	//возможность задать поля, с неотрицательными шириной и высотой
	BOOST_AUTO_TEST_CASE(can_set_fields)
	{
		rect.SetLeft(-10);
		rect.SetTop(10);
		rect.SetWidth(5);
		rect.SetHeight(0);
		BOOST_CHECK(IsRectangleFieldsEqualToExpected(rect, -10, 10, 5, 0));
	}

	struct set_rect_fields_ : RectangleFixture
	{
		set_rect_fields_()
		{
			rect.SetLeft(-10);
			rect.SetTop(10);
			rect.SetWidth(5);
			rect.SetHeight(8);
		}
	};

	BOOST_FIXTURE_TEST_SUITE(set_rect_fields, set_rect_fields_)

		//когда задаем отрицательную ширину или высоту они обнулются
		BOOST_AUTO_TEST_CASE(is_heigth_0_when_was_try_set_less_than_0)
		{
			rect.SetHeight(-1);
			BOOST_CHECK(IsRectangleFieldsEqualToExpected(rect, -10, 10, 5, 0));
		}

		BOOST_AUTO_TEST_CASE(is_width_0_when_was_try_set_less_than_0)
		{
			rect.SetWidth(-5);
			BOOST_CHECK(IsRectangleFieldsEqualToExpected(rect, -10, 10, 0, 8));
		}

		//правильность вычисления правого нижнего угла
		{
			BOOST_CHECK(IsRectangleRightBottomDotEqualToExpected(rect, -5, 18));
		}

		//когда меняем высоту и ширину, меняется левый нижний угол
		BOOST_AUTO_TEST_CASE(left_changes_when_width_changes)
		{		
			rect.SetWidth(10);
			BOOST_CHECK(IsRectangleFieldsEqualToExpected(rect, -10, 10, 10, 8));
			BOOST_CHECK(IsRectangleRightBottomDotEqualToExpected(rect, 0, 18));
		}

		BOOST_AUTO_TEST_CASE(bottom_changes_height_changes)
		{
			rect.SetHeight(5);
			BOOST_CHECK(IsRectangleFieldsEqualToExpected(rect, -10, 10, 5, 5));
			BOOST_CHECK(IsRectangleRightBottomDotEqualToExpected(rect, 0, 15));
		}

		//можно задать правый нижний угол, больший левого верхнего
		BOOST_AUTO_TEST_CASE(can_set_right_more_than_left)
		{
			rect.SetRight(-9);
			BOOST_CHECK(IsRectangleFieldsEqualToExpected(rect, -10, 10, 1, 8));
			BOOST_CHECK(IsRectangleRightBottomDotEqualToExpected(rect, -9, 18));
		}

		BOOST_AUTO_TEST_CASE(can_set_bottom_more_than_top)
		{
			rect.SetBottom(12);
			BOOST_CHECK(IsRectangleFieldsEqualToExpected(rect, -10, 10, 5, 2));
			BOOST_CHECK(IsRectangleRightBottomDotEqualToExpected(rect, -5, 12));
		}

		//когда задаем правый нижний угол меньше левого верхнего, высота и ширина обнуляются
		{
			SetRectangleFields(rect, -10, 10, 0, 0);
		}

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()