#include "FileOutputStream.h"

FileOutputStream::FileOutputStream(const std::string& filename)
{
	m_file.open(filename, std::ios::out | std::ios::binary);

	if (!m_file.is_open())
	{
		throw std::runtime_error("Cannot open file " + filename);
	}
}

FileOutputStream::~FileOutputStream()
{
	Close();
}

void FileOutputStream::WriteByte(uint8_t data)
{
	m_file.write((char*)&data, sizeof(data));

	if (m_file.fail())
	{
		throw std::ios_base::failure("Write failure");
	}

	m_file.flush();
}

void FileOutputStream::WriteBlock(const void* srcData, std::streamsize size)
{
	m_file.write(static_cast<const char*>(srcData), size);

	if (m_file.fail())
	{
		throw std::ios_base::failure("Write failure");
	}

	m_file.flush();
}

void FileOutputStream::Close()
{
	m_file.close();
}