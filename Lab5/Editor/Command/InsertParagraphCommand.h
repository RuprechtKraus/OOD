#pragma once
#include "Document/IDocument.h"
#include "ICommand.h"

class InsertParagraphCommand : public ICommand
{
public:
	InsertParagraphCommand(
		IDocument& document, 
		const std::string& text, 
		const std::optional<size_t> position = std::nullopt);

	void Execute() override;
	void Revert() override;

private:
	IDocument& m_document;
	std::string m_text;
	std::optional<size_t> m_position;
};