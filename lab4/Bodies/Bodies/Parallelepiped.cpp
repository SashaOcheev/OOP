
#include "stdafx.h"
#include "Parallelepiped.h"


CParallelepiped::CParallelepiped(double density, double width, double height, double depth)
	: CSolidBody("Parallelepiped", density)
	, m_width(width)
	, m_height(height)
	, m_depth(depth)
{
}

double CParallelepiped::GetWidth() const
{
	return m_width;
}

double CParallelepiped::GetHeight() const
{
	return m_height;
}

double CParallelepiped::GetDepth() const
{
	return m_depth;
}

double CParallelepiped::GetVolume() const
{
	return GetWidth() * GetHeight() * GetDepth();
}

void CParallelepiped::AppendProperties(std::ostream &strm) const
{
	strm << "\tWidth = " << GetWidth() << std::endl
		<< "\tHeight = " << GetHeight() << std::endl
		<< "\tDepth = " << GetDepth() << std::endl;
}