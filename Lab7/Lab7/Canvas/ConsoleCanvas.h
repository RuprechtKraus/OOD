#pragma once
#include "Canvas/ICanvas.h"
#include <string>

class ConsoleCanvas : public ICanvas
{
public:
	void SetLineColor(std::optional<RGBAColor> color) noexcept override;
	void SetFillColor(std::optional<RGBAColor> color) noexcept override;
	void SetLineWidth(std::optional<int> width) noexcept override;

	void DrawLine(const Point& from, const Point& to) const override;
	void DrawPolygon(const std::vector<Point>& points) const override;
	void DrawEllipse(const Point& center, int width, int height) const override;

private:
	static std::string ColorToHexString(std::optional<RGBAColor> color);

	std::optional<RGBAColor> m_lineColor = 0xFFFFFF;
	std::optional<RGBAColor> m_fillColor = 0xFFFFFF;
	std::optional<int> m_lineWidth = 1;
};