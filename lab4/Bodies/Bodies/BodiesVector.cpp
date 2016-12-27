#include "stdafx.h"
#include "program.h"
#include "BodiesVector.h"


void CBodiesVector::SetLiquidDensity(double density)
{
	if (density > 0.0)
	{
		m_liquidDensity = density;
	}
}

void CBodiesVector::PushBack(const std::shared_ptr<CBody> &m_bodyPtr)
{
	m_bodyPtrs.push_back(m_bodyPtr);
}

std::string CBodiesVector::GetMaxMassBody()
{
	if (m_bodyPtrs.empty())
	{
		return "";
	}
	auto max = std::max_element(m_bodyPtrs.begin(), m_bodyPtrs.end(),
		[](const std::shared_ptr<CBody> &body1, const std::shared_ptr<CBody> &body2)
	{
		return body1->GetMass() < body2->GetMass();
	});
	return "the max mass body:\n" + (*max)->ToString() + "\n";
}

std::string CBodiesVector::GetMinWeightBody()
{
	if (m_bodyPtrs.empty())
	{
		return "";
	}
	auto GetWeight = [&](const std::shared_ptr<CBody> &body)->double
	{
		return (body->GetDensity() - m_liquidDensity) * 9.8 * body->GetVolume();
	};

	auto min = std::min_element(m_bodyPtrs.begin(), m_bodyPtrs.end(),
		[&](const std::shared_ptr<CBody> &body1, const std::shared_ptr<CBody> &body2)
	{
		return GetWeight(body1) < GetWeight(body2);
	});
	return "the min weight body:\n" + (*min)->ToString() + "\n";
}

