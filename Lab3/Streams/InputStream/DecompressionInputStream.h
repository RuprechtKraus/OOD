#pragma once
#include "IInputStream.h"
#include "Compression/ICompressor.h"

class DecompressionInputStream : public IInputStream
{
public:
	DecompressionInputStream(InputStreamPtr&& stream, const ICompressor& compressor);

	bool IsEOF() const override;
	std::uint8_t ReadByte() override;
	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override;

private:
	InputStreamPtr m_stream;
	const ICompressor& m_compressor;
};
