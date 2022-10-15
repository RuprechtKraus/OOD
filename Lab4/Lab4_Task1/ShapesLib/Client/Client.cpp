#include "Client.h"

Client::Client(std::unique_ptr<ICanvas>&& canvas)
	: m_canvas(std::move(canvas))
{
}

void Client::OrderPainting(std::istream& inputData, IDesigner& designer, Painter& painter)
{
	auto draft = designer.CreateDraft(inputData);
	painter.DrawPicture(draft, *m_canvas);
}