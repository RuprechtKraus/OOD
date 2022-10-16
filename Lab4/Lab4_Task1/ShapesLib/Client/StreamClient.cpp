#include "StreamClient.h"

StreamClient::StreamClient()
{
	SetCanvas(std::make_unique<StreamCanvas>());
}

void StreamClient::VisualizeDraft(const PictureDraft& draft, Painter& painter)
{
	painter.DrawPicture(draft, *m_canvas);
}