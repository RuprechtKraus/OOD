#pragma once
#include "Document/IDocument.h"
#include "IRevertableCommand.h"

class InsertParagraphCommand : public IRevertableCommand
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