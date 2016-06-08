#include "stdafx.h"
#include "program.h"
#include "BodiesVector.h"

void CBodiesVector::GetMaxMassBody(std::ostream &strm) const
{
	auto max = std::max_element(m_bodyPtrs.begin(), m_bodyPtrs.end(),
		[](const std::unique_ptr<CBody> &body1, const std::unique_ptr<CBody> &body2)
	{
		return body1->GetMass() < body2->GetMass();
	});
	strm << (*max)->ToString() << std::endl;
}

void CBodiesVector::GetMinWeightBody(std::ostream &strm, const double liquidDensity) const
{
	auto GetWeight = [&liquidDensity](const std::unique_ptr<CBody> &body)->double
	{
		return (body->GetDensity() - liquidDensity) * 9.8 * body->GetVolume();
	};

	auto min = std::min_element(m_bodyPtrs.begin(), m_bodyPtrs.end(),
		[&](const std::unique_ptr<CBody> &body1, const std::unique_ptr<CBody> &body2)
	{
		return GetWeight(body1) < GetWeight(body2);
	});
	strm << (*min)->ToString() << std::endl;
}

void CBodiesVector::ReadBodies(std::istream & strm)
{
	std::string type;
	while (strm >> type)
	{
		auto body = std::move(GetBody(strm, type));
		if (body)
		{
			m_bodyPtrs.push_back(std::move(body));
		}
		if (strm.fail())
		{
			strm.clear();
		}
	}
}

std::unique_ptr<CBody> CBodiesVector::GetBody(std::istream &strm, const std::string &type)
{
	int a, b, c, d;
	if (type == "Cone" && strm >> a >> b >> c)
	{
		return std::make_unique<CCone>(CCone(a, b, c));
	}
	else if (type == "Cylinder" && strm >> a >> b >> c)
	{
		return std::make_unique<CCylinder>(CCylinder(a, b, c));
	}
	else if (type == "Parallelepiped" && strm >> a >> b >> c >> d)
	{
		return std::make_unique<CParallelepiped>(CParallelepiped(a, b, c, d));
	}
	else if (type == "Sphere" && strm >> a >> b)
	{
		return std::make_unique<CSphere>(CSphere(a, b));
	}
	else if (type == "Compound")
	{
		return std::make_unique<CCompound>(GetCompound(strm));
	}
	else
	{
		return nullptr;
	}
}

std::unique_ptr<CBody> CBodiesVector::GetCompound(std::istream &strm)
{
	CCompound compound;
	std::string type;
	while (type != "next")
	{
		strm >> type;
		auto body = std::move(GetBody(strm, type));
		if (body)
		{
			compound.AddBody(std::move(body));
		}
	}

	return std::make_unique<CBody>(compound);
}