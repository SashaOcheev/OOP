#pragma once

#include "Body.h"


class CSolidBody :
	public CBody
{
public:
	CSolidBody(const std::string &type, double density);

	double GetDensity() const final;
	double GetVolume() const override = 0;
	double GetMass() const final;
	~CSolidBody() override;
protected:
	void AppendProperties(std::ostream & strm) const override = 0;
private:
	double m_density;
};