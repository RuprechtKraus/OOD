#pragma once
#include "IOutputStream.h"

class CompressionOutputStream : public IOutputStream
{
public:
	CompressionOutputStream(OutputStreamPtr&& stream);

	void WriteBlock(const void* srcData, std::streamsize size) override;
	void WriteByte(uint8_t data) override;

private:
	std::string Compress(const void* srcData, std::streamsize size);
	std::string MakeByteInfo(uint8_t byte, size_t count);

	OutputStreamPtr m_stream;
};
