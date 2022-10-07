#pragma once
#include "IOutputStream.h"

class CompressionOutputStream : public IOutputStream
{
private:
	struct Block
	{
		uint8_t byte;
		int count;
	};

public:
	CompressionOutputStream(OutputStreamPtr&& stream);
	~CompressionOutputStream() override;

	void WriteBlock(const void* srcData, std::streamsize size) override;
	void WriteByte(uint8_t data) override;

private:
	void Flush();

	OutputStreamPtr m_stream;
	Block m_block{};
};
