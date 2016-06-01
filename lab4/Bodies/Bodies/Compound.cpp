
#include "stdafx.h"
#include "Compound.h"


CCompound::CCompound(std::unique_ptr<CBody> &bodyPtr)
	: CBody("Compound")
{
	m_bodyPtrs.push_back(std::move(bodyPtr));
}

CCompound::CCompound(std::vector<std::unique_ptr<CBody> > &bodyPtrs)
	: CBody("Compound")
	, m_bodyPtrs(std::move(bodyPtrs))
{
}


void CCompound::AddBody(std::unique_ptr<CBody> &bodyPtr)
{

	m_bodyPtrs.push_back(std::move(bodyPtr));
}

double CCompound::GetDensity() const
{
	return GetMass() / GetVolume();
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
	std::for_each(m_bodyPtrs.begin(), m_bodyPtrs.end(),
		[](const std::unique_ptr<CBody> &body)
	{
		body->ToString();
	});
}
