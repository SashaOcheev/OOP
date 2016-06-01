
#include "stdafx.h"
#include "Cone.h"


CCone::CCone(double density, double radius, double height)
	: CSolidBody("Cone", density)
	, m_radius(radius)
	, m_height(height)
{
}

double CCone::GetRadius() const
{
	return m_radius;
}

double CCone::GetHeight() const
{
	return m_height;
}

double CCone::GetVolume() const
{
	return GetHeight() * pow(GetRadius(), 2) * M_PI / 3;
}

void CCone::AppendProperties(std::ostream &strm) const
{
	strm << "\tradius = " << GetRadius() << std::endl
		<< "\theight = " << GetHeight() << std::endl;
}