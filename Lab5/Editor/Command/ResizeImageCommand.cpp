#include "ResizeImageCommand.h"

ResizeImageCommand::ResizeImageCommand(IDocument& document, int width, int height, size_t index)
	: m_document(document)
	, m_newWidth(width)
	, m_newHeight(height)
	, m_index(index)
{
}

void ResizeImageCommand::Execute()
{
	auto image = m_document.GetItem(m_index).GetImage();

	if (!image)
	{
		throw std::logic_error("Item is not an image");
	}

	m_oldWidth = image->GetWidth();
	m_oldHeight = image->GetHeight();
	image->Resize(m_newWidth, m_newHeight);
}

void ResizeImageCommand::Revert()
{
	auto image = m_document.GetItem(m_index).GetImage();

	if (!image)
	{
		throw std::logic_error("Item is not an image");
	}

	image->Resize(m_oldWidth, m_oldHeight);
}