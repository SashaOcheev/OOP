// WorkWithVector.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

bool isDivided(double number, double divider)
{
	return (number - int(number / divider) * divider == 0.0);
}

double AverageOfDivided(std::vector<double> const &numbers, double divider)
{
	double sum = 0.0;
	int count = 0;
	for (double number : numbers)
	{
		if (isDivided(number, divider))
		{
			sum += number;
			count++;
		}
	}
	if (count)
		return sum / count;
	return 0.0;
}

int main()
{
	std::vector<double> numbers;
	double number;
	while (std::cin >> number)
		numbers.push_back(number);

	double mean = AverageOfDivided(numbers, 2);
	std::replace_if(numbers.begin(), numbers.end(), [](double number) { return isDivided(number, 3); }, mean);

	for (double number : numbers)
		std::cout << std::fixed << std::setprecision(3) << number << ' ';

    return 0;
}

