#include "InsertImageCommand.h"

namespace fs = std::filesystem;

InsertImageCommand::InsertImageCommand(
	IDocument& document,
	IResourceRepository& repository,
	const Path& path,
	int width,
	int height,
	std::optional<size_t> position)
	: m_document(document)
	, m_repository(repository)
	, m_sourcePath(path)
	, m_width(width)
	, m_height(height)
	, m_position(position)
{
}

void InsertImageCommand::Execute()
{
	m_resourcePath = m_repository.AddResource(m_sourcePath);
	m_document.InsertImage(m_resourcePath, m_width, m_height, m_position);
}

void InsertImageCommand::Revert()
{
	m_document.DeleteItem(m_position.value_or(m_document.GetItemsCount() - 1));
}