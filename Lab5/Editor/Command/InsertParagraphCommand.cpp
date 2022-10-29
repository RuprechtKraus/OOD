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

// TODO: Добавить отмену вставки параграфа
void InsertParagraphCommand::Revert()
{
	throw std::logic_error("Method is not implemented");
}