#pragma once

#include "Body.h"


class CSolidBody :
	public CBody
{
public:
	CSolidBody(const std::string &type, double density);

	double GetDensity() const final;
	double GetMass() const final;
	~CSolidBody() override;
private:
	double m_density;
};