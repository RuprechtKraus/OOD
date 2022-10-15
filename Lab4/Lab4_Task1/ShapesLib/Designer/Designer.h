#pragma once
#include "Shapes/IShapeFactory.h"
#include "IDesigner.h"

class Designer : public IDesigner
{
public:
	Designer(IShapeFactory& factory);

	PictureDraft CreateDraft(std::istream& inputData) override;

private:
	IShapeFactory& m_factory;
};