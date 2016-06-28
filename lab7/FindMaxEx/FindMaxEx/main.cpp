// FindMaxEx.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "FindMaxEx.h"

int main()
{
	{
		std::vector<int> vec = { 1, 3, 2 };
		auto max = 0;
		FindMax(vec, max);
		std::cout << max << std::endl;
	}

	{
		std::vector<const char*> vec = { "abc", "aab", "ccc", "aa" };
		auto max = "";
		FindMax(vec, max, [](const char* str1, const char* str2)
		{
			return strcmp(str1, str2) > 0;
		});
		std::cout << max << std::endl;
	}
    return 0;
}

