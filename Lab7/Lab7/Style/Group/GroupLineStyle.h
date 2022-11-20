#pragma once
#include "GroupStyleImpl.h"
#include "Style/ILineStyle.h"
#include <functional>

using LineStyleCallback = std::function<void(ILineStyle&)>;
using LineStyleEnumerator = std::function<void(const LineStyleCallback&)>;

class GroupLineStyle : public GroupStyleImpl<ILineStyle, LineStyleEnumerator>
{
private:
	using BaseStyle = ILineStyle;

public:
	explicit GroupLineStyle(LineStyleEnumerator&& enumerator);

	void SetLineWidth(int width) override;
	std::optional<int> GetLineWidth() const override;
};