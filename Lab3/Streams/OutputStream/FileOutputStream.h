#pragma once
#include "IOutputStream.h"
#include <fstream>

class FileOutputStream : public IOutputStream
{
public:
	FileOutputStream(const std::string& filename);
	~FileOutputStream() override;

	void WriteByte(uint8_t data) override;
	void WriteBlock(const void* srcData, std::streamsize size) override;
	void Close();

private:
	std::ofstream m_file;
};