#pragma once

class CBodiesVector
{
public:
	CBodiesVector() = default;

	void ReadBodies(std::istream &strm);
	void GetMaxMassBody(std::ostream &strm) const;
	void GetMinWeightBody(std::ostream &strm, const double liquidDensity = 1000.0) const;
private:
	std::unique_ptr<CBody> GetBody(std::istream &strm, const std::string &type);
	std::vector<std::unique_ptr<CBody> > m_bodyPtrs;
	std::unique_ptr<CBody> GetCompound(std::istream &strm);
};