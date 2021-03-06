#include "stdafx.h"
#include "Compound.h"


CCompound::CCompound()
	: CBody("Compound")
{
}


void CCompound::AddBody(const std::shared_ptr<CBody> &bodyPtr)
{
	if (!bodyPtr->m_fatherPtr && CanAdd(bodyPtr.get(), this))
	{
		m_bodyPtrs.push_back(bodyPtr);
		bodyPtr->m_fatherPtr = this;
	}
}

CCompound::~CCompound()
{
	for (auto &body : m_bodyPtrs)
	{
		body->m_fatherPtr = nullptr;
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
		[](double currentVolume, const std::shared_ptr<CBody> &body)
	{
		return currentVolume + body->GetVolume();
	});
}

double CCompound::GetMass() const
{
	return
		std::accumulate(m_bodyPtrs.begin(), m_bodyPtrs.end(), 0.0,
		[](double currentMass, const std::shared_ptr<CBody> &body)
	{
		return currentMass + body->GetMass();
	});
}

void CCompound::AppendProperties(std::ostream &strm) const
{
	for (auto const &body : m_bodyPtrs)
	{
		auto str = body->ToString();
		for (size_t i = 0; i < str.size(); ++i)
		{
			if (str[i] == '\n' && i + 1 < str.size())
			{
				str.insert(i + 1, "\t");
			}
			else if (i == 0)
			{
				str.insert(i++, "\t");
			}
		}
		strm << str;
	}
}

bool CCompound::CanAdd(const CBody * mayFatherPtr, const CBody * bodyPtr)
{
	if (!bodyPtr)
	{
		return true;
	}
	if (bodyPtr == mayFatherPtr)
	{
		return false;
	}
	return (CanAdd(mayFatherPtr, bodyPtr->m_fatherPtr));
}

