
#include "stdafx.h"
#include "Cylinder.h"


CCylinder::CCylinder(double density, double radius, double height)
	: CSolidBody("Cylinder", density)
	, m_radius(radius)
	, m_height(height)
{
}

double CCylinder::GetRadius() const
{
	return m_radius;
}

double CCylinder::GetHeight() const
{
	return m_height;
}

double CCylinder::GetVolume() const
{
	return GetHeight() * pow(GetRadius(), 2) * M_PI;
}

void CCylinder::AppendProperties(std::ostream &strm) const
{
	strm << "\tradius = " << GetRadius() << std::endl
		<< "\theight = " << GetHeight() << std::endl;
}