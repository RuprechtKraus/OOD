#pragma once
#include "GraphicsLib/GraphicsLib.h"

// ������������ ���� ���������� ��� ��������� ����� (���������� graphics_lib)
// ��� ���������� ���������� ��� ���������
namespace shape_drawing_lib
{
struct Point
{
	int x;
	int y;
};

// ��������� ��������, ������� ����� ���� ���������� �� ������ �� graphics_lib
class ICanvasDrawable
{
public:
	virtual void Draw(graphics_lib::ICanvas& canvas) const = 0;
	virtual ~ICanvasDrawable() = default;
};

class Triangle : public ICanvasDrawable
{
public:
	Triangle(const Point& p1, const Point& p2, const Point& p3)
		: m_p1(p1)
		, m_p2(p2)
		, m_p3(p3)
	{
	}

	void Draw(graphics_lib::ICanvas& canvas) const override
	{
		canvas.MoveTo(m_p1.x, m_p1.y);
		canvas.LineTo(m_p2.x, m_p2.y);
		canvas.LineTo(m_p3.x, m_p3.y);
		canvas.LineTo(m_p1.x, m_p1.y);
	}

private:
	Point m_p1;
	Point m_p2;
	Point m_p3;
};

class Rectangle : public ICanvasDrawable
{
public:
	Rectangle(const Point& leftTop, int width, int height)
	{
		if (width < 0 || height < 0)
		{
			throw std::invalid_argument("Width and height cannot be negative");
		}

		m_point = leftTop;
		m_width = width;
		m_height = height;
	}

	void Draw(graphics_lib::ICanvas& canvas) const override
	{
		canvas.MoveTo(m_point.x, m_point.y);
		canvas.LineTo(m_point.x + m_width, m_point.y);
		canvas.LineTo(m_point.x + m_width, m_point.y + m_height);
		canvas.LineTo(m_point.x, m_point.y + m_height);
		canvas.LineTo(m_point.x, m_point.y);
	}

private:
	Point m_point;
	int m_width;
	int m_height;
};

// ��������, ��������� �������� ICanvasDrawable-������� �� ICanvas
class CanvasPainter
{
public:
	CanvasPainter(graphics_lib::ICanvas& canvas)
		: m_canvas(canvas)
	{
	}

	void Draw(const ICanvasDrawable& drawable)
	{
		drawable.Draw(m_canvas);
	}

private:
	graphics_lib::ICanvas& m_canvas;
};
} // namespace shape_drawing_lib
