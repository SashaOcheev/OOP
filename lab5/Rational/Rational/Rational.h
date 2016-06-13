#pragma once

class CRational
{
public:
	CRational(int numerator = 0, int denominator = 1);

	int GetNumerator() const;
	int GetDenominator() const;
	double ToDouble() const;
	std::pair<int, CRational> ToCompoundFraction()  const;

	CRational const operator+() const;
	CRational const operator-() const;

	CRational & operator+=(const CRational & other);
	CRational & operator-=(const CRational & other);
	CRational & operator*=(const CRational & other);
	CRational & operator/=(const CRational & other);

private:
	int m_numerator = 0;
	int m_denominator = 1;

	void Normalize();
};

CRational const operator+(const CRational & rational1, const CRational & rational2);
CRational const operator-(const CRational & rational1, const CRational & rational2);
CRational const operator*(const CRational & rational1, const CRational & rational2);
CRational const operator/(const CRational & rational1, const CRational & rational2);

bool const operator==(const CRational & rational1, const CRational & rational2);
bool const operator!=(const CRational & rational1, const CRational & rational2);
bool const operator<(const CRational & rational1, const CRational & rational2);
bool const operator<=(const CRational & rational1, const CRational & rational2);
bool const operator>(const CRational & rational1, const CRational & rational2);
bool const operator>=(const CRational & rational1, const CRational & rational2);

std::istream & operator >> (std::istream & stream, CRational & rational);
std::ostream & operator << (std::ostream & stream, CRational const & rational);