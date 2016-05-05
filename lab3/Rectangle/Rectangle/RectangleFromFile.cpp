#include "stdafx.h"
#include "RectangleFromFile.h"

CRectangle SetRectangleFromFile(std::string const& fileName)
{
	CRectangle rect;

	std::ifstream file(fileName);
	if (!file.is_open())
		return rect;

	bool isSetted = false;
	std::string command;
	int a, b, c, d;
	while (!file.eof())
	{
		file >> command;
		if (command == "Rectangle" && file >> a >> b >> c >> d)
		{
			isSetted = true;
			rect.Set(a, b, c, d);
		}
		else if (command == "Move" && file >> a >> b && isSetted)
		{
			rect.Move(a, b);
		}
		else if (command == "Scale" && file >> a >> b && isSetted)
		{
			rect.Scale(a, b);
		}

		if (file.fail())
			file.clear();
		command.clear();
		
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

void PutRectanglentersectionsToOstream(std::string const& fileName1, std::string const& fileName2, std::ostream & outStream)
{
	auto rect1 = SetRectangleFromFile(fileName1);
	PutRectangleToOstream(rect1, "Rectangle 1", outStream);

	auto rect2 = SetRectangleFromFile(fileName2);
	PutRectangleToOstream(rect2, "Rectangle 2", outStream);

	if (rect1.Intersect(rect2))
	{
		PutRectangleToOstream(rect1, "Intersect", outStream);
	}
	else
	{
		outStream << "Rectangles doesn't intersects" << std::endl;
	}
}