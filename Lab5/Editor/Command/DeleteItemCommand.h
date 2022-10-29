#pragma once
#include "IRevertableCommand.h"
#include "Document/IDocument.h"
#include <optional>

class DeleteItemCommand : public IRevertableCommand
{
public:
	DeleteItemCommand(IDocument& document, size_t index);

	void Execute() override;
	void Revert() override;

private:
	IDocument& m_document;
	size_t m_index;
	std::optional<DocumentItem> m_item;
};