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

// ����� ��� ������������ ��������� �������
class ModernGraphicsRenderer
{
public:
	ModernGraphicsRenderer(std::ostream& strm);
	~ModernGraphicsRenderer();

	// ���� ����� ������ ���� ������ � ������ ���������
	void BeginDraw();

	// ��������� ��������� �����
	void DrawLine(const Point& start, const Point& end);

	// ���� ����� ������ ���� ������ � ����� ���������
	void EndDraw();

private:
	std::ostream& m_out;
	bool m_drawing = false;
};
} // namespace modern_graphics_lib