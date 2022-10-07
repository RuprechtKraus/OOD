#pragma once
#include "IInputStream.h"
#include <queue>

class DecompressionInputStream : public IInputStream
{
private:
	struct Block
	{
		uint8_t byte;
		int count;
	};

public:
	DecompressionInputStream(InputStreamPtr&& stream);

	bool IsEOF() const override;
	std::uint8_t ReadByte() override;
	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override;

private:
	InputStreamPtr m_stream;
	Block m_block{};
};
