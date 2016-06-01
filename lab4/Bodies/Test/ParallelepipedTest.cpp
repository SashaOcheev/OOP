
#include "stdafx.h"

#include <boost/test/output/compiler_log_formatter.hpp>
#include "../Bodies/program.h"


struct Parallelepiped_
{
	const double expectedWidth = 42.8;
	const double expectedHeight = 5.4;
	const double expectedDepth = 12.6;
	const double expectedDensity = 8.8;
	const double expectedVolume = 31'076.43;
	const CParallelepiped parallelepiped;
	Parallelepiped_()
		: parallelepiped(expectedDensity, expectedWidth, expectedHeight, expectedDepth)
	{}
};

// Цилиндр
BOOST_FIXTURE_TEST_SUITE(Parallelepiped, Parallelepiped_)
	// является объемным телом
	BOOST_AUTO_TEST_CASE(is_a_body)
	{
		BOOST_CHECK(static_cast<const CBody*>(&parallelepiped));
	}
	// имеет ширину
	BOOST_AUTO_TEST_CASE(has_a_width)
	{
		BOOST_CHECK_EQUAL(parallelepiped.GetWidth(), expectedWidth);
	}
	// имеет высоту
	BOOST_AUTO_TEST_CASE(has_a_heigth)
	{
		BOOST_CHECK_EQUAL(parallelepiped.GetHeight(), expectedHeight);
	}
	// имеет глубину
	BOOST_AUTO_TEST_CASE(has_a_depth)
	{
		BOOST_CHECK_EQUAL(parallelepiped.GetDepth(), expectedDepth);
	}
	// имеет плотность
	BOOST_AUTO_TEST_CASE(has_a_density)
	{
		BOOST_CHECK_EQUAL(static_cast<const CBody &>(parallelepiped).GetDensity(), expectedDensity);
	}
	// имеет объем
	BOOST_AUTO_TEST_CASE(has_a_volume)
	{
		BOOST_CHECK_CLOSE_FRACTION(static_cast<const CBody &>(parallelepiped).GetVolume(), expectedVolume, 1e-7);
	}
	// имеет массу
	BOOST_AUTO_TEST_CASE(has_a_mass)
	{
		BOOST_CHECK_CLOSE_FRACTION(static_cast<const CBody &>(parallelepiped).GetMass(), expectedVolume * expectedDensity, 1e-7);
	}
	// имеет строковое представление
	BOOST_AUTO_TEST_CASE(can_be_converted_to_string)
	{
		const auto expectedString = R"(Parallelepiped:
		density = 8.8
		volume = 31076.43
		mass = 2890031.581
		radius = 42.8
		height = 5.8
	)";
		BOOST_CHECK_EQUAL(static_cast<const CBody &>(parallelepiped).ToString(), expectedString);
	}
BOOST_AUTO_TEST_SUITE_END()