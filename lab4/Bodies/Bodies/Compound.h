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
	void AddBody(const std::shared_ptr<CBody> &bodyPtr);

	~CCompound();
protected:
	void AppendProperties(std::ostream &strm) const override;
private:
	bool CanAdd(const CBody * mayFatherPtr, const CBody *bodyPtr);
	std::vector<std::shared_ptr<CBody> > m_bodyPtrs;
};