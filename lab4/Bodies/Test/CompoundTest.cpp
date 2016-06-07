
#include "stdafx.h"

#include <boost/test/output/compiler_log_formatter.hpp>
#include "../Bodies/program.h"

struct Cone_
{
	const double expectedRadius = 42.8;
	const double expectedDensity = 8.8;
	const double expectedVolume = 10'358.81116;
	const double expectedHeight = 5.4;
	CCone cone;
	Cone_()
		: cone(expectedDensity, expectedRadius, expectedHeight)
	{}
};

struct Compound_
{
	Cone_ cone;
	const double expectedVolume = 10'358.81116;
	const double expectedDensity = 8.8;
	CCompound compound;
	Compound_()
		: compound(std::make_unique<CCone>(cone.cone))
	{
	}
};

//BOOST_FIXTURE_TEST_SUITE(Compound, Compound_)
//
//	BOOST_AUTO_TEST_CASE(is_a_body)
//	{
//		BOOST_CHECK(static_cast<const CBody*>(&compound));
//	}
//
//	BOOST_AUTO_TEST_CASE(has_a_density)
//	{
//		BOOST_CHECK_EQUAL(static_cast<const CBody &>(compound).GetDensity(), expectedDensity);
//	}
//	// טלווע מבתול
//	BOOST_AUTO_TEST_CASE(has_a_volume)
//	{
//		BOOST_CHECK_CLOSE_FRACTION(static_cast<const CBody &>(compound).GetVolume(), expectedVolume, 1e-7);
//	}
//	// טלווע לאססף
//	BOOST_AUTO_TEST_CASE(has_a_mass)
//	{
//		BOOST_CHECK_CLOSE_FRACTION(static_cast<const CBody &>(compound).GetMass(), expectedVolume * expectedDensity, 1e-7);
//	}
//
//BOOST_AUTO_TEST_SUITE_END()