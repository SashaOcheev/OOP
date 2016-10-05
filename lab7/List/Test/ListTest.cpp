#include "stdafx.h"
#include "../List/List.h"
#include <string>


BOOST_AUTO_TEST_SUITE(List_Test)

	BOOST_AUTO_TEST_CASE(is_emty_new_list)
	{
		CList<int> list;
		BOOST_CHECK_EQUAL(list.size(), 0);
		BOOST_CHECK(!list.empty());
	}


BOOST_AUTO_TEST_SUITE_END()

/*BOOST_AUTO_TEST_SUITE(List_Test)

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
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()*/