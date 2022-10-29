#pragma once
#include "Document/IDocument.h"
#include "IRevertableCommand.h"

class ReplaceTextCommand : IRevertableCommand
{
public:
	ReplaceTextCommand(
		IDocument& document, 
		const std::string& text, 
		size_t index);

	void Execute() override;
	void Revert() override;

private:
	IDocument& m_document;
	std::string m_newText;
	std::string m_oldText;
	size_t m_index;
};