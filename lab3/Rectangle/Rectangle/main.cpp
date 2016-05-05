// Rectangle.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CRectangle.h"
#include "RectangleFromFile.h"

int main(int argc, char * argv[])
{
	if (argc < 3 || argc > 4)
	{
		std::cout << "Usage: <rectangle_file_1> <rectangle_file_2> [reult_file]" << std::endl;
		return 1;
	}
	
	if (argc == 3)
	{
		PutRectanglentersectionsToOstream(argv[1], argv[2], std::cout);
	}
	else
	{
		std::ofstream outFile(argv[3]);
		PutRectanglentersectionsToOstream(argv[1], argv[2], outFile);
	}

	return 0;
}