#pragma once

#include <iostream>
#include <algorithm>

class CRectangle
{
public:
	CRectangle() = default;
	CRectangle(int left, int top, int width, int height);

	int GetWidth() const;
	void SetWidth(int width);

	int GetHeight() const;
	void SetHeight(int height);

	int GetLeft() const;
	void SetLeft(int left);

	int GetTop() const;
	void SetTop(int top);

	int GetRight() const;
	void SetRight(int right);

	int GetBottom() const;
	void SetBottom(int bottom);

	unsigned Area() const;
	unsigned Perimeter() const;

	void Move(int dx, int dy);
	void Scale(int sx, int sy);
	bool Intersect(CRectangle const& other);

private:
	int m_left = 0;
	int m_top = 0;
	int m_width = 0;
	int m_height = 0;
};