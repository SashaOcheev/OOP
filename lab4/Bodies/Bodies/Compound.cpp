
#include "stdafx.h"
#include "Compound.h"


CCompound::CCompound()
	: CBody("Compound")
{
}


void CCompound::AddBody(std::unique_ptr<CBody> bodyPtr)
{
	const CBody *thisBody = this;
	const CBody *appendedBody = bodyPtr.get();
	if (thisBody != appendedBody)
	{
		m_bodyPtrs.push_back(std::move(bodyPtr));
	}
}

double CCompound::GetDensity() const
{
	auto volume = GetVolume();
	return (volume > 0) ? (GetMass() / volume) : 0;
}

double CCompound::GetVolume() const
{
	return
		std::accumulate(m_bodyPtrs.begin(), m_bodyPtrs.end(), 0.0,
		[](double currentVolume, const std::unique_ptr<CBody> &body)
	{
		return currentVolume + body->GetVolume();
	});
}

double CCompound::GetMass() const
{
	return
		std::accumulate(m_bodyPtrs.begin(), m_bodyPtrs.end(), 0.0,
		[](double currentMass, const std::unique_ptr<CBody> &body)
	{
		return currentMass + body->GetMass();
	});
}

void CCompound::AppendProperties(std::ostream &strm) const
{
	for (auto const &body : m_bodyPtrs)
	{
		strm << body->ToString();
	}
}
