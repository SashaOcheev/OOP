#include "stdafx.h"

#include "FindAndReplace.h"


int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		std::cout << "enter-format: <search-string> <replace-string>" << std::endl;
		return 1;
	}

	std::cout << "enter the string" << std::endl;
	std::string str;
	std::cin >> str;
	std::cout << std::endl;
	std::cout << FindAndReplace(str, argv[1], argv[2]) << std::endl;

	return 0;
}