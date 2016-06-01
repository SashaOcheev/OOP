#pragma once

#include "SolidBody.h"


class CSphere final :
	public CSolidBody
{
public:
	CSphere(double density, double radius);

	double GetRadius() const;
	double GetVolume() const override;
protected:
	void AppendProperties(std::ostream & strm) const override;
private:
	double m_radius;
};