#pragma once
#include "Canvas/ICanvas.h"
#include "Shapes/PictureDraft.h"

class Painter
{
public:
	void DrawPicture(const PictureDraft& draft, ICanvas& canvas) const;
};