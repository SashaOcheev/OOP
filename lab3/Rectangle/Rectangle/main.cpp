// Rectangle.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CRectangle.h"
#include "RectangleFromFile.h"

int main(int argc, char * argv[])
{
	if (argc < 3)
	{
		std::cout << "enter two input file to set rectangles" << std::endl;
		return 1;
	}
	
	Set2RectangleFromFilesAndPutItAndIntersectionToOstream(argv[1], argv[2], std::cout);

	return 0;
}