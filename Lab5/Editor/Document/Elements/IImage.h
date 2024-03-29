#pragma once
#include <filesystem>

using Path = std::filesystem::path;

class IImage
{
public:
	// Возвращает путь относительно каталога документа
	virtual Path GetPath() const = 0;

	virtual int GetWidth() const = 0;
	virtual int GetHeight() const = 0;
	virtual void Resize(int width, int height) = 0;

	virtual ~IImage() = default;
};
