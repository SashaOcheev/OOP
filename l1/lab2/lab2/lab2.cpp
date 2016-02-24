// lab2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

static const int MIN_RADIX = 2;
static const int MAX_RADIX = 36;

std::vector<int> StringToDigitsVector(std::string stringNumber, int radix)
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

std::string IntToString(std::vector<int> digitsInDec)
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

int DivideOnRadix(std::vector<int> &digitsInDec, const int sourceNotation, const int destinationNotation)
{
	std::vector<int> result;
	int temp = 0;
	bool wasNot0 = false;
	for (int digit : digitsInDec)
	{
		if (wasNot0 || (temp + digit) / destinationNotation)
		{
			result.push_back((temp + digit) / destinationNotation);
			wasNot0 = true;
		}
		temp = (temp + digit) % destinationNotation * sourceNotation;
	}
	digitsInDec = result;
	return temp / sourceNotation;
}

std::vector<int> ConvertToOtherRadix(std::vector<int> digitsInDec, const int sourceNotation, const int destinationNotation)
{
	std::vector<int> result;
	while (!digitsInDec.empty())
		result.push_back(DivideOnRadix(digitsInDec, sourceNotation, destinationNotation));
	std::reverse(result.begin(), result.end());
	return result;
}

std::string ConvertNumberToOtherRadixInString(std::string numberInString, const int sourceNotation, const int destinationNotation)
{
	std::string sign = "";
	switch (numberInString.front())
	{
	case '-':
		sign = "-";
		numberInString.erase(numberInString.begin());
		break;
	case '+':
		numberInString.erase(numberInString.begin());
		break;
	}

	std::vector<int> digitsInDec = StringToDigitsVector(numberInString, sourceNotation);
	if (digitsInDec.empty())
		return "";

	std::vector<int> convertedNumber = ConvertToOtherRadix(digitsInDec, sourceNotation, destinationNotation);
	return sign + IntToString(convertedNumber);
}

int main(int argc, char *argv[])
{
	if (argc != 4)
	{
		std::cout << "invalid input format" << std::endl;
		std::cout << "enter <source notation> <destination notation> <value>" << std::endl;
		return 1;
	}
	
	int sourceNotation;
	int destinationNotation;
	bool wasNotError = (sourceNotation = atoi(argv[1])) && (destinationNotation = atoi(argv[2]));
	wasNotError = wasNotError && sourceNotation >= MIN_RADIX && sourceNotation <= MAX_RADIX &&
		destinationNotation >= MIN_RADIX && destinationNotation <= MAX_RADIX;
	if (!wasNotError)
	{
		std::cout << "invalid notations format" << std::endl;
		std::cout << "enter 2 =< notation <= 36" << std::endl;
		return 2;
	}

	std::string numberInString = ConvertNumberToOtherRadixInString(argv[3], sourceNotation, destinationNotation);
	if (numberInString.empty())
	{
		std::cout << "invalid number format" << std::endl;
		return 3;
	}
	
	std::cout << numberInString << std::endl;

	return 0;
}