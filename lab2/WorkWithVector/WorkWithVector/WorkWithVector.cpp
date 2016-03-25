// WorkWithVector.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "WorkWithVector.h"

bool IsEqualDouble(double n1, double n2, double precision)
{
	return abs(n1 - n2) < precision;
}

bool IsDivided(double dividend, double divider, double precision)
{
	double res = dividend / divider;
	return IsEqualDouble(res , round(res), precision);
}

double ArrangeOfDividedByNumber(std::vector<double> const& numbers, double divider, double precision = 0.001)
{
	size_t count = 0;
	auto SumOfDividedByNumber =
		std::accumulate(numbers.cbegin(), numbers.cend(), 0.0,
		[=, &count](double current, double y)
		{
			if (IsDivided(y, divider, precision))
			{
				count++;
				current += y;
			}
			return current;
		});

	return count ?
		SumOfDividedByNumber / count : 0.0;
}

void ProcessVector(std::vector<double> & numbers, double precision)
{
	double n1 = 3.0;
	double n2 = 2.0;

	auto mean = ArrangeOfDividedByNumber(numbers, n2, precision);

	std::for_each(numbers.begin(), numbers.end(),
		[=](double &x)
		{
			if (IsDivided(x, n1, precision))
				x *= mean;
		});
}

void SortVectorOfDoubles(std::vector<double> & numbers)
{
	std::sort(numbers.begin(), numbers.end());
}