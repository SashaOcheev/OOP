#include "stdafx.h"
#include <string>
#include <iomanip>
#include <sstream>
#include "Body.h"

CBody::CBody(const std::string &type)
	: m_type(type)
{
}

CBody::~CBody()
{
}

std::string CBody::ToString()const
{
	std::ostringstream strm;
	strm << m_type << ":" << std::endl << std::setprecision(10)
		<< "\tdensity = " << GetDensity() << std::endl
		<< "\tvolume = " << GetVolume() << std::endl
		<< "\tmass = " << GetMass() << std::endl;
	AppendProperties(strm);
	return strm.str();
}