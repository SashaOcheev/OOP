#include "stdafx.h"
#include "program.h"
#include "BodiesVector.h"

std::shared_ptr<CBody> GetBody(std::istream &strm, const std::string &type, unsigned tabCount = 0);
bool GetHelpForCone(std::istream &strm, double &density, double &radius, double &height, unsigned tabCount = 0);
bool GetHelpForParallelepiped(std::istream &strm, double &density, double &width, double &height, double &depth, unsigned tabCount = 0);
bool GetHelpForSphere(std::istream &strm, double &density, double &radius, unsigned tabCount = 0);
std::string GetHelp(unsigned tabCount = 0);
std::string GetHelpForCompound(unsigned tabCount = 0);


void GetMaxMassBody(std::ostream &strm, const std::vector<std::shared_ptr<CBody> > & m_bodyPtrs)
{
	if (m_bodyPtrs.empty())
	{
		return;
	}
	auto max = std::max_element(m_bodyPtrs.begin(), m_bodyPtrs.end(),
		[](const std::shared_ptr<CBody> &body1, const std::shared_ptr<CBody> &body2)
	{
		return body1->GetMass() < body2->GetMass();
	});
	strm << "the max mass body: " << std::endl << (*max)->ToString() << std::endl;
}

void GetMinWeightBody(std::ostream &strm, const std::vector<std::shared_ptr<CBody> > & m_bodyPtrs, const double liquidDensity)
{
	if (m_bodyPtrs.empty())
	{
		return;
	}
	auto GetWeight = [&liquidDensity](const std::shared_ptr<CBody> &body)->double
	{
		return (body->GetDensity() - liquidDensity) * 9.8 * body->GetVolume();
	};

	auto min = std::min_element(m_bodyPtrs.begin(), m_bodyPtrs.end(),
		[&](const std::shared_ptr<CBody> &body1, const std::shared_ptr<CBody> &body2)
{
		return GetWeight(body1) < GetWeight(body2);
	});
	strm << "the min weight body: " << std::endl << (*min)->ToString() << std::endl;
}


std::shared_ptr<CCompound> GetCompound(std::istream &strm, unsigned tabCount = 0)
{
	std::shared_ptr<CCompound> compound = std::make_shared<CCompound>();
	std::string type;
	while (type != "next")
	{
		std::cout << GetHelpForCompound(tabCount);
		if (strm >> type)
		{
			auto body = GetBody(strm, type, tabCount);
			if (body)
			{
				compound->AddBody(body);
			}
		}
		else
		{
			type = "next";
		}
	}

	return compound;
}

std::shared_ptr<CBody> GetBody(std::istream &strm, const std::string &type, unsigned tabCount)
{
	double a, b, c, d;
	if (type == "cone" && GetHelpForCone(strm, a, b, c, tabCount))
	{
		return std::make_shared<CCone>(CCone(a, b, c));
	}
	else if (type == "cylinder" && GetHelpForCone(strm, a, b, c, tabCount))
	{
		return std::make_shared<CCylinder>(CCylinder(a, b, c));
	}
	else if (type == "parallelepiped" && GetHelpForParallelepiped(strm, a, b, c, d, tabCount))
	{
		return std::make_shared<CParallelepiped>(CParallelepiped(a, b, c, d));
	}
	else if (type == "sphere" && GetHelpForSphere(strm, a, b, tabCount))
	{
		return std::make_shared<CSphere>(CSphere(a, b));
	}
	else if (type == "compound")
	{
		return GetCompound(strm, tabCount + 1);
	}
	else
	{
		return nullptr;
	}
}

std::vector<std::shared_ptr<CBody> > ReadBodies(std::istream & strm)
{
	std::vector<std::shared_ptr<CBody> > m_bodyPtrs;
	std::string type;
	std::cout << GetHelp();
	while (strm >> type)
	{
		auto body = GetBody(strm, type);
		if (body)
		{
			m_bodyPtrs.push_back(body);
		}
		if (strm.fail())
		{
			strm.clear();
		}
		std::cout << GetHelp();
	}

	return m_bodyPtrs;
}

bool GetHelpForCone(std::istream &strm, double &density, double &radius, double &height, unsigned tabCount)
{
	std::cout << std::string(tabCount, '\t') <<"Enter <density> <radius> <height>\n" << std::string(tabCount, '\t');
	return bool(strm >> density >> radius >> height);
}

bool GetHelpForParallelepiped(std::istream &strm, double &density, double &width, double &height, double &depth, unsigned tabCount)
{
	std::cout << std::string(tabCount, '\t') << "Enter <density> <width> <height> <depth>\n" << std::string(tabCount, '\t');
	return bool(strm >> density >> width >> height >> depth);
}

bool GetHelpForSphere(std::istream &strm, double &density, double &radius, unsigned tabCount)
{
	std::cout << std::string(tabCount, '\t') << "Enter <density> <radius>\n" << std::string(tabCount, '\t');
	return bool(strm >> density >> radius);
}

std::string GetHelp(unsigned tabCount)
{
	return std::string(tabCount, '\t') +
		std::string("Enter figure: cone, cylinder, parallelepiped, sphere or compound\n") +
		std::string(tabCount, '\t');
}

std::string GetHelpForCompound(unsigned tabCount)
{
	return std::string(tabCount, '\t') +
		std::string("Enter figure: cone, cylinder, parallelepiped, sphere or compound; next for end\n") +
		std::string(tabCount, '\t');
}