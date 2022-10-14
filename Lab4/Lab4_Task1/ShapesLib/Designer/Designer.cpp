#include "Designer.h"
#include <fstream>
#include <string>

Designer::Designer(IShapeFactory& factory)
	: m_factory(factory)
{
}

PictureDraft Designer::CreateDraft(std::istream& inputData)
{
	PictureDraft draft;
	std::string line;

	while (std::getline(inputData, line))
	{
		draft.AddShape(m_factory.CreateShape(line));
	}

	return draft;
}