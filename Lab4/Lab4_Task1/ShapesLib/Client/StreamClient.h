#pragma once
#include "Canvas/StreamCanvas.h"
#include "Client.h"

class StreamClient : public Client
{
public:
	StreamClient();

protected:
	void VisualizeDraft(const PictureDraft& draft, Painter& painter) override;
};