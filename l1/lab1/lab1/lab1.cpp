// lab1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

void ReplaceSubstringInFile(const std::string searchString, const std::string replaceString, std::ifstream &inputFile, std::ofstream &outputFile)
{
	std::string tempString;
	char tempChar;
	while (inputFile.get(tempChar))
	{
		tempString += tempChar;
		if (searchString.empty() || tempString.back() != searchString[tempString.length() - 1])
		{
			while (!tempString.empty() && tempString.back() != searchString[tempString.length() - 1])
			{
				outputFile << tempString.front();
				tempString.erase(tempString.begin());
			}
		}
		else if (tempString.length() == searchString.length())
		{
			outputFile << replaceString;
			tempString.clear();
		}
	}
	outputFile << tempString;
}

int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "Russian");

	if (argc != 5)
	{
		std::cout << "invalid input format" << std::endl;
		std::cout << "enter <input file> <output file> <search string> <replace string>" << std::endl;
		return 1;
	}

	std::ifstream inputFile(argv[1], std::ios_base::in);
	if (!inputFile.is_open())
	{
		std::cout << "input file can't be opened" << std::endl;
		return 2;
	}

	std::ofstream outputFile(argv[2], std::ios_base::out | std::ios_base::trunc);

	ReplaceSubstringInFile(argv[3], argv[4], inputFile, outputFile);

	outputFile.flush();
	if (!outputFile)
	{
		std::cout << "an error occurred when writing outputFile" << std::endl;
		return 3;
	}

    return 0;
}

