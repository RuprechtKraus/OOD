#pragma once
#include "Compression/RLECompressor.h"
#include "IOutputStream.h"

class CompressionOutputStream : public IOutputStream
{
public:
	CompressionOutputStream(OutputStreamPtr&& stream, const ICompressor& compressor);

	void WriteByte(uint8_t data) override;
	void WriteBlock(const void* srcData, std::streamsize size) override;

private:
	OutputStreamPtr m_stream;
	const ICompressor& m_compressor;
};
