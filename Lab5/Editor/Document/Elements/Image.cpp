#include "Image.h"

Image::Image(const Path& path, int width, int height)
	: m_path(path)
	, m_width(width)
	, m_height(height)
{
}

Path Image::GetPath() const
{
	return m_path;
}

int Image::GetWidth() const noexcept
{
	return m_width;
}

int Image::GetHeight() const noexcept
{
	return m_height;
}

void Image::Resize(int width, int height) noexcept
{
	m_width = width;
	m_height = height;
}