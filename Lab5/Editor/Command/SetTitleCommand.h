#pragma once
#include "Document/IDocument.h"
#include "IRevertableCommand.h"
#include <string>

class SetTitleCommand : public IRevertableCommand
{
public:
	SetTitleCommand(IDocument& document, const std::string& text);

	void Execute() override;
	void Revert() override;

private:
	IDocument& m_document;
	std::string m_newTitle;
	std::string m_oldTitle;
};