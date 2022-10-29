#pragma once
#include <filesystem>
#include <string>

using Path = std::filesystem::path;

class IResourceRepository
{
public:
	//Делает копию файла и сохраняет ее в папке с ресурсами с новым именем.
	//Возвращает новое имя файла
	virtual Path AddResource(const Path& target) = 0;

	//Удаляет ресурс из папки с ресурсами
	virtual void DeleteResource(const std::string& target) = 0;

	//Возвращает путь к папке с ресурсами
	virtual Path GetResourcesPath() const = 0;
};