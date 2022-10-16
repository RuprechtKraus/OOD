#include "Client.h"

void Client::SetCanvas(std::unique_ptr<ICanvas>&& canvas)
{
	m_canvas = std::move(canvas);
}

void Client::OrderPainting(std::istream& inputData, IDesigner& designer, Painter& painter)
{
	auto draft = designer.CreateDraft(inputData);

	if (m_canvas)
	{
		VisualizeDraft(draft, painter);
	}
}