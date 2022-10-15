#pragma once
#include "Canvas/ICanvas.h"
#include "Designer/IDesigner.h"
#include "Painter/Painter.h"
#include <istream>

class Client
{
public:
	Client(std::unique_ptr<ICanvas>&& canvas);

	void OrderPainting(std::istream& inputData, IDesigner& designer, Painter& painter);

private:
	std::unique_ptr<ICanvas> m_canvas;
};