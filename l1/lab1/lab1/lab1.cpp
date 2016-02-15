// lab1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <conio.h>

static const std::streamoff MAX_SIZE = 2147483648;

std::streamoff GetFileSize(std::string fileName)
{
	std::streamoff size = -1;
	std::ifstream file(fileName, std::ios_base::binary);
	file.seekg(0, std::ios::end);
	size = file.tellg();
	return size;
}

int main(int argc, char *argv[])
{
	if (argc != 5)
	{
		std::cout << "invalid input format" << std::endl;
		std::cout << "enter <input file> <output file> <search string> <replace string>" << std::endl;
		return 1;
	}

	std::streamoff size = GetFileSize(argv[1]);
	if (size == -1)
	{
		std::cout << "file can't be opened" << std::endl;
		return 2;
	}
	else if (size > MAX_SIZE)
	{
		std::cout << "size of file is more than 2 GB" << std::endl;
		return 3;
	}
	
	std::ifstream inputFile(argv[1], std::ios_base::in);
	std::ofstream outputFile(argv[2], std::ios_base::out | std::ios_base::trunc);

	const std::string searchString(argv[3]);
	const std::string replaceString(argv[4]);

	std::string tempString;
	char tempChar;
	while ((tempChar = inputFile.get()) != EOF)
	{		
		tempString += tempChar;

		if (!searchString.length() || tempString.back() != searchString[tempString.length() - 1])
		{
			outputFile << tempString;
			tempString.clear();
		}
		else if (tempString.length() == searchString.length())
		{
			outputFile << replaceString;
			tempString.clear();
		}
	}
	if (tempString.size())
		outputFile << tempString;

	outputFile.flush();
	if (!outputFile)
	{
		std::cout << "an error occurred when writing outputFile" << std::endl;
		return 4;
	}

    return 0;
}

