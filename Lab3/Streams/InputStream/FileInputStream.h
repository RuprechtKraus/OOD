#pragma once
#include "IInputStream.h"
#include <fstream>
#include <string>

class FileInputStream : public IInputStream
{
public:
	FileInputStream(const std::string& filename);
	~FileInputStream() override;

	bool IsEOF() const override;
	uint8_t ReadByte() override;
	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override;
	void Close();

private:
	std::ifstream m_file;
};