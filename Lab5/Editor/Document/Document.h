#pragma once
#include "IDocument.h"
#include "CommandHistory/ICommandHistory.h"
#include <vector>

class Document : public IDocument
{
public:
	Document(ICommandHistory& history);

	std::shared_ptr<IParagraph> InsertParagraph(const std::string& text,
		std::optional<size_t> position = std::nullopt) override;
	std::shared_ptr<IImage> InsertImage(const Path& path, int width, int height,
		std::optional<size_t> position = std::nullopt) override;

	size_t GetItemsCount() const noexcept override;

	ConstDocumentItem GetItem(size_t index) const override;
	DocumentItem GetItem(size_t index) override;
	void DeleteItem(size_t index) override;

	std::string GetTitle() const override;
	void SetTitle(const std::string& title) override;

	bool CanUndo() const noexcept override;
	void Undo() override;
	bool CanRedo() const noexcept override;
	void Redo() override;

	void Save(const Path& path) const override;

private:
	void InsertItem(DocumentItem&& item, std::optional<size_t> position);

	ICommandHistory& m_history;
	std::vector<DocumentItem> m_items;
	std::string m_title;
};