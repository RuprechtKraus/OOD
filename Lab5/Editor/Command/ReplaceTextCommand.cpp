#include "ReplaceTextCommand.h"

ReplaceTextCommand::ReplaceTextCommand(
	IDocument& document,
	const std::string& text,
	size_t index)
	: m_document(document)
	, m_newText(text)
	, m_index(index)
{
}

void ReplaceTextCommand::Execute()
{
	auto paragraph = m_document.GetItem(m_index).GetParagraph();

	if (!paragraph)
	{
		throw std::logic_error("Item is not a paragraph");
	}

	m_oldText = paragraph->GetText();
	paragraph->SetText(m_newText);
}

void ReplaceTextCommand::Revert()
{
	auto paragraph = m_document.GetItem(m_index).GetParagraph();

	if (!paragraph)
	{
		throw std::logic_error("Item is not a paragraph");
	}

	paragraph->SetText(m_oldText);
}