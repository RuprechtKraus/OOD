#pragma once
#include "Canvas/ICanvas.h"
#include "Common/FrameRect.h"
#include "IDrawable.h"
#include "Style/ILineStyle.h"
#include "Style/IStyle.h"
#include <memory>

class IShapeGroup;

class IShape : public IDrawable
{
public:
	virtual void Draw(ICanvas& canvas) const = 0;

	virtual void SetFrame(const FrameRect& frame) = 0;
	virtual std::optional<FrameRect> GetFrame() const = 0;

	virtual std::shared_ptr<ILineStyle> GetOutlineStyle() = 0;
	virtual std::shared_ptr<const ILineStyle> GetOutlineStyle() const = 0;

	virtual std::shared_ptr<IStyle> GetFillStyle() = 0;
	virtual std::shared_ptr<const IStyle> GetFillStyle() const = 0;

	virtual std::shared_ptr<IShapeGroup> GetShapeGroup() = 0;
	virtual std::shared_ptr<const IShapeGroup> GetShapeGroup() const = 0;

	virtual ~IShape() = default;
};