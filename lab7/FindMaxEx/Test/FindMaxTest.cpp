#include "stdafx.h"
#include "../FindMaxEx/FindMaxEx.h"
#include <string>


BOOST_AUTO_TEST_SUITE(Findmax_Test)

	BOOST_AUTO_TEST_CASE(return_false_and_does_not_change_input_max_value_when_vector_is_empty)
	{
		std::vector<int> arr;
		int maxValue = 0;
		BOOST_CHECK(!FindMax(arr, maxValue));
		BOOST_CHECK_EQUAL(maxValue, 0);
	}

	BOOST_AUTO_TEST_CASE(can_find_max_int)
	{
		std::vector<int> arr = { 1, 2, 3, 5, 4 };
		int maxValue;
		BOOST_CHECK(FindMax(arr, maxValue));
		BOOST_CHECK_EQUAL(maxValue, 5);
	}

	BOOST_AUTO_TEST_CASE(can_find_max_double)
	{
		std::vector<double> arr = { 1.1, 2.1, 3.1, 5.1, 4.1 };
		double maxValue;
		BOOST_CHECK(FindMax(arr, maxValue));
		BOOST_CHECK_EQUAL(maxValue, 5.1);
	}

	BOOST_AUTO_TEST_CASE(can_find_max_string)
	{
		std::vector<std::string> arr = { "ab", "ewrea", "aa", "ewree", "ewree", "aaa" };
		std::string maxValue;
		BOOST_CHECK(FindMax(arr, maxValue));
		BOOST_CHECK_EQUAL(maxValue, "ewree");
	}

	struct Athlete
	{
		std::string name;
		int height;
		int weight;
		Athlete(const std::string & name, int height, int weight)
			: name(name)
			, height(height)
			, weight(weight)
		{
		};
	};

	struct Athletes
	{
		std::vector<Athlete> arr;
		Athletes()
		{
			arr =
			{
				Athlete("a", 1, 5),
				Athlete("b", 2, 4),
				Athlete("c", 3, 3),
				Athlete("d", 4, 2),
				Athlete("e", 5, 1),
			};
		}
	};

	BOOST_FIXTURE_TEST_SUITE(Can_Find_Max_Struct_Element_Using_Binary_Predicate, Athletes)
		BOOST_AUTO_TEST_CASE(can_find_max_weight_athlete)	
		{
			Athlete maxValue("f", 6, 6);
			BOOST_CHECK(FindMax(arr, maxValue, [](const Athlete & athlete1, const Athlete & athlete2)
			{
				return athlete1.weight < athlete2.weight;
			}));
			BOOST_CHECK_EQUAL(maxValue.name, arr[0].name);
		}
		BOOST_AUTO_TEST_CASE(can_find_max_height_athlete)
		{
			Athlete maxValue("f", 6, 6);
			BOOST_CHECK(FindMax(arr, maxValue, [](const Athlete & athlete1, const Athlete & athlete2)
			{
				return athlete1.height < athlete2.height;
			}));
			BOOST_CHECK_EQUAL(maxValue.name, arr[4].name);
		}
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()