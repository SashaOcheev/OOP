#include "stdafx.h"
#include "WorkWithVector.h"

int main()
{
	std::vector<double> numbers;

	std::copy(std::istream_iterator<double>(std::cin),
	std::istream_iterator<double>(),
	std::back_inserter(numbers));

	ProcessVector(numbers, 0.001);

	for (auto number : numbers)
		std::cout << std::fixed << std::setprecision(3) << number << ' ';
	std::cout << std::endl;

	return 0;
}