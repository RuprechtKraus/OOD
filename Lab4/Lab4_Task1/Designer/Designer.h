#pragma once
#include "Shapes/IShapeFactory.h"
#include "Shapes/PictureDraft.h"

class Designer
{
public:
	Designer(IShapeFactory& factory);

	PictureDraft CreateDraft(std::istream& inputData);

private:
	IShapeFactory& m_factory;
};