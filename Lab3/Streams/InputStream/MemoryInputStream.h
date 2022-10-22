#pragma once
#include "IInputStream.h"
#include <vector>

class MemoryInputStream : public IInputStream
{
public:
	MemoryInputStream(std::vector<uint8_t>& buffer);

	bool IsEOF() const override;
	std::uint8_t ReadByte() override;
	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override;

private:
	std::vector<uint8_t>& m_buffer;
	size_t m_position{ 0 };
};
