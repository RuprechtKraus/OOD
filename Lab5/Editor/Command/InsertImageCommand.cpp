#include "InsertImageCommand.h"

InsertImageCommand::InsertImageCommand(
	IDocument& document,
	IResourceRepository& repository,
	const Path& path,
	int width,
	int height,
	std::optional<size_t> position)
	: m_document(document)
	, m_repository(repository)
	, m_path(path)
	, m_width(width)
	, m_height(height)
	, m_position(position)
{
}

void InsertImageCommand::Execute()
{
	Path imagePath = m_repository.AddResource(m_path);
	m_name = imagePath.filename().string();

	m_document.InsertImage(imagePath, m_width, m_height, m_position);
}

void InsertImageCommand::Revert()
{
	throw std::logic_error("Method is not implemented");
}