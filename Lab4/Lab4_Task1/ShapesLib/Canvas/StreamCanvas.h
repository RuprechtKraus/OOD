#pragma once
#include "ICanvas.h"
#include <iostream>

class StreamCanvas : public ICanvas
{
public:
	StreamCanvas(std::ostream& os = std::cout);

	void SetColor(Color color) noexcept override;
	void DrawLine(const Point& from, const Point& to) override;
	void DrawEllipse(const Point& center, int width, int height) override;

private:
	std::ostream& m_stream;
	Color m_color;
};
