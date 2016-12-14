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
			list.PushBack("first");
			BOOST_CHECK_EQUAL(list.GetBackElement(), "first");
			BOOST_CHECK_EQUAL(list.GetFrontElement(), "first");
			list.PushBack("second");
			BOOST_CHECK_EQUAL(list.GetBackElement(), "second");
			BOOST_CHECK_EQUAL(list.GetFrontElement(), "first");
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(after_push_front)

		BOOST_AUTO_TEST_CASE(size_increases_by_1)
		{
			auto oldSize = list.GetSize();
			list.PushFront("first");
			BOOST_CHECK_EQUAL(list.GetSize(), oldSize + 1);
			list.PushFront("first");
			BOOST_CHECK_EQUAL(list.GetSize(), oldSize + 2);
		}

		BOOST_AUTO_TEST_CASE(accessible_via_GetBackElement_and_GetFrontElement_method)
		{
			list.PushFront("first");
			BOOST_CHECK_EQUAL(list.GetFrontElement(), "first");
			BOOST_CHECK_EQUAL(list.GetBackElement(), "first");
			list.PushFront("second");
			BOOST_CHECK_EQUAL(list.GetFrontElement(), "second");
			BOOST_CHECK_EQUAL(list.GetBackElement(), "first");
		}

		BOOST_AUTO_TEST_CASE(accessible_via_iterator_to_first_element)
		{
			list.PushBack("first");
			auto it = list.begin();
			BOOST_CHECK_EQUAL(addressof(*it), addressof(list.GetBackElement()));
		}

	BOOST_AUTO_TEST_SUITE_END()

	struct filled : EmptyStringList
	{
		filled()
		{
			list.PushBack("first");
			list.PushBack("second");
			list.PushBack("third");
		}

		std::vector<std::string> expectedStrings = { "first", "second", "third" };
	};

	BOOST_FIXTURE_TEST_SUITE(when_not_empty_, filled)

		BOOST_AUTO_TEST_CASE(empty_after_clearing)
		{
			BOOST_CHECK(!list.IsEmpty());
			list.Clear();
			BOOST_CHECK(list.IsEmpty());
		}

		BOOST_AUTO_TEST_CASE(has_iterators_at_begin_and_end)
		{
			size_t counter = 0;
			for (auto it = list.begin(); it != list.end(); ++it)
			{
				BOOST_CHECK_EQUAL(*it, expectedStrings[counter]);
				counter++;
			}
		}

		BOOST_AUTO_TEST_CASE(has_const_iterators_at_begin_and_end)
		{
			size_t counter = 0;
			for (auto it = list.cbegin(); it != list.cend(); ++it)
			{
				BOOST_CHECK_EQUAL(*it, expectedStrings[counter]);
				
				counter++;
			}
		}

		BOOST_AUTO_TEST_CASE(has_reverse_iterators)
		{
			size_t counter = expectedStrings.size() - 1;
			for (auto it = list.rbegin(); it != list.rend(); ++it)
			{
				BOOST_CHECK_EQUAL(*it, expectedStrings[counter]);
				counter--;
			}
		}

		BOOST_AUTO_TEST_CASE(has_const_reverse_iterators)
		{
			size_t counter = expectedStrings.size() - 1;
			for (auto it = list.crbegin(); it != list.crend(); ++it)
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
			list.Insert(it, "first insert");
			BOOST_CHECK_EQUAL(*++list.begin(), "first insert");

			list.Insert(list.begin(), "second insert");
			BOOST_CHECK_EQUAL(*list.begin(), "second insert");

			list.Insert(list.end(), "third insert");

			std::vector<std::string> expectedStrings = {"second insert", "first", "first insert", "second", "third", "third insert"};
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
			BOOST_CHECK_EQUAL(*it, "second");
			list.Erase(it);
			BOOST_CHECK_EQUAL(*++list.begin(), "third");

			list.Erase(list.begin());
			BOOST_CHECK_EQUAL(*list.begin(), "third");

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
				list.PushBack("string");
			}
			std::cout << "(list is filled, ";
		}
		std::cout << "and successfully destroyed)" << std::endl;
	}

	BOOST_FIXTURE_TEST_SUITE(iterator_operator, filled)

		BOOST_AUTO_TEST_CASE(prefix_incremenet_and_decrement_work_correctly)
		{
			auto it = list.begin();
			BOOST_CHECK_EQUAL(*(++it), expectedStrings[1]);
			BOOST_CHECK_EQUAL(*(--it), expectedStrings[0]);
		}

		BOOST_AUTO_TEST_CASE(postfix_incremenet_and_decrement_work_correctly)
		{
			auto it = list.begin();
			BOOST_CHECK_EQUAL(*(it++), expectedStrings[0]);
			BOOST_CHECK_EQUAL(*(it--), expectedStrings[1]);
			BOOST_CHECK_EQUAL(*(it), expectedStrings[0]);
			BOOST_CHECK_EQUAL(*it, expectedStrings[0]);
		}

		BOOST_AUTO_TEST_CASE(is_equal_works_correctly)
		{
			BOOST_CHECK(list.begin() == (list.begin()));
			BOOST_CHECK(!(list.begin() == (++list.begin())));
		}

		BOOST_AUTO_TEST_CASE(is_not_equal_works_correctly)
		{
			auto it = list.begin();
			BOOST_CHECK(!(list.begin() != list.begin()));
			BOOST_CHECK(list.begin() != (++list.begin()));
		}

		BOOST_AUTO_TEST_CASE(arrow_works_correctly)
		{
			BOOST_CHECK_EQUAL(list.begin()->length(), expectedStrings[0].length());
		}

		BOOST_AUTO_TEST_CASE(star_works_correctly)
		{
			auto it = list.begin();
			BOOST_CHECK_EQUAL(*it, expectedStrings[0]);
		}

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()