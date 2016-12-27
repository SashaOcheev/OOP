#pragma once
#include "Body.h"

class CBodiesVector
{
public:
	void SetLiquidDensity(double density);
	void PushBack(const std::shared_ptr<CBody> &m_bodyPtr);
	std::string GetMaxMassBody();
	std::string GetMinWeightBody();
private:
	std::vector<std::shared_ptr<CBody>> m_bodyPtrs;
	double m_liquidDensity = 0.0;
};
