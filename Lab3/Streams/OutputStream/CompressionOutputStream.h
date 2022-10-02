#pragma once
#include "Compression/RLECompressor.h"
#include "IOutputStream.h"

class CompressionOutputStream : public IOutputStream
{
public:
	CompressionOutputStream(OutputStreamPtr&& stream, std::unique_ptr<ICompressor>&& compressor);

	void WriteByte(uint8_t data) override;
	void WriteBlock(const void* srcData, std::streamsize size) override;

private:
	OutputStreamPtr m_stream;
	std::unique_ptr<ICompressor> m_compressor;
};
