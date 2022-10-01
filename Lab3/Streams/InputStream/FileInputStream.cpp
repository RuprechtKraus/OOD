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

std::uint8_t FileInputStream::ReadByte()
{
	uint8_t byte{ static_cast<uint8_t>(m_file.get()) };
	
	if (m_file.fail())
	{
		throw std::ios_base::failure("Read failure");
	}

	return byte;
}

std::streamsize FileInputStream::ReadBlock(void* dstBuffer, std::streamsize size)
{
	char* buffer = new char[size];
	m_file.read(buffer, size);

	if (m_file.fail() && m_file.gcount() == 0)
	{
		throw std::ios_base::failure("Read failure");
	}

	std::memcpy(dstBuffer, buffer, size);

	return m_file.gcount();
}

void FileInputStream::Close()
{
	m_file.close();
}