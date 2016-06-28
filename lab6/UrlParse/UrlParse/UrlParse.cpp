// UrlParse.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int Div(int a, int b)
{
	if (a < 0 || b < 0)
	{
		throw 1;
	}

	return a / b;
}

int main()
{
	try
	{
		std::cout << Div(5, -5) << std::endl;
	}
	catch (int i)
	{
		std::cout << i << std::endl;
	}
    return 0;
}

