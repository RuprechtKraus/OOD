#include "ResourceRepository.h"
#include "Filesystem/FilenameGenerator.h"

namespace fs = std::filesystem;

ResourceRepository::ResourceRepository(const Path& path)
	: m_path(path)
{
	if (!m_path.string().ends_with('\\'))
	{
		m_path += "\\";
	}

	fs::create_directories(m_path);
}

Path ResourceRepository::AddResource(const Path& target)
{
	auto extension = target.extension();
	Path filename = GetRandomFilename(extension);
	Path resourcePath = m_path.string() + filename.string();
	fs::copy_file(target, resourcePath);

	return resourcePath;
}

void ResourceRepository::DeleteResource(const std::string& name)
{
	Path path = m_path.string() + name;
	fs::remove(path);
}

Path ResourceRepository::GetResourcesPath() const
{
	return m_path;
}
