
#include "stdafx.h"
#include "SolidBody.h"

CSolidBody::CSolidBody(const std::string &type, double density)
	: CBody(type)
	, m_density(density)
{
}

double CSolidBody::GetMass() const
{
	return GetVolume() * GetDensity();
}

double CSolidBody::GetDensity() const
{
	return m_density;
}