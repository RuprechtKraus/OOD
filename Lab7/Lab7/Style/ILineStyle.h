#pragma once
#include "IStyle.h"

class ILineStyle : public IStyle
{
public:
	virtual void SetLineWidth(int width) = 0;
	virtual std::optional<int> GetLineWidth() const = 0;
};