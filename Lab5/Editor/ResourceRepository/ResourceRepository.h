#pragma once
#include "IResourceRepository.h"
#include <unordered_map>

class ResourceRepository : public IResourceRepository
{
public:
	ResourceRepository(const Path& path);
	~ResourceRepository() override;

	Path AddResource(const Path& target) override;
	void DeleteResource(const std::string& name) override;
	Path GetResourcesPath() const override;

private:
	Path m_path;
	std::unordered_map<Path, Path> m_resourceSource;
};