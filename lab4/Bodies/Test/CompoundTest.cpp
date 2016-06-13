
#include "stdafx.h"

#include <boost/test/output/compiler_log_formatter.hpp>
#include "../Bodies/program.h"


struct Compound_
{
	CCompound compound;

	Compound_() : compound()
	{}
};

BOOST_FIXTURE_TEST_SUITE(Compound, Compound_)

	BOOST_AUTO_TEST_CASE(is_a_body)
	{
		BOOST_CHECK(static_cast<const CBody*>(&compound));
	}
	BOOST_AUTO_TEST_CASE(has_a_null_mass)
	{
		BOOST_CHECK_EQUAL(static_cast<const CBody &>(compound).GetMass(), 0);
	}
	BOOST_AUTO_TEST_CASE(has_a_null_volume)
	{
		BOOST_CHECK_EQUAL(static_cast<const CBody &>(compound).GetVolume(), 0);
	}
	BOOST_AUTO_TEST_CASE(has_a_null_density)
	{
		BOOST_CHECK_EQUAL(static_cast<const CBody &>(compound).GetDensity(), 0);
	}
	BOOST_AUTO_TEST_CASE(can_add_shape)
	{
		auto cone = CCone(15, 10, 40);
		compound.AddBody(std::make_shared<CCone>(CCone(8.8, 42.8, 5.4)));
	}

	struct One_body_compound_ : Compound_
	{
		const double expectedDensity = 8.8;
		const double expectedVolume = 10'358.81116;
		const char *const expectedString = R"(Compound:
	density = 8.8
	volume = 10358.81116
	mass = 91157.53817
Cone:
	density = 8.8
	volume = 10358.81116
	mass = 91157.53817
	radius = 42.8
	height = 5.4
)";
		One_body_compound_()
		{
			compound.AddBody(std::make_shared<CCone>(CCone(8.8, 42.8, 5.4)));
		}
	};

	BOOST_FIXTURE_TEST_SUITE(One_body_compound, One_body_compound_)
		BOOST_AUTO_TEST_CASE(has_a_density)
		{
			BOOST_CHECK_CLOSE_FRACTION(compound.GetDensity(), expectedDensity, 1e-7);
		}
		BOOST_AUTO_TEST_CASE(has_a_volume)
		{
			BOOST_CHECK_CLOSE_FRACTION(compound.GetVolume(), expectedVolume, 1e-7);
		}
		BOOST_AUTO_TEST_CASE(has_a_mass)
		{
			BOOST_CHECK_CLOSE_FRACTION(compound.GetMass(), expectedVolume * expectedDensity, 1e-7);
		}
		BOOST_AUTO_TEST_CASE(can_be_converted_to_string)
		{
			BOOST_CHECK_EQUAL(compound.ToString(), expectedString);
		}
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()