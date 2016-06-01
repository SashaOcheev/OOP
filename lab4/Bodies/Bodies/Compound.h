#pragma once

#include "Body.h"


class CCompound final:
	public CBody
{
public:
	CCompound(std::unique_ptr<CBody> &bodyPtr);
	CCompound(std::vector<std::unique_ptr<CBody> > &bodyPtrs);

	double GetDensity() const override;
	double GetVolume() const override;
	double GetMass() const override;
	void AddBody(std::unique_ptr<CBody> &bodyPtr);
protected:
	void AppendProperties(std::ostream &strm) const override;
private:
	std::vector<std::unique_ptr<CBody> > m_bodyPtrs;
};