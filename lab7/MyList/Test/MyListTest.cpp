#include "stdafx.h"
#include "../MyList/MyList.h"
#include <iostream>

struct EmptyStringList
{
	CMyList<std::string> list;
};

template<typename T>
void VerifyList(CMyList<T> & list, std::vector<T> & expected)
{
	size_t counter = 0;
	for (auto it = list.cbegin(); it != list.cend(); ++it)
	{
		BOOST_CHECK_EQUAL(*it, expected[counter]);
		counter++;
	}
}

BOOST_FIXTURE_TEST_SUITE(CMyList_, EmptyStringList)

	BOOST_AUTO_TEST_SUITE(after_created)

		BOOST_AUTO_TEST_CASE(is_empty)
		{
			BOOST_CHECK(list.IsEmpty());
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(after_push_back)

		BOOST_AUTO_TEST_CASE(size_increases_by_1)
		{
			auto oldSize = list.GetSize();
			list.PushBack("hello");
			BOOST_CHECK_EQUAL(list.GetSize(), oldSize + 1);
			list.PushBack("hello");
			BOOST_CHECK_EQUAL(list.GetSize(), oldSize + 2);
		}

		BOOST_AUTO_TEST_CASE(accessible_via_GetBackElement_and_GetFrontElement_method)
		{
			list.PushBack("hello");
			BOOST_CHECK_EQUAL(list.GetBackElement(), "hello");
			BOOST_CHECK_EQUAL(list.GetFrontElement(), "hello");
			list.PushBack("goodbye");
			BOOST_CHECK_EQUAL(list.GetBackElement(), "goodbye");
			BOOST_CHECK_EQUAL(list.GetFrontElement(), "hello");
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(after_push_front)

		BOOST_AUTO_TEST_CASE(size_increases_by_1)
		{
			auto oldSize = list.GetSize();
			list.PushFront("hello");
			BOOST_CHECK_EQUAL(list.GetSize(), oldSize + 1);
			list.PushFront("hello");
			BOOST_CHECK_EQUAL(list.GetSize(), oldSize + 2);
		}

		BOOST_AUTO_TEST_CASE(accessible_via_GetBackElement_and_GetFrontElement_method)
		{
			list.PushFront("hello");
			BOOST_CHECK_EQUAL(list.GetFrontElement(), "hello");
			BOOST_CHECK_EQUAL(list.GetBackElement(), "hello");
			list.PushFront("goodbye");
			BOOST_CHECK_EQUAL(list.GetFrontElement(), "goodbye");
			BOOST_CHECK_EQUAL(list.GetBackElement(), "hello");
		}

		BOOST_AUTO_TEST_CASE(accessible_via_iterator_to_first_element)
		{
			list.PushBack("hello");
			auto it = list.begin();
			BOOST_CHECK_EQUAL(addressof(*it), addressof(list.GetBackElement()));
		}

	BOOST_AUTO_TEST_SUITE_END()

	struct when_not_empty : EmptyStringList
	{
		when_not_empty()
		{
			list.PushBack("hello");
			list.PushBack("ho-ho-ho");
			list.PushBack("goodbye");
		}

		std::vector<std::string> expectedStrings = { "hello", "ho-ho-ho", "goodbye" };
	};

	BOOST_FIXTURE_TEST_SUITE(when_not_empty_, when_not_empty)

		BOOST_AUTO_TEST_CASE(can_be_cleared)
		{
			BOOST_CHECK(!list.IsEmpty());
			list.Clear();
			BOOST_CHECK(list.IsEmpty());
		}

		BOOST_AUTO_TEST_CASE(has_iterators_and_const_iterators_at_begin_and_end)
		{
			size_t counter = 0;
			for (auto it = list.begin(); it != list.end(); ++it)
			{
				BOOST_CHECK_EQUAL(*it, expectedStrings[counter]);
				counter++;
			}

			counter = 0;
			for (auto it = list.cbegin(); it != list.cend(); ++it)
			{
				BOOST_CHECK_EQUAL(*it, expectedStrings[counter]);
				counter++;
			}
		}

		BOOST_AUTO_TEST_CASE(has_reverse_iterators_and_const_revers_iterators_at_begin_and_end)
		{
			size_t counter = expectedStrings.size() - 1;
			for (auto it = list.rbegin(); it != list.rend(); ++it)
			{
				BOOST_CHECK_EQUAL(*it, expectedStrings[counter]);
				counter--;
			}
		}

		BOOST_AUTO_TEST_CASE(can_acces_to_elements_from_range_based_for)
		{
			size_t counter = 0;
			for (auto str : list)
			{
				BOOST_CHECK_EQUAL(str, expectedStrings[counter]);
				counter++;
			}
		}

		BOOST_AUTO_TEST_CASE(can_insert_element_at_iterator_pos)
		{
			auto it = ++list.begin();
			list.Insert(it, "20");
			BOOST_CHECK_EQUAL(*++list.begin(), "20");

			list.Insert(list.begin(), "11");
			BOOST_CHECK_EQUAL(*list.begin(), "11");

			list.Insert(list.end(), "30");

			std::vector<std::string> expectedStrings = {"11", "hello", "20", "ho-ho-ho", "goodbye", "30"};
			size_t i = 0;
			for (auto str : list)
			{
				BOOST_CHECK_EQUAL(str, expectedStrings[i]);
				i++;
			}
			
		}

		BOOST_AUTO_TEST_CASE(can_erase_element_at_iterator_pos)
		{
			auto it = ++list.begin();
			BOOST_CHECK_EQUAL(*it, "ho-ho-ho");
			list.Erase(it);
			BOOST_CHECK_EQUAL(*++list.begin(), "goodbye");

			list.Erase(list.begin());
			BOOST_CHECK_EQUAL(*list.begin(), "goodbye");

			list.Erase(list.begin());
			BOOST_CHECK(list.IsEmpty());
		}

		BOOST_AUTO_TEST_CASE(has_copy_constructor)
		{
			CMyList<std::string> list1(list);
			VerifyList(list, expectedStrings);
			VerifyList(list1, expectedStrings);
		}

		BOOST_AUTO_TEST_CASE(has_copy_assignment_operator)
		{
			CMyList<std::string> list1;
			list1 = list;
			VerifyList(list, expectedStrings);
			VerifyList(list1, expectedStrings);
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_CASE(should_not_cause_stack_oveflow_on_destruction)
	{
		{
			CMyList<std::string> list;
			for (int i = 0; i < 100000; ++i)
			{
				list.PushBack("123");
			}
			std::cout << "(list is filled, ";
		}
		std::cout << "and successfully destroyed)" << std::endl;
	}

BOOST_AUTO_TEST_SUITE_END()