#include "stdafx.h"
#include "program.h"
#include "BodiesVector.h"

//std::shared_ptr<CBody> GetBody(std::istream &strm, const std::string &type);
//
//void GetMaxMassBody(std::ostream &strm, const std::vector<std::shared_ptr<CBody> > & m_bodyPtrs)
//{
//	auto max = std::max_element(m_bodyPtrs.begin(), m_bodyPtrs.end(),
//		[](const std::shared_ptr<CBody> &body1, const std::shared_ptr<CBody> &body2)
//	{
//		return body1->GetMass() < body2->GetMass();
//	});
//	strm << "the max mass body: " << std::endl << (*max)->ToString() << std::endl;
//}
//
//void GetMinWeightBody(std::ostream &strm, const std::vector<std::shared_ptr<CBody> > & m_bodyPtrs, const double liquidDensity)
//{
//	auto GetWeight = [&liquidDensity](const std::shared_ptr<CBody> &body)->double
//	{
//		return (body->GetDensity() - liquidDensity) * 9.8 * body->GetVolume();
//	};
//
//	auto min = std::min_element(m_bodyPtrs.begin(), m_bodyPtrs.end(),
//		[&](const std::shared_ptr<CBody> &body1, const std::shared_ptr<CBody> &body2)
//	{
//		return GetWeight(body1) < GetWeight(body2);
//	});
//	strm << "the min weight body: " << std::endl << (*min)->ToString() << std::endl;
//}
//
//
//std::shared_ptr<CBody> GetCompound(std::istream &strm)
//{
//	CCompound compound;
//	std::string type;
//	while (type != "next")
//	{
//		strm >> type;
//		auto body = std::move(GetBody(strm, type));
//		if (body)
//		{
//			compound.AddBody(std::move(body));
//		}
//	}
//
//	return std::make_shared<CBody>(compound);
//}
//
//std::shared_ptr<CBody> GetBody(std::istream &strm, const std::string &type)
//{
//	int a, b, c, d;
//	if (type == "Cone" && strm >> a >> b >> c)
//	{
//		return std::make_shared<CCone>(CCone(a, b, c));
//	}
//	else if (type == "Cylinder" && strm >> a >> b >> c)
//	{
//		return std::make_shared<CCylinder>(CCylinder(a, b, c));
//	}
//	else if (type == "Parallelepiped" && strm >> a >> b >> c >> d)
//	{
//		return std::make_shared<CParallelepiped>(CParallelepiped(a, b, c, d));
//	}
//	else if (type == "Sphere" && strm >> a >> b)
//	{
//		return std::make_shared<CSphere>(CSphere(a, b));
//	}
//	else if (type == "Compound")
//	{
//		return std::make_shared<CCompound>(GetCompound(strm));
//	}
//	else
//	{
//		return nullptr;
//	}
//}
//
//std::vector<std::shared_ptr<CBody> > ReadBodies(std::istream & strm)
//{
//	std::vector<std::shared_ptr<CBody> > m_bodyPtrs;
//	std::string type;
//	while (strm >> type)
//	{
//		auto body = std::move(GetBody(strm, type));
//		if (body)
//		{
//			m_bodyPtrs.push_back(std::move(body));
//		}
//		if (strm.fail())
//		{
//			strm.clear();
//		}
//	}
//
//	return m_bodyPtrs;
//}