#include "ResourceRepository.h"

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
	std::string filename = GenerateFileName(extension.string());
	Path resourcePath = m_path.string() + filename;
	fs::copy_file(target, resourcePath);

	return resourcePath;
}

void ResourceRepository::DeleteResource(const std::string& target)
{
	Path path = m_path.string() + target;
	fs::remove(path);
}

Path ResourceRepository::GetResourcesPath() const
{
	return m_path;
}

std::string ResourceRepository::GenerateFileName(const std::string& extension)
{
	char buffer[L_tmpnam];
	tmpnam_s(buffer, L_tmpnam);

	return Path(buffer).filename().replace_extension(extension).string();
}
