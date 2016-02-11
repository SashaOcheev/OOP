// lab1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <conio.h>

long GetFileSize(char *fileName)
{
	long size = -1;
	std::ifstream file(fileName, std::ios_base::binary);
	file.seekg(0, std::ios::end);
	size = file.tellg();
	file.close();
	return size;
}

int main(int argc, char *argv[])
{
	if (argc != 5)
	{
		std::cout << "invalid input format" << std::endl;
		return 1;
	}

	long size = GetFileSize(argv[1]);
	if (size == -1)
	{
		std::cout << "file can't be opened" << std::endl;
		return 2;
	}
	else if (size > 2147483648)
	{
		std::cout << "size of file is more than 2 GB" << std::endl;
		return 3;
	}
	
	std::ifstream fin(argv[1], std::ios_base::in);
	std::ofstream fout(argv[2], std::ios_base::out | std::ios_base::trunc);

	const std::string searchString(argv[3]);
	const std::string replaceString(argv[4]);
	std::string tempString;

	char tempChar;

	while ((tempChar = fin.get()) != EOF)
	{		

		tempString += tempChar;

		if (!searchString.length() || tempString.back() != searchString[tempString.length() - 1])
		{
			fout << tempString;
			tempString.clear();
		}
		else if (tempString.length() == searchString.length())
		{
			fout << replaceString;
			tempString.clear();
		}
	}

	fin.close();
	fout.close();

    return 0;
}

