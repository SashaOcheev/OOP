#include "stdafx.h"
#include "RectangleFromFile.h"

int ReadIntFromFile(std::ifstream & file)
{
	int number;
	file >> number;
	return number;
}

CRectangle SetRectangleFromFile(std::string const& fileName)
{
	CRectangle rect;

	std::ifstream file(fileName);
	if (!file.is_open())
		return rect;

	bool isSetted = false;
	while (!file.eof())
	{
		std::string command;
		file >> command;
		if (command == "Rectangle")
		{
			isSetted = true;
			rect.SetLeft(ReadIntFromFile(file));
			rect.SetTop(ReadIntFromFile(file));
			rect.SetWidth(ReadIntFromFile(file));
			rect.SetHeight(ReadIntFromFile(file));
		}
		else if (command == "Move" && isSetted)
		{
			rect.Move(ReadIntFromFile(file), 0);
			rect.Move(0, ReadIntFromFile(file));
		}
		else if (command == "Scale" && isSetted)
		{
			rect.Scale(ReadIntFromFile(file), 1);
			rect.Scale(1, ReadIntFromFile(file));
		}
	}
	return rect;
}

void PutRectangleToOstream(CRectangle const& rect, std::string const& rectName, std::ostream & outStream)
{
	outStream <<
		rectName << ":" << std::endl <<
		"	Left top : (" << rect.GetLeft() << "; " << rect.GetTop() << ')' << std::endl <<
		"	Size : " << rect.GetWidth() << '*' << rect.GetHeight() << std::endl <<
		"	Right bottom : (" << rect.GetRight() << "; " << rect.GetBottom() << ')' << std::endl <<
		"	Area : " << rect.Area() << std::endl <<
		"	Perimeter : " << rect.Perimeter() << std::endl;
}

void Set2RectangleFromFilesAndPutItAndIntersectionToOstream(std::string const& fileName1, std::string const& fileName2, std::ostream & outStream)
{
	auto rect1 = SetRectangleFromFile(fileName1);
	PutRectangleToOstream(rect1, "Rectangle 1", outStream);

	auto rect2 = SetRectangleFromFile(fileName2);
	PutRectangleToOstream(rect2, "Rectangle 2", outStream);

	if (rect1.Intersect(rect2))
		PutRectangleToOstream(rect1, "Intersect", outStream);
	else
		outStream << "Rectangles doesn't intersects" << std::endl;
}