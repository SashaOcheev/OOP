// WorkWithVector.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "WorkWithVector.h"

bool IsEqualDouble(double n1, double n2, double precision)
{
	return abs(n1 - n2) < precision;
}

bool IsDivided(double dividend, double divider, double precision = 0.001)
{
	double res = dividend / divider;
	return IsEqualDouble(res , int(res), precision);
}

double ArrangeOfDividedByNumber(std::vector<double> const& numbers, double divider, double precision = 0.001)
{
	auto SumAndCountOfDividedByNumber = std::accumulate(numbers.cbegin(), numbers.cend(), std::make_pair<double, size_t>(0.0, 0),
		[=](std::pair<double, size_t> current, double y)
	{ return IsDivided(y, divider, precision) ? std::make_pair(current.first + y, current.second + 1) : current; });

	return SumAndCountOfDividedByNumber.second ?
		SumAndCountOfDividedByNumber.first / SumAndCountOfDividedByNumber.second : 0.0;
}

void Foo(std::vector<double> & numbers, double precision)
{
	double n1 = 3.0;
	double n2 = 2.0;

	auto mean = ArrangeOfDividedByNumber(numbers, n2, precision);

	std::for_each(numbers.begin(), numbers.end(),
		[=](double &x) { if (IsDivided(x, n1, precision)) x *= mean; });
}

int main()
{
	std::vector<double> numbers;
	
	std::copy(std::istream_iterator<double>(std::cin),
		std::istream_iterator<double>(),
		std::back_inserter(numbers));

	Foo(numbers, 0.001);

	for (auto number : numbers)
		std::cout << std::fixed << std::setprecision(3) << number << ' ';
	std::cout << std::endl;

    return 0;
}