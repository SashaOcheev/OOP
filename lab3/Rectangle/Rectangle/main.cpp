// Rectangle.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CRectangle.h"

int main()
{
	CRectangle rect1(0, 0, 10, 10);
	CRectangle rect2(11, 11, 10, 10);
	if (rect1.Intersect(rect2))
		std::cout << "true";
	else
		std::cout << "false";
	std::cout << std::endl;
	return 0;
}

