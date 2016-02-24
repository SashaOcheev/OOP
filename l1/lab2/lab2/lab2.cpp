// lab2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

static const int MIN_RADIX = 2;
static const int MAX_RADIX = 36;

std::vector<int> StringToInt(std::string stringNumber, int radix, bool & wasError)
{
	std::vector<int> digitsInDec;
	for (char ch : stringNumber)
	{
		int digit;
		if (ch >= '0' && ch <= '9' && ch - '0' < radix)
			digit = ch - '0';
		else if (ch >= 'A' && ch < radix - 10 + 'A')
			digit = ch - 'A';
		else
		{
			wasError = true;
			break;
		}
		digitsInDec.push_back(digit);
	}
	if (digitsInDec.empty())
		wasError = true;
	return digitsInDec;
}

std::string IntToString(std::vector<int> digitsInDec)
{
	std::string digitsString;
	for (int digit : digitsInDec)
	{
		char ch;
		if (digit >= 0 && digit <= 9)
			ch = digit - '0';
		else
			ch = digit - 10 + 'A';
	}
	return digitsString;
}

std::string DivideOnRadix(std::vector<int> digitsInDec, const int radix)
{
	std::vector<int> result;
	int temp = 0;
	for (int digit : digitsInDec)
	{
		result.push_back((digit + temp) / radix);

	}
}

void IntToString(int n, int radix, char str[], int bufferLength, bool & wasError)
{

}

int main(int argc, char *argv[])
{
	if (argc != 4)
	{
		std::cout << "invalid input format" << std::endl;
		std::cout << "enter <source notation> <destination notation> <value>" << std::endl;
		return 1;
	}
	
	bool wasError = false;
	int sourceNotation;
	int destinationNotation;
	if (!((sourceNotation = atoi(argv[1])) && (destinationNotation = atoi(argv[2]))))
		wasError = true;
	wasError = wasError && sourceNotation >= MIN_RADIX && sourceNotation <= MAX_RADIX &&
		destinationNotation >= MIN_RADIX && destinationNotation <= MAX_RADIX;
	if (wasError)
	{
		std::cout << "invalid notations format" << std::endl;
		return 2;
	}

	std::string stringNumber = argv[3];
	std::vector<int> digitsInDec = StringToInt(argv[3], sourceNotation, wasError);
	if (wasError)
	{
		std::cout << "invalid number format" << std::endl;
		return 3;
	}
	
	

	return 0;
}
