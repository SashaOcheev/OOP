
#include "stdafx.h"
#include "Compound.h"


CCompound::CCompound(const std::unique_ptr<CBody> &bodyPtr)
	: CBody("Compound")
{
	m_bodyPtrs.push_back(bodyPtr);
}

CCompound::CCompound(const std::vector<std::unique_ptr<CBody> > &bodyPtrs)
	: CBody("Compound")
	, m_bodyPtrs(bodyPtrs)
{
}


void CCompound::AddBody(const std::unique_ptr<CBody> &bodyPtr)
{
	m_bodyPtrs.push_back(bodyPtr);
}

double CCompound::GetDensity() const
{
	return GetMass() / GetVolume();
}

double CCompound::GetVolume() const
{
	return
		std::accumulate(m_bodyPtrs.cbegin(), m_bodyPtrs.end(), 0,
		[](const std::unique_ptr<CBody> &body1, const std::unique_ptr<CBody> &body2)
	{
		return body1->GetVolume() + body2->GetVolume();
	});
}

double CCompound::GetMass() const
{
	return
		std::accumulate(m_bodyPtrs.cbegin(), m_bodyPtrs.end(), 0,
		[](const std::unique_ptr<CBody> &body1, const std::unique_ptr<CBody> &body2)
	{
		return body1->GetMass() + body2->GetMass();
	});
}

void CCompound::AppendProperties(std::ostream & strm) const
{
	std::for_each(m_bodyPtrs.begin(), m_bodyPtrs.end(),
		[](const std::unique_ptr<CBody> &body)
	{
		body->ToString();
	});
}
