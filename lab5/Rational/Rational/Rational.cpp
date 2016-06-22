#include "stdafx.h"
#include "Rational.h"
#include <utility>
#include <stdexcept>
#include <boost/math/common_factor.hpp>


CRational::CRational(int numerator, int denominator)
{
	if (denominator == 0)
	{
		throw std::invalid_argument("Denominator must be nonzero");
	}
	m_numerator = (denominator < 0) ? -numerator : numerator;
	m_denominator = abs(denominator);
	Normalize();
}

void CRational::Normalize()
{
	if (!(m_numerator * m_denominator))
	{
		return;
	}
	int gcd = boost::math::gcd(m_numerator, m_denominator);
	m_numerator /= gcd;
	m_denominator /= gcd;
}

int CRational::GetNumerator() const
{
	return m_numerator;
}

int CRational::GetDenominator() const
{
	return m_denominator;
}

double CRational::ToDouble() const
{
	return static_cast<double>(GetNumerator()) / static_cast<double>(GetDenominator());
}

std::pair<int, CRational> CRational::ToCompoundFraction() const
{
	return { m_numerator / m_denominator, CRational(m_numerator % m_denominator, m_denominator) };
}

CRational const CRational::operator+() const
{
	return *this;
}

CRational const CRational::operator-() const
{
	return CRational(-GetNumerator(), GetDenominator());
}

CRational & CRational::operator+=(const CRational & other)
{
	m_numerator = GetNumerator() * other.GetDenominator() + GetDenominator() * other.GetNumerator();
	m_denominator = GetDenominator() * other.GetDenominator();
	Normalize();
	return *this;
}

CRational & CRational::operator-=(const CRational & other)
{
	return *this += -other;
}

CRational & CRational::operator*=(const CRational & other)
{
	m_numerator *= other.GetNumerator();
	m_denominator *= other.GetDenominator();
	Normalize();
	return *this;
}

CRational & CRational::operator/=(const CRational & other)
{
	*this *= CRational(other.GetDenominator(), other.GetNumerator());
	// to throw the exeption if other numerator equals 0
	return *this;
}

//////////////////////////////////////////////////

CRational const operator+(const CRational & rational1, const CRational & rational2)
{
	return (CRational(rational1) += rational2);
}

CRational const operator-(const CRational & rational1, const CRational & rational2)
{
	return (CRational(rational1) -= rational2);
}

CRational const operator*(const CRational & rational1, const CRational & rational2)
{
	return (CRational(rational1) *= rational2);
}

CRational const operator/(const CRational & rational1, const CRational & rational2)
{
	return (CRational(rational1) /= rational2);
}

bool const operator==(const CRational & rational1, const CRational & rational2)
{
	return rational1.GetNumerator() == rational2.GetNumerator() && rational1.GetDenominator() == rational2.GetDenominator();
}

bool const operator!=(const CRational & rational1, const CRational & rational2)
{
	return !(rational1 == rational2);
}

bool const operator<(const CRational & rational1, const CRational & rational2)
{
	return rational1.GetNumerator() * rational2.GetDenominator() < rational1.GetDenominator() * rational2.GetNumerator();
}

bool const operator<=(const CRational & rational1, const CRational & rational2)
{
	return rational1 < rational2 || rational1 == rational2;
}

bool const operator>(const CRational & rational1, const CRational & rational2)
{
	return !(rational1 <= rational2);
}

bool const operator>=(const CRational & rational1, const CRational & rational2)
{
	return !(rational1 < rational2);
}

std::istream & operator >> (std::istream & stream, CRational & rational)
{
	int numerator;
	int denominator;

	if ((stream >> numerator) && (stream.get() == '/') && (stream >> denominator))
	{
		rational = CRational(numerator, denominator);
	}
	return stream;
}

std::ostream & operator<<(std::ostream & stream, CRational const & rational)
{
	stream << rational.GetNumerator() << "/" << rational.GetDenominator();
	return stream;
}
