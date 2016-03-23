// PrimeNumbers.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

const int UPPER_BOUND = 100000000;

bool IsValidBound(std::string const& stringNumber, int upperBound)
{
	int number = strtol(stringNumber.c_str(), nullptr, 10);
	return number > 0 && number <= upperBound;
}

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	std::set<int> primeNumbers;
	std::vector<bool> isPrimeNumbers(upperBound + 1, true);
	for (size_t i = 2; i < isPrimeNumbers.size(); i++)
	{
		if (isPrimeNumbers[i])
		{
			primeNumbers.emplace(int(i));
			for (size_t j = i * 2; j < isPrimeNumbers.size(); j += i)
				isPrimeNumbers[j] = false;
		}
	}
	return primeNumbers;
}

void PrintSetOfint(std::set<int> const& set, std::ostream &stream)
{
	std::copy(set.cbegin(), set.cend(), std::ostream_iterator<int>(stream, "\n"));
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cout << "enter <upper bound>" << std::endl;
		return 1;
	}

	if (!IsValidBound(argv[1], UPPER_BOUND))
	{
		std::cout << "0 < upper bound <= " << UPPER_BOUND << std::endl;
		return 1;
	}

	auto bound = strtol(argv[1], nullptr, 10);
	auto primeNumbers = GeneratePrimeNumbersSet(bound);
	PrintSetOfint(primeNumbers, std::cout);

    return 0;
}

