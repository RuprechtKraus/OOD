#include "pch.h"
#include "InputStream/FileInputStream.h"
#include "OutputStream/FileOutputStream.h"
#include <string>

const std::string TEST_FILES_DIRECTORY{ "Test files/" };
const std::string EMPTY_TEST_FILENAME{ TEST_FILES_DIRECTORY + "EmptyFileTest.txt" };
const std::string INPUT_STREAM_FILENAME{ TEST_FILES_DIRECTORY + "InputFileStreamTest.txt" };
const std::string OUTPUT_STREAM_FILENAME{ TEST_FILES_DIRECTORY + "OutputFileStreamTest.txt" };

TEST(FileInputStreamTest, OpeningNotExistingFile)
{
	EXPECT_THROW(FileInputStream stream("MissingFile.txt"), std::runtime_error);
}

TEST(FileInputStreamTest, ReadingByOneByte)
{
	FileInputStream stream(INPUT_STREAM_FILENAME);
	uint8_t byte1{ stream.ReadByte() };
	uint8_t byte2{ stream.ReadByte() };
	uint8_t byte3{ stream.ReadByte() };

	EXPECT_EQ(byte1, 'A');
	EXPECT_EQ(byte2, 'B');
	EXPECT_EQ(byte3, 'C');
	EXPECT_FALSE(stream.IsEOF());
}

TEST(FileInputStreamTest, ReadingByteAfterLastSymbol)
{
	FileInputStream stream(INPUT_STREAM_FILENAME);

	stream.ReadByte();
	stream.ReadByte();
	stream.ReadByte();
	stream.ReadByte();

	EXPECT_TRUE(stream.IsEOF());
}

TEST(FileInputStreamTest, ReadingByteFromEmptyFile)
{
	FileInputStream stream(EMPTY_TEST_FILENAME);
	stream.ReadByte();

	EXPECT_TRUE(stream.IsEOF());
}

TEST(FileInputStreamTest, ReadingBlock)
{
	FileInputStream stream(INPUT_STREAM_FILENAME);
	char* buffer = new char[3];
	std::streamsize bytesCount = stream.ReadBlock(buffer, 3);

	EXPECT_EQ(bytesCount, 3);
	EXPECT_EQ(buffer[0], 'A');
	EXPECT_EQ(buffer[1], 'B');
	EXPECT_EQ(buffer[2], 'C');
	EXPECT_FALSE(stream.IsEOF());

	delete[] buffer;
}

TEST(FileInputStreamTest, ReadingBlockBiggerThanFile)
{
	FileInputStream stream(INPUT_STREAM_FILENAME);
	char* buffer = new char[5];
	std::streamsize bytesCount = stream.ReadBlock(buffer, 5);

	EXPECT_EQ(bytesCount, 3);
	EXPECT_EQ(buffer[0], 'A');
	EXPECT_EQ(buffer[1], 'B');
	EXPECT_EQ(buffer[2], 'C');
	EXPECT_TRUE(stream.IsEOF());

	delete[] buffer;
}

TEST(FileInputStreamTest, ReadingBlockFromEmptyFile)
{
	FileInputStream stream(EMPTY_TEST_FILENAME);
	char* buffer = new char[3];

	stream.ReadBlock(buffer, 3);

	EXPECT_TRUE(stream.IsEOF());

	delete[] buffer;
}

TEST(FileOutputStreamTest, WritingByByte)
{
	FileOutputStream outStream(OUTPUT_STREAM_FILENAME);

	outStream.WriteByte('A');
	outStream.WriteByte('B');
	outStream.WriteByte('C');
	outStream.Close();

	std::ifstream inStream(OUTPUT_STREAM_FILENAME);

	EXPECT_EQ(inStream.get(), 'A');
	EXPECT_EQ(inStream.get(), 'B');
	EXPECT_EQ(inStream.get(), 'C');
}

TEST(FileOutputStreamTest, WritingBlock)
{
	FileOutputStream outStream(OUTPUT_STREAM_FILENAME);
	const char* content = "ABC";

	outStream.WriteBlock(content, 3);
	outStream.Close();

	std::ifstream inStream(OUTPUT_STREAM_FILENAME);
	char* buffer = new char[3];

	inStream.read(buffer, 3);

	EXPECT_EQ(buffer[0], 'A');
	EXPECT_EQ(buffer[1], 'B');
	EXPECT_EQ(buffer[2], 'C');

	delete[] buffer;
}