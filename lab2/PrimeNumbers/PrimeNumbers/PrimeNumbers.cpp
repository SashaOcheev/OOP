// PrimeNumbers.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "PrimeNumbers.h"

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

void PrintSetOfInt(std::set<int> const& set, std::ostream &stream)
{
	std::copy(set.cbegin(), set.cend(), std::ostream_iterator<int>(stream, "\n"));
}
