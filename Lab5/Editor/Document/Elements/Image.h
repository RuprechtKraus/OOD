#pragma once
#include "IImage.h"

class Image : public IImage
{
public:
	Image(const Path& path, int width, int height);

	Path GetPath() const override;
	int GetWidth() const noexcept override;
	int GetHeight() const noexcept override;
	void Resize(int width, int height) noexcept override;

private:
	Path m_path;
	int m_width;
	int m_height;
};