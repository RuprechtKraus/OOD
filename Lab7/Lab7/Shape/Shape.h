#pragma once
#include "IShape.h"
#include <memory>

class Shape : public IShape
{
public:
	void SetFrame(const FrameRect& frame) noexcept override;
	std::optional<FrameRect> GetFrame() const override;

	std::shared_ptr<ILineStyle> GetOutlineStyle() override;
	std::shared_ptr<const ILineStyle> GetOutlineStyle() const override;

	std::shared_ptr<IStyle> GetFillStyle() override;
	std::shared_ptr<const IStyle> GetFillStyle() const override;

protected:
	virtual void AdjustScale(int scaleFactorX, int scaleFactorY) = 0;

private:
	FrameRect m_frame;
	std::shared_ptr<ILineStyle> m_lineStyle;
	std::shared_ptr<IStyle> m_fillStyle;
};