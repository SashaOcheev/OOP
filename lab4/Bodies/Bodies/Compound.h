#pragma once

#include "Body.h"

class CCompound final:
	public CBody
{
public:
	CCompound();

	double GetDensity() const override;
	double GetVolume() const override;
	double GetMass() const override;
	void AddBody(std::shared_ptr<CBody> &&bodyPtr);
protected:
	void AppendProperties(std::ostream &strm) const override;
private:
	std::vector<std::shared_ptr<CBody> > m_bodyPtrs;
	bool CanAdd(CBody * mainPtr, CBody * bodyPtr) const;
};