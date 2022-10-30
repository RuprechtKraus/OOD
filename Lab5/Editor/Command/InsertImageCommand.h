#pragma once
#include "Document/Document.h"
#include "IRevertableCommand.h"
#include "ResourceRepository/IResourceRepository.h"

class InsertImageCommand : public IRevertableCommand
{
public:
	InsertImageCommand(
		IDocument& document,
		IResourceRepository& repository,
		const Path& path,
		int width,
		int height,
		std::optional<size_t> position = std::nullopt);

	void Execute() override;
	void Revert() override;

	~InsertImageCommand() override;

private:
	IDocument& m_document;
	IResourceRepository& m_repository;
	Path m_resourcePath;
	Path m_sourcePath;
	int m_width;
	int m_height;
	std::optional<size_t> m_position;
};