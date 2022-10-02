#pragma once
#include "IInputStream.h"
#include "Compression/ICompressor.h"

class DecompressionInputStream : public IInputStream
{
public:
	DecompressionInputStream(InputStreamPtr&& stream, std::unique_ptr<ICompressor>&& compressor);

	bool IsEOF() const override;
	std::uint8_t ReadByte() override;
	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override;

private:
	InputStreamPtr m_stream;
	std::unique_ptr<ICompressor> m_compressor;
};
