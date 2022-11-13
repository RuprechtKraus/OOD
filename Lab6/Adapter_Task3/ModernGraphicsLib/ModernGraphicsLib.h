#pragma once
#include <iostream>

// ������������ ���� ����������� ����������� ���������� (���������� ��� ���������)
namespace modern_graphics_lib
{
class Point
{
public:
	Point(int x, int y)
		: x(x)
		, y(y)
	{
	}

	int x;
	int y;
};

// ���� � ������� RGBA, ������ ��������� ��������� �������� �� 0.0f �� 1.0f
class RGBAColor
{
public:
	RGBAColor(float r, float g, float b, float a)
		: r(r)
		, g(g)
		, b(b)
		, a(a)
	{
	}

	float r, g, b, a;
};

// ����� ��� ������������ ��������� �������
class ModernGraphicsRenderer
{
public:
	ModernGraphicsRenderer(std::ostream& strm);
	~ModernGraphicsRenderer();

	// ���� ����� ������ ���� ������ � ������ ���������
	void BeginDraw();

	// ��������� ��������� �����
	void DrawLine(const Point& start, const Point& end, const RGBAColor& color);

	// ���� ����� ������ ���� ������ � ����� ���������
	void EndDraw();

private:
	std::ostream& m_out;
	bool m_drawing = false;
};
} // namespace modern_graphics_lib