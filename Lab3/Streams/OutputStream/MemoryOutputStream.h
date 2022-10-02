#pragma once
#include "IOutputStream.h"
#include <vector>

class MemoryOutputStream : public IOutputStream
{
public:
	MemoryOutputStream(std::vector<uint8_t>& buffer);

	void WriteByte(uint8_t data) override;
	void WriteBlock(const void* srcData, std::streamsize size) override;

private:
	std::vector<uint8_t>& m_buffer;
};
