#pragma once
#include "Shapes/PictureDraft.h"
#include <iostream>

class IDesigner
{
public:
	virtual PictureDraft CreateDraft(std::istream& inputData) = 0;
	virtual ~IDesigner() = default;
};