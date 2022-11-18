#pragma once
#include "Canvas/ICanvas.h"

class ConsoleCanvas : public ICanvas
{
public:
	void SetLineColor(RGBAColor color) noexcept override;
	void SetFillColor(RGBAColor color) noexcept override;
	void SetLineWidth(int width) noexcept override;

	void DrawLine(const Point& from, const Point& to) const override;
	void DrawPolygon(const std::vector<Point>& points) const override;
	void DrawEllipse(const Point& center, int width, int height) const override;

private:
	RGBAColor m_lineColor = 0xFFFFFF;
	RGBAColor m_fillColor = 0xFFFFFF;
	int m_lineWidth = 1;
};