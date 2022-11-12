#pragma once
#include <iostream>

// ѕространство имен современной графической библиотеки (недоступно дл€ изменени€)
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

//  ласс дл€ современного рисовани€ графики
class ModernGraphicsRenderer
{
public:
	ModernGraphicsRenderer(std::ostream& strm);
	~ModernGraphicsRenderer();

	// Ётот метод должен быть вызван в начале рисовани€
	void BeginDraw();

	// ¬ыполн€ет рисование линии
	void DrawLine(const Point& start, const Point& end);

	// Ётот метод должен быть вызван в конце рисовани€
	void EndDraw();

private:
	std::ostream& m_out;
	bool m_drawing = false;
};
} // namespace modern_graphics_lib