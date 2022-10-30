#include "InsertParagraphCommand.h"

InsertParagraphCommand::InsertParagraphCommand(
	IDocument& document,
	const std::string& text,
	const std::optional<size_t> position)
	: m_document(document)
	, m_text(text)
	, m_position(position)
{
}

void InsertParagraphCommand::Execute()
{
	m_document.InsertParagraph(m_text, m_position);
}

void InsertParagraphCommand::Revert()
{
	m_document.DeleteItem(m_position.value_or(m_document.GetItemsCount() - 1));
}