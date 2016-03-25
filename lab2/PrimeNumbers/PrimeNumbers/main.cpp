#include "stdafx.h"
#include "PrimeNumbers.h"

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cout << "enter <upper bound>" << std::endl;
		return 1;
	}

	auto primeNumbers = GeneratePrimeNumbersSet(std::stoi(argv[1]));
	PrintSetOfInt(primeNumbers, std::cout);

	return 0;
}