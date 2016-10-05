#include "stdafx.h"
#include "../MyList/MyList.h"

struct ListItem
{
	ListItem(int value = 0) : value(value)
	{}
	int value;
};

struct EmptyListItemList
{
	CMyList<ListItem> list;
};

BOOST_FIXTURE_TEST_SUITE(MyListTest, EmptyListItemList)
	BOOST_AUTO_TEST_SUITE(by_default)
		BOOST_AUTO_TEST_CASE(has_0_size)
		{
			BOOST_CHECK_EQUAL(list.GetSize(), 0u);
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(after_appending_an_item)
		BOOST_AUTO_TEST_CASE(increases_its_size_and_capacity)
		{
			
		}
		BOOST_AUTO_TEST_CASE(it_becomes_available_at_the_back)
		{
			
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()