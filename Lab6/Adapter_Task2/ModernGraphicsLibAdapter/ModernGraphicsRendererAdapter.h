#pragma once
#include "GraphicsLib/GraphicsLib.h"
#include "ModernGraphicsLib/ModernGraphicsLib.h"

namespace mgl = modern_graphics_lib;

class ModernGraphicsRendererAdapter : public graphics_lib::ICanvas, private mgl::ModernGraphicsRenderer
{
public:
	ModernGraphicsRendererAdapter(std::ostream& out)
		: ModernGraphicsRenderer(out)
		, m_penCoordinates(0, 0)
		, m_drawing(false)
	{
	}
	
	~ModernGraphicsRendererAdapter()
	{
		EndDraw();
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

		DrawLine(m_penCoordinates, { x, y });
		MoveTo(x, y);
	}

private:
	mgl::Point m_penCoordinates;
	bool m_drawing;
};