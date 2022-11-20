#pragma once
#include "Shape/ShapeCollection/IShapeCollection.h"
#include "Shape/IDrawable.h"
#include <memory>

class Slide : public IDrawable
{
public:
	Slide();

	void Draw(ICanvas& canvas) const override;
	IShapeCollection& GetShapes() noexcept;

private:
	std::unique_ptr<IShapeCollection> m_shapes;
};