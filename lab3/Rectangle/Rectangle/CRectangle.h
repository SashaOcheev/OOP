#pragma once

#include <iostream>
#include <algorithm>

class CRectangle
{
public:
	CRectangle() = default;

	CRectangle(int left, int top, int width, int height) :
		m_left(left),
		m_top(top)
	{
		SetWidth(width);
		SetHeight(height);
	};


	int GetWidth() const
	{
		return m_width;
	}

	void SetWidth(int width)
	{
		if (width > 0)
			m_width = width;
	}


	int GetHeight() const
	{
		return m_height;
	}

	void SetHeight(int height)
	{
		if (height > 0)
			m_height = height;
	}


	int GetLeft() const
	{
		return m_left;
	}

	void SetLeft(int left)
	{
		m_left = left;
	}


	int GetTop() const
	{
		return m_top;
	}

	void SetTop(int top)
	{
		m_top = top;
	}


	int GetRight() const
	{
		return m_left + m_width;
	}

	void SetRight(int right)
	{
		SetWidth(right - m_left);
	}


	int GetBottom() const
	{
		return m_top + m_height;
	}

	void SetBottom(int bottom)
	{
		SetHeight(bottom - m_top);
	}


	unsigned Area() const
	{
		return m_height * m_width;
	}

	unsigned Perimeter() const
	{
		return (m_height + m_width) * 2;
	}


	void Move(int dx, int dy)
	{
		m_left += dx;
		m_top += dy;
	}

	void Scale(int sx, int sy)
	{
		SetWidth(m_width * sx);
		SetHeight(m_height * sy);
	}

	bool Intersect(CRectangle const& other)
	{
		auto interLeft = std::max(GetLeft(), other.GetLeft());
		auto interWidth = std::min(GetRight(), other.GetRight()) - interLeft;
		auto interTop = std::max(GetTop(), other.GetTop());
		auto interHeight = std::min(GetTop(), other.GetBottom()) - interTop;
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

private:
	int m_left = 0;
	int m_top = 0;
	int m_width = 0;
	int m_height = 0;
};