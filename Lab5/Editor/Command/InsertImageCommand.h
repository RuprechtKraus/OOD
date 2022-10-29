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

private:
	IDocument& m_document;
	IResourceRepository& m_repository;
	std::string m_name;
	Path m_path;
	int m_width;
	int m_height;
	std::optional<size_t> m_position;
};