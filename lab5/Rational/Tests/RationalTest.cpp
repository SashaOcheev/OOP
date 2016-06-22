
#include "stdafx.h"
#include "../Rational/Rational.h"
#include <boost/test/output/compiler_log_formatter.hpp>

void VerifyRational(const CRational & r, int expectedNumerator, int expectedDenominator)
{
	BOOST_CHECK_EQUAL(r.GetNumerator(), expectedNumerator);
	BOOST_CHECK_EQUAL(r.GetDenominator(), expectedDenominator);
}

void VerifyRational(const std::pair<int, CRational> const& rational, int expectedIntegerPart, int expectedNumerator, int expectedDenominator)
{
	BOOST_CHECK_EQUAL(rational.first, expectedIntegerPart);
	BOOST_CHECK_EQUAL((rational.second).GetNumerator(), expectedNumerator);
	BOOST_CHECK_EQUAL((rational.second).GetDenominator(), expectedDenominator);
}

BOOST_AUTO_TEST_SUITE(Rational_number)
	BOOST_AUTO_TEST_CASE(is_0_by_default)
	{
		VerifyRational(CRational(), 0, 1);
	}
	BOOST_AUTO_TEST_CASE(can_be_constructed_from_integer)
	{
		VerifyRational(CRational(10), 10, 1);
		VerifyRational(CRational(-10), -10, 1);
		VerifyRational(CRational(0), 0, 1);
	}
	BOOST_AUTO_TEST_CASE(can_be_constructed_with_numerator_and_denominator)
	{
		VerifyRational(CRational(5, 2), 5, 2);
		VerifyRational(CRational(-5, 2), -5, 2);
		VerifyRational(CRational(5, -2), -5, 2);
		VerifyRational(CRational(-5, -2), 5, 2);
	}
	BOOST_AUTO_TEST_CASE(is_normalized_after_construction)
	{
		VerifyRational(CRational(6, 8), 3, 4);
		VerifyRational(CRational(6, -8), -3, 4);
		VerifyRational(CRational(-6, 8), -3, 4);
		VerifyRational(CRational(-6, -8), 3, 4);
		VerifyRational(CRational(-10, 20), -1, 2);
	}
	BOOST_AUTO_TEST_CASE(cant_have_zero_denominator)
	{
		BOOST_REQUIRE_THROW(CRational(1, 0), std::invalid_argument);
	}

	BOOST_AUTO_TEST_CASE(can_be_returned_in_the_form_of_a_mixed_fraction)
	{
		VerifyRational(CRational(15, 2).ToCompoundFraction(), 7, 1, 2);
		VerifyRational(CRational(-9, 4).ToCompoundFraction(), -2, -1, 4);
		VerifyRational(CRational(1, 2).ToCompoundFraction(), 0, 1, 2);
	}

	BOOST_AUTO_TEST_CASE(can_be_interpreted_as_double)
	{
		BOOST_CHECK_EQUAL(CRational(3, 5).ToDouble(), 0.6);
		BOOST_CHECK_EQUAL(CRational(-2, 10).ToDouble(), -0.2);
		BOOST_CHECK_EQUAL(CRational(0, 10).ToDouble(), 0);
	}

	struct unaryOperation_
	{
		CRational rational_3_5;
		unaryOperation_()
			: rational_3_5(3, 5)
		{}
	};

	BOOST_FIXTURE_TEST_SUITE(unary_operation, unaryOperation_)
		BOOST_AUTO_TEST_CASE(unary_plus_does_not_change_sign)
		{
			VerifyRational(+rational_3_5, 3, 5);
		}
		BOOST_AUTO_TEST_CASE(unary_minus_change_numerator_sign)
		{
			VerifyRational(-rational_3_5, -3, 5);
		}
		BOOST_AUTO_TEST_CASE(unary_plus_does_not_change_source)
		{
			auto r1 = rational_3_5;
			VerifyRational(rational_3_5, 3, 5);
		}
		BOOST_AUTO_TEST_CASE(unary_minus_does_not_change_source)
		{
			auto r1 = -rational_3_5;
			VerifyRational(rational_3_5, 3, 5);
		}
	BOOST_AUTO_TEST_SUITE_END()

	struct binaryOperation_
	{
		CRational rational_1_2;
		binaryOperation_()
			: rational_1_2(1, 2)
		{}
	};

	BOOST_FIXTURE_TEST_SUITE(assignment_expression, binaryOperation_)
		BOOST_AUTO_TEST_CASE(can_be_changed_after_summ_with_the_other_rational)
		{
			rational_1_2 += CRational(1, 6);
			VerifyRational(rational_1_2, 2, 3);
		}
		BOOST_AUTO_TEST_CASE(can_be_changed_after_summ_with_int)
		{
			rational_1_2 += CRational(1);
			VerifyRational(rational_1_2, 3, 2);
		}

		BOOST_AUTO_TEST_CASE(can_be_changed_after_minus_with_the_other_rational)
		{
			rational_1_2 -= CRational(1, 6);
			VerifyRational(rational_1_2, 1, 3);
		}
		BOOST_AUTO_TEST_CASE(can_be_changed_after_minus_with_int)
		{
			rational_1_2 -= CRational(1);
			VerifyRational(rational_1_2, -1, 2);
		}

		BOOST_AUTO_TEST_CASE(can_be_changed_after_multiplication_by_other_rational)
		{
			rational_1_2 *= CRational(2, 3);
			VerifyRational(rational_1_2, 1, 3);
		}
		BOOST_AUTO_TEST_CASE(can_be_changed_after_multiplication_by_integer)
		{
			rational_1_2 *= CRational(3);
			VerifyRational(rational_1_2, 3, 2);
		}

		BOOST_AUTO_TEST_CASE(can_be_changed_after_division_by_other_rational)
		{
			rational_1_2 /= CRational(2, 3);
			VerifyRational(rational_1_2, 3, 4);
		}
		BOOST_AUTO_TEST_CASE(can_be_changed_after_division_by_integerr)
		{
			rational_1_2 /= CRational(3);
			VerifyRational(rational_1_2, 1, 6);
		}

		BOOST_AUTO_TEST_CASE(cant_be_divided_by_rational_with_zero_numerator)
		{
			BOOST_REQUIRE_THROW(rational_1_2 /= CRational(0, 3), std::invalid_argument);
		}
		BOOST_AUTO_TEST_CASE(cant_be_divided_by_rational_with_zero_integer)
		{
			BOOST_REQUIRE_THROW(rational_1_2 /= 0, std::invalid_argument);
		}
	BOOST_AUTO_TEST_SUITE_END()


	BOOST_FIXTURE_TEST_SUITE(binary_opeartion, binaryOperation_)
		BOOST_AUTO_TEST_CASE(can_be_realized_the_binary_summ_with_rational_or_ineteger)
		{
			VerifyRational(rational_1_2 + CRational(1, 6), 2, 3);
			VerifyRational(rational_1_2 + 1, 3, 2);
			VerifyRational(1 + rational_1_2, 3, 2);
		}

		BOOST_AUTO_TEST_CASE(can_be_realize_the_binary_minus_with_rational_or_ineteger)
		{
			VerifyRational(rational_1_2 - CRational(1, 6), 1, 3);
			VerifyRational(rational_1_2 - 1, -1, 2);
			VerifyRational(1 - rational_1_2, 1, 2);
		}

		BOOST_AUTO_TEST_CASE(can_be_multiplied_by_another_rational_or_integer)
		{
			VerifyRational(rational_1_2 * CRational(2, 3), 1, 3);
			VerifyRational(rational_1_2 * -3, -3, 2);
			VerifyRational(7 * rational_1_2, 7, 2);
		}

		BOOST_AUTO_TEST_CASE(can_be_dividen_by_another_rational_or_integer)
		{
			VerifyRational(rational_1_2 / CRational(2, 3), 3, 4);
			VerifyRational(rational_1_2 / 5, 1, 10);
			VerifyRational(7 / CRational(2, 3), 21, 2);
		}

		BOOST_AUTO_TEST_CASE(cant_be_dividen_by_zero_numerator_rational_or_zero_integer)
		{
			BOOST_REQUIRE_THROW(rational_1_2 / CRational(0, 3), std::invalid_argument);
			BOOST_REQUIRE_THROW(rational_1_2 /= 0, std::invalid_argument);
		}
	BOOST_AUTO_TEST_SUITE_END()


	BOOST_FIXTURE_TEST_SUITE(binary_opeartion_does_not_change_source, binaryOperation_)
		BOOST_AUTO_TEST_CASE(plus)
		{
			rational_1_2 + CRational(1, 6);
			VerifyRational(rational_1_2, 1, 2);
			rational_1_2 + CRational(1, 6);
			VerifyRational(rational_1_2, 1, 2);
			1 + CRational(1, 2);
			VerifyRational(rational_1_2, 1, 2);
		}
		BOOST_AUTO_TEST_CASE(minus)
		{
			rational_1_2 - CRational(1, 6);
			VerifyRational(rational_1_2, 1, 2);
			rational_1_2 - CRational(1, 6);
			VerifyRational(rational_1_2, 1, 2);
			1 - CRational(1, 2);
			VerifyRational(rational_1_2, 1, 2);
		}

		BOOST_AUTO_TEST_CASE(multiplication)
		{
			rational_1_2 * CRational(1, 6);
			VerifyRational(rational_1_2, 1, 2);
			rational_1_2 * CRational(1, 6);
			VerifyRational(rational_1_2, 1, 2);
			1 * CRational(1, 2);
			VerifyRational(rational_1_2, 1, 2);
		}

		BOOST_AUTO_TEST_CASE(division)
		{
			rational_1_2 / CRational(1, 6);
			VerifyRational(rational_1_2, 1, 2);
			rational_1_2 / CRational(1, 6);
			VerifyRational(rational_1_2, 1, 2);
			1 / CRational(1, 2);
			VerifyRational(rational_1_2, 1, 2);
		}
	BOOST_AUTO_TEST_SUITE_END()

	struct comparingOperation_
	{
		CRational rational_2_1;
		comparingOperation_()
			: rational_2_1(2, 1)
		{}
	};
	BOOST_FIXTURE_TEST_SUITE(comparing_operations, comparingOperation_)
		BOOST_AUTO_TEST_CASE(can_be_compared_integer_and_rational_by_operator_equals)
		{
			BOOST_CHECK(rational_2_1 == rational_2_1);
			BOOST_CHECK(!(rational_2_1 == rational_2_1 + 1));
			BOOST_CHECK(rational_2_1 == 2);
			BOOST_CHECK(!(rational_2_1 == 3));
			BOOST_CHECK(2 == rational_2_1);
			BOOST_CHECK(!(3 == rational_2_1));
		}

		BOOST_AUTO_TEST_CASE(can_be_compared_integer_and_rational_by_operator_not_equals)
		{
			BOOST_CHECK(!(rational_2_1 != rational_2_1));
			BOOST_CHECK(rational_2_1 != rational_2_1 + 1);
			BOOST_CHECK(!(rational_2_1 != 2));
			BOOST_CHECK(rational_2_1 != 3);
			BOOST_CHECK(!(2 != rational_2_1));
			BOOST_CHECK(3 != rational_2_1);
		}

		BOOST_AUTO_TEST_CASE(can_be_compared_integer_and_rational_by_operator_greater)
		{
			BOOST_CHECK(!(rational_2_1 > rational_2_1));
			BOOST_CHECK(rational_2_1 > rational_2_1 - 1);
			BOOST_CHECK(!(rational_2_1 > 2));
			BOOST_CHECK(rational_2_1 > 1);
		}

		BOOST_AUTO_TEST_CASE(can_be_compared_integer_and_rational_by_operator_greater_or_equals)
		{
			BOOST_CHECK(rational_2_1 >= rational_2_1);
			BOOST_CHECK(rational_2_1 >= rational_2_1 - 1);
			BOOST_CHECK(rational_2_1 >= 2);
			BOOST_CHECK(rational_2_1 >= 1);
			BOOST_CHECK(!(rational_2_1 >= 3));
		}

		BOOST_AUTO_TEST_CASE(can_be_compared_integer_and_rational_by_operator_less)
		{
			BOOST_CHECK(!(rational_2_1 < rational_2_1));
			BOOST_CHECK(rational_2_1 < rational_2_1 + 1);
			BOOST_CHECK(!(rational_2_1 < 2));
			BOOST_CHECK(rational_2_1 < 3);
		}

		BOOST_AUTO_TEST_CASE(can_be_compared_integer_and_rational_by_operator_less_or_equals)
		{
			BOOST_CHECK(rational_2_1 <= rational_2_1);
			BOOST_CHECK(rational_2_1 <= rational_2_1 + 1);
			BOOST_CHECK(rational_2_1 <= 2);
			BOOST_CHECK(rational_2_1 <= 3);
			BOOST_CHECK(!(rational_2_1 <= 1));
		}
	BOOST_AUTO_TEST_SUITE_END()


	BOOST_FIXTURE_TEST_SUITE(ostream_operator, binaryOperation_)
		BOOST_AUTO_TEST_CASE(can_be_put_to_ostream)
		{
			std::ostringstream strm;
			strm << rational_1_2;
			BOOST_CHECK_EQUAL(strm.str(), "1/2");
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_FIXTURE_TEST_SUITE(istream_operator, binaryOperation_)
		BOOST_AUTO_TEST_CASE(can_be_got_from_istream)
		{
			std::istringstream strm("1/2");
			strm >> rational_1_2;
			VerifyRational(rational_1_2, 1, 2);
		}

		BOOST_AUTO_TEST_CASE(can_be_got_negative_rational_from_istream)
		{
			std::istringstream strm("-7/15");
			strm >> rational_1_2;
			VerifyRational(rational_1_2, -7, 15);
		}
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()