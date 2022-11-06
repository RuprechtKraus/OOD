#pragma once
#include <filesystem>
#include <string>

using Path = std::filesystem::path;

class IResourceRepository
{
public:
	//Делает копию файла и сохраняет ее в папке с ресурсами с новым именем.
	//Если файл уже существует то сразу возвращает его имя в папке с ресурсами
	//Возвращает новое имя файла
	virtual Path AddResource(const Path& target) = 0;

	//Удаляет ресурс из папки с ресурсами
	virtual void DeleteResource(const std::string& name) = 0;

	//Возвращает путь к папке с ресурсами
	virtual Path GetResourcesPath() const = 0;

	virtual ~IResourceRepository() = default;
};