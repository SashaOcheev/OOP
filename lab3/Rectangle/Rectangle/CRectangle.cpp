#pragma once

#include "stdafx.h"
#include "CRectangle.h"


CRectangle::CRectangle(int left, int top, int width, int height)
{
	SetLeft(left);
	SetTop(top);
	SetWidth(width);
	SetHeight(height);
}


int CRectangle::GetWidth() const
{
	return m_width;
}

void CRectangle::SetWidth(int width)
{
	if (width < 0)
	{
		width = 0;
	}
	
	m_width = width;
}


int CRectangle::GetHeight() const
{
	return m_height;
}

void CRectangle::SetHeight(int height)
{
	if (height < 0)
	{
		height = 0;
	}

	m_height = height;
}


int CRectangle::GetLeft() const
{
	return m_left;
}

void CRectangle::SetLeft(int left)
{
	m_left = left;
}


int CRectangle::GetTop() const
{
	return m_top;
}

void CRectangle::SetTop(int top)
{
	m_top = top;
}


int CRectangle::GetRight() const
{
	return m_left + m_width;
}

void CRectangle::SetRight(int right)
{
	SetWidth(right - m_left);
}


int CRectangle::GetBottom() const
{
	return m_top + m_height;
}

void CRectangle::SetBottom(int bottom)
{
	SetHeight(bottom - m_top);
}


unsigned CRectangle::Area() const
{
	return m_height * m_width;
}

unsigned CRectangle::Perimeter() const
{
	auto perim = m_height + m_width;

	if (GetWidth() > 0 && GetHeight() > 0)
		perim *= 2;

	return perim;
}


void CRectangle::Move(int dx, int dy)
{
	m_left += dx;
	m_top += dy;
}

void CRectangle::Scale(int sx, int sy)
{
	if (sx < 0 || sy < 0)
		return;

	SetWidth(m_width * sx);
	SetHeight(m_height * sy);
}

bool CRectangle::Intersect(CRectangle const& other)
{
	auto interLeft = std::max(GetLeft(), other.GetLeft());
	auto interWidth = std::min(GetRight(), other.GetRight()) - interLeft;
	auto interTop = std::max(GetTop(), other.GetTop());
	auto interHeight = std::min(GetBottom(), other.GetBottom()) - interTop;
	if (interHeight < 0 || interWidth < 0)
	{
		SetWidth(0);
		SetHeight(0);
		return false;
	}
	SetLeft(interLeft);
	SetWidth(interWidth);
	SetHeight(interHeight);
	SetTop(interTop);
	return true;
}