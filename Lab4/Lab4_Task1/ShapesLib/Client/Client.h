#pragma once
#include "Canvas/ICanvas.h"
#include "Designer/IDesigner.h"
#include "Painter/Painter.h"
#include <istream>

class Client
{
public:
	void SetCanvas(std::unique_ptr<ICanvas>&& canvas);
	void OrderPainting(std::istream& inputData, IDesigner& designer, Painter& painter);

protected:
	virtual void VisualizeDraft(const PictureDraft& draft, Painter& painter) = 0;

	std::unique_ptr<ICanvas> m_canvas;
};