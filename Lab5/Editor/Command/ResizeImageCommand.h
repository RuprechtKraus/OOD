#pragma once
#include "Document/IDocument.h"
#include "IRevertableCommand.h"

class ResizeImageCommand : public IRevertableCommand
{
public:
	ResizeImageCommand(IDocument& document, int width, int height, size_t index);

	void Execute() override;
	void Revert() override;

private:
	IDocument& m_document;
	int m_newWidth;
	int m_newHeight;
	int m_oldWidth;
	int m_oldHeight;
	int m_index;
};