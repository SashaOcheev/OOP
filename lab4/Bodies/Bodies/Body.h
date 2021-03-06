#pragma once


class CBody
{
public:
	friend class CCompound;
	CBody(const std::string &type);

	virtual double GetDensity() const = 0;
	virtual double GetVolume() const = 0;
	virtual double GetMass() const = 0;
	std::string ToString() const;

	virtual ~CBody();
protected:
	virtual void AppendProperties(std::ostream &strm) const = 0;
private:
	CBody *m_fatherPtr = nullptr;
	std::string m_type;
};