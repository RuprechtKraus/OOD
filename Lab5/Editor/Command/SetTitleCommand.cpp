#include "SetTitleCommand.h"

SetTitleCommand::SetTitleCommand(IDocument& document, const std::string& text)
	: m_document(document)
	, m_newTitle(text)
{
}

void SetTitleCommand::Execute()
{
	m_oldTitle = m_document.GetTitle();
	m_document.SetTitle(m_newTitle);
}

void SetTitleCommand::Revert()
{
	m_document.SetTitle(m_oldTitle);
}