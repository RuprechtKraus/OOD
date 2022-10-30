#pragma once
#include "IResourceRepository.h"

class ResourceRepository : public IResourceRepository
{
public:
	ResourceRepository(const Path& path);

	Path AddResource(const Path& target) override;
	void DeleteResource(const std::string& name) override;
	Path GetResourcesPath() const override;

private:
	static std::string GenerateFileName(const std::string& extension);

	Path m_path;
};