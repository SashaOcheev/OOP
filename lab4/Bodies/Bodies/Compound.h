#pragma once

#include "Body.h"


class CCompound final:
	public CBody
{
public:
	CCompound(const std::unique_ptr<CBody> &bodyPtr);
	CCompound(const std::vector<std::unique_ptr<CBody> > &bodyPtrs);

	double GetDensity() const override;
	double GetVolume() const override;
	double GetMass() const override;
	void AddBody(const std::unique_ptr<CBody> &bodyPtr);
protected:
	void AppendProperties(std::ostream & strm) const override;
private:
	std::vector<std::unique_ptr<CBody> > m_bodyPtrs;
};