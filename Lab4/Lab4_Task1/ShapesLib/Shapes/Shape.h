#pragma once
#include "Canvas/ICanvas.h"
#include "Color.h"

class Shape
{
public:
	Shape(Color color)
		: m_color(color)
	{
	}

	virtual ~Shape() = default;
	virtual void Draw(ICanvas& canvas) const = 0;

	Color GetColor() const noexcept
	{
		return m_color;
	};

protected:
	Color m_color;
};