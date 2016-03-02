// lab2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

static const int MIN_RADIX = 2;
static const int MAX_RADIX = 36;

std::vector<int> StringToDigitsVector(const std::string &stringNumber, int radix)
{
	std::vector<int> digitsInDec;
	for (char ch : stringNumber)
	{
		int digit;
		if (ch >= '0' && ch <= '9' && ch - '0' < radix)
			digit = ch - '0';
		else if (ch >= 'A' && ch - 'A' < radix - 10)
			digit = ch + 10 - 'A';
		else
		{
			digitsInDec.clear();
			break;
		}
		digitsInDec.push_back(digit);
	}

	return digitsInDec;
}

std::string IntToString(const std::vector<int> &digitsInDec)
{
	std::string digitsString;
	for (int digit : digitsInDec)
	{
		if (digit >= 0 && digit <= 9)
			digitsString += '0' + digit;
		else
			digitsString += 'A' - 10 + digit;
	}
	return digitsString;
}

struct DivisionResult
{
	std::vector <int> integerPart;
	int remaind;
};

DivisionResult DivideNumberOfSourceNotation(const std::vector<int> &digits, int sourceNotation, int divider)
{
	DivisionResult currentResult;
	currentResult.remaind = 0;
	bool isIntegerPartNot0 = false;
	for (int digit : digits)
	{
		int integerPart = (currentResult.remaind + digit) / divider;
		if (isIntegerPartNot0 || integerPart)
		{
			currentResult.integerPart.push_back(integerPart);
			isIntegerPartNot0 = true;
		}
		currentResult.remaind = (currentResult.remaind + digit) % divider * sourceNotation;
	}
	currentResult.remaind /= sourceNotation;
	return currentResult;
}

std::vector<int> ConvertToOtherRadix(const std::vector<int> &digits, int sourceNotation, int destinationNotation)
{
	std::vector<int> result;
	DivisionResult currentResultOfDivision = { digits, 0 };
	while (!currentResultOfDivision.integerPart.empty())
	{
		currentResultOfDivision = DivideNumberOfSourceNotation(currentResultOfDivision.integerPart, sourceNotation, destinationNotation);
		result.push_back(currentResultOfDivision.remaind);
	}
	return{ result.rbegin(), result.rend() };
}

std::string ConvertNumberToOtherRadixInString(std::string numberInString, int sourceNotation, int destinationNotation)
{
	if (numberInString.empty())
		return "";

	int countOfValidPreNumberSymbols = 0; // 1/0;
	std::string sign = "";
	switch (numberInString.front())
	{
	case '-':
		sign = "-";
		countOfValidPreNumberSymbols = 1;
		break;
	case '+':
		countOfValidPreNumberSymbols = 1;
		break;
	}

	std::vector<int> digits = StringToDigitsVector({ numberInString.begin() + countOfValidPreNumberSymbols, numberInString.end() }, sourceNotation);
	if (digits.empty())
		return "";

	std::vector<int> convertedNumber = ConvertToOtherRadix(digits, sourceNotation, destinationNotation);
	return sign + IntToString(convertedNumber);
}

bool isValidNotation(const char radixInString[], int minRadix, int maxRadix)
{
	int radix = 0;
	radix = atoi(radixInString);
	if (!radix)
		return false;
	return radix >= minRadix && radix <= maxRadix;
}

int main(int argc, char *argv[])
{
	if (argc != 4)
	{
		std::cout << "invalid input format" << std::endl;
		std::cout << "enter <source notation> <destination notation> <value>" << std::endl;
		return 1;
	}
	
	bool wasNotError = isValidNotation(argv[1], MIN_RADIX, MAX_RADIX) && isValidNotation(argv[2], MIN_RADIX, MAX_RADIX);
	if (!wasNotError)
	{
		std::cout << "invalid notations format" << std::endl;
		std::cout << "enter 2 <= notation <= 36" << std::endl;
		return 2;
	}
	int sourceNotation = sourceNotation = atoi(argv[1]);
	int destinationNotation = atoi(argv[2]);


	std::string numberInString = ConvertNumberToOtherRadixInString(argv[3], sourceNotation, destinationNotation);
	if (numberInString.empty())
	{
		std::cout << "invalid number format" << std::endl;
		return 3;
	}
	
	std::cout << numberInString << std::endl;

	return 0;
}