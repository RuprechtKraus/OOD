#include "Document.h"
#include "Elements/Image.h"
#include "Elements/Paragraph.h"
#include <assert.h>

std::shared_ptr<IParagraph> Document::InsertParagraph(const std::string& text,
	std::optional<size_t> position)
{
	auto paragraph = std::make_shared<Paragraph>(text);
	InsertItem(DocumentItem(paragraph), position);

	return paragraph;
}

std::shared_ptr<IImage> Document::InsertImage(const Path& path, int width, int height,
	std::optional<size_t> position)
{
	auto image = std::make_shared<Image>(path, width, height);
	InsertItem(DocumentItem(image), position);

	return image;
}

void Document::InsertItem(DocumentItem&& item, std::optional<size_t> position)
{
	if (position)
	{
		assert(position.value() < m_items.size());
		m_items.insert(m_items.begin() + position.value(), item);
	}
	else
	{
		m_items.push_back(item);
	}
}

size_t Document::GetItemsCount() const noexcept
{
	return m_items.size();
}

ConstDocumentItem Document::GetItem(size_t index) const
{
	assert(index < m_items.size());
	return m_items[index];
}

DocumentItem Document::GetItem(size_t index)
{
	assert(index < m_items.size());
	return m_items[index];
}

void Document::DeleteItem(size_t index)
{
	assert(index < m_items.size());
	m_items.erase(m_items.begin() + index);
}

std::string Document::GetTitle() const
{
	return m_title;
}

void Document::SetTitle(const std::string& title)
{
	m_title = title;
}

bool Document::CanUndo() const
{
	throw std::logic_error("Method is not implemented");
}

void Document::Undo()
{
	throw std::logic_error("Method is not implemented");
}

bool Document::CanRedo() const
{
	throw std::logic_error("Method is not implemented");
}

void Document::Redo()
{
	throw std::logic_error("Method is not implemented");
}

void Document::Save(const Path& path) const
{
	throw std::logic_error("Method is not implemented");
}