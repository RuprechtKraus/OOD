#pragma once
#include "GraphicsLib/GraphicsLib.h"
#include "ModernGraphicsLib/ModernGraphicsLib.h"

namespace mgl = modern_graphics_lib;

class ModernGraphicsRendererAdapter : public graphics_lib::ICanvas
{
public:
	ModernGraphicsRendererAdapter(mgl::ModernGraphicsRenderer& renderer)
		: m_renderer(renderer)
		, m_penCoordinates(0, 0)
		, m_drawing(false)
	{
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
			m_renderer.BeginDraw();
			m_drawing = true;
		}

		m_renderer.DrawLine(m_penCoordinates, { x, y });
		MoveTo(x, y);
	}

private:
	mgl::ModernGraphicsRenderer& m_renderer;
	mgl::Point m_penCoordinates;
	bool m_drawing;
};