#include "FileInputStream.h"

FileInputStream::FileInputStream(const std::string& filename)
{
	m_file.open(filename, std::ios::in | std::ios::binary);

	if (!m_file.is_open())
	{
		throw std::runtime_error("Cannot open file " + filename);
	}
}

FileInputStream::~FileInputStream()
{
	Close();
}

bool FileInputStream::IsEOF() const
{
	return m_file.eof();
}

uint8_t FileInputStream::ReadByte()
{
	uint8_t byte{};

	m_file.read((char*)&byte, sizeof(uint8_t));

	if (m_file.fail() && !m_file.eof())
	{
		throw std::ios_base::failure("Read failure");
	}

	return byte;
}

std::streamsize FileInputStream::ReadBlock(void* dstBuffer, std::streamsize size)
{
	m_file.read(static_cast<char*>(dstBuffer), size);

	if (m_file.fail() && !m_file.eof())
	{
		throw std::ios_base::failure("Read failure");
	}

	return m_file.gcount();
}

void FileInputStream::Close()
{
	m_file.close();
}