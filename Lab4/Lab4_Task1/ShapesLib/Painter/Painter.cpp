#include "Painter.h"

void Painter::DrawPicture(const PictureDraft& draft, ICanvas& canvas) const
{
	for (const Shape& shape : draft)
	{
		shape.Draw(canvas);
	}
}