#include "DeleteItemCommand.h"

DeleteItemCommand::DeleteItemCommand(IDocument& document, size_t index)
	: m_document(document)
	, m_index(index)
{
}

void DeleteItemCommand::Execute()
{
	m_item = m_document.GetItem(m_index);
	m_document.DeleteItem(m_index);
}

void DeleteItemCommand::Revert()
{
	auto& item = m_item.value();

	if (item.GetImage())
	{
		auto image = item.GetImage();
		m_document.InsertImage(image->GetPath(), image->GetWidth(), image->GetHeight(), m_index);
	}
	else
	{
		auto paragraph = item.GetParagraph();
		m_document.InsertParagraph(paragraph->GetText(), m_index);
	}
}
