#pragma once
#include "GraphicsLib/GraphicsLib.h"
#include "ModernGraphicsLib/ModernGraphicsLib.h"

namespace mgl = modern_graphics_lib;

class ModernGraphicsRendererAdapter : public graphics_lib::ICanvas
	, private mgl::ModernGraphicsRenderer
{
public:
	ModernGraphicsRendererAdapter(std::ostream& out)
		: ModernGraphicsRenderer(out)
		, m_penCoordinates(0, 0)
		, m_color({ 0, 0, 0, 0 })
		, m_drawing(false)
	{
	}

	void SetColor(uint32_t rgbColor) override
	{
		float r = ((rgbColor & 0xff0000) >> 16) / 255.0f,
			  g = ((rgbColor & 0x00ff00) >> 8) / 255.0f,
			  b = (rgbColor & 0x0000ff) / 255.0f,
			  a = 1;
		m_color = { r, g, b, a };
	}

	void MoveTo(int x, int y) override
	{
		m_penCoordinates.x = x;
		m_penCoordinates.y = y;
	}

	void LineTo(int x, int y) override
	{
		if (!m_drawing)
		{
			BeginDraw();
			m_drawing = true;
		}

		DrawLine(m_penCoordinates, { x, y }, m_color);
		MoveTo(x, y);
	}

private:
	mgl::Point m_penCoordinates;
	modern_graphics_lib::RGBAColor m_color;
	bool m_drawing;
};