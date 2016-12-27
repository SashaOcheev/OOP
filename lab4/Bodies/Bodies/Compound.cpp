#include "stdafx.h"
#include <memory>
#include <vector>
#include <numeric>
#include <sstream>
#include <algorithm>
#include <exception>
#include "Compound.h"


CCompound::CCompound()
	: CBody("Compound")
{
}


void CCompound::AddBody(const std::shared_ptr<CBody> &bodyPtr)
{
	if (CanAdd(this, bodyPtr.get()))
	{
		m_bodyPtrs.push_back(bodyPtr);
	}
}

bool CCompound::CanAdd(CBody * mainPtr, CBody * bodyPtr) const
{
	if (mainPtr == bodyPtr)
	{
		return false;
	}

	try
	{
		CCompound& compoundPtr = dynamic_cast<CCompound&>(*bodyPtr);
		for (auto it = compoundPtr.m_bodyPtrs.begin(); it != compoundPtr.m_bodyPtrs.end(); it++)
		{
			if (!CanAdd(mainPtr, it->get()))
				return false;
		}
	}
	catch (const std::bad_cast)
	{
	}

	return true;
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
