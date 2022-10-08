#include "pch.h"
#include "InputStream/FileInputStream.h"
#include "OutputStream/FileOutputStream.h"
#include "InputStream/DecryptionInputStream.h"
#include "OutputStream/EncryptionOutputStream.h"
#include "Cryptography/Cryptographer.h"
#include "InputStream/DecompressionInputStream.h"
#include "OutputStream/CompressionOutputStream.h"
#include <string>

const std::string TEST_FILES_DIRECTORY{ "Test files/" };
const std::string EMPTY_TEST_FILENAME{ TEST_FILES_DIRECTORY + "EmptyFileTest.txt" };
const std::string INPUT_STREAM_FILENAME{ TEST_FILES_DIRECTORY + "InputFileStreamTest.txt" };
const std::string OUTPUT_STREAM_FILENAME{ TEST_FILES_DIRECTORY + "OutputFileStreamTest.txt" };
const std::string DECRYPTION_OUTPUT_FILE{ TEST_FILES_DIRECTORY + "DecryptedFile.dat" };
const std::string COMPRESSION_OUTPUT_FILE{ TEST_FILES_DIRECTORY + "CompressedFile.dat" };

TEST(FileInputStreamTest, ReadingByteFromEmptyFile)
{
	FileInputStream file(EMPTY_TEST_FILENAME);
	uint8_t byte{ file.ReadByte() };

	EXPECT_EQ(byte, '\0');
	EXPECT_TRUE(file.IsEOF());
}

TEST(FileInputStreamTest, ReadingBlockFromEmptyFile)
{
	FileInputStream file(EMPTY_TEST_FILENAME);
	uint8_t* buffer = new uint8_t[10];
	std::streamsize bytesRead{ file.ReadBlock(buffer, 10) };

	EXPECT_EQ(bytesRead, 0);
	EXPECT_TRUE(file.IsEOF());

	delete[] buffer;
}

TEST(FileInputStreamTest, ReadingByteFromFile)
{
	FileInputStream file(INPUT_STREAM_FILENAME);
	uint8_t byte{ file.ReadByte() };

	EXPECT_EQ(byte, 'A');
	EXPECT_FALSE(file.IsEOF());
}

TEST(FileInputStreamTest, ReadingWholeFileByBlock)
{
	FileInputStream file(INPUT_STREAM_FILENAME);
	uint8_t* buffer = new uint8_t[3];
	std::streamsize bytesRead{ file.ReadBlock(buffer, 10) };

	EXPECT_EQ(bytesRead, 3);
	EXPECT_EQ(std::memcmp(buffer, "ABC", 3), 0);
	EXPECT_TRUE(file.IsEOF());

	delete[] buffer;
}

TEST(FileInputStreamTest, ReadingPartOfFileByBlock)
{
	FileInputStream file(INPUT_STREAM_FILENAME);
	uint8_t* buffer = new uint8_t[2];
	std::streamsize bytesRead{ file.ReadBlock(buffer, 2) };

	EXPECT_EQ(bytesRead, 2);
	EXPECT_EQ(std::memcmp(buffer, "AB", 2), 0);
	EXPECT_FALSE(file.IsEOF());

	delete[] buffer;
}

TEST(FileOutputStreamTest, WriteByte)
{
	FileOutputStream outFile(OUTPUT_STREAM_FILENAME);
	FileInputStream inFile(OUTPUT_STREAM_FILENAME);
	uint8_t byte;

	outFile.WriteByte('A');
	byte = inFile.ReadByte();

	EXPECT_EQ(byte, 'A');
}

TEST(FileOutputStreamTest, WriteBlock)
{
	FileOutputStream outFile(OUTPUT_STREAM_FILENAME);
	FileInputStream inFile(OUTPUT_STREAM_FILENAME);
	uint8_t* buffer = new uint8_t[10];
	const char* str = "ABC";

	outFile.WriteBlock(str, 3);
	inFile.ReadBlock(buffer, 3);

	EXPECT_EQ(std::memcmp(buffer, str, 3), 0);

	delete[] buffer;
}

TEST(EncryptionTest, EncryptAndDecryptWithTheSameKey)
{
	std::unique_ptr<IOutputStream> outStream = std::make_unique<EncryptionOutputStream>(
		std::make_unique<FileOutputStream>(DECRYPTION_OUTPUT_FILE), std::make_unique<Cryptographer>(3));
	std::unique_ptr<IInputStream> inStream = std::make_unique<DecryptionInputStream>(
		std::make_unique<FileInputStream>(DECRYPTION_OUTPUT_FILE), std::make_unique<Cryptographer>(3));
	const char* message = "This is my secret message...";
	uint8_t* buffer = new uint8_t[50];

	outStream->WriteBlock(message, 28);
	inStream->ReadBlock(buffer, 28);

	EXPECT_EQ(std::memcmp(buffer, message, 28), 0);

	delete[] buffer;
}

TEST(EncryptionTest, EncryptAndDecryptWithTheDifferentKeys)
{
	std::unique_ptr<IOutputStream> outStream = std::make_unique<EncryptionOutputStream>(
		std::make_unique<FileOutputStream>(DECRYPTION_OUTPUT_FILE), std::make_unique<Cryptographer>(3));
	std::unique_ptr<IInputStream> inStream = std::make_unique<DecryptionInputStream>(
		std::make_unique<FileInputStream>(DECRYPTION_OUTPUT_FILE), std::make_unique<Cryptographer>(6));
	const char* message = "This is my secret message...";
	uint8_t* buffer = new uint8_t[50];

	outStream->WriteBlock(message, 28);
	inStream->ReadBlock(buffer, 28);

	EXPECT_NE(std::memcmp(buffer, message, 28), 0);

	delete[] buffer;
}

TEST(CompressionTest, CompressAndDecompressData)
{
	std::unique_ptr<IOutputStream> outStream = std::make_unique<CompressionOutputStream>(
		std::make_unique<FileOutputStream>(COMPRESSION_OUTPUT_FILE));
	std::unique_ptr<IInputStream> inStream = std::make_unique<DecompressionInputStream>(
		std::make_unique<FileInputStream>(COMPRESSION_OUTPUT_FILE));
	const char* message = "This is my secret message...";
	uint8_t* buffer = new uint8_t[50];

	outStream->WriteBlock(message, 28);
	inStream->ReadBlock(buffer, 28);

	EXPECT_NE(std::memcmp(buffer, message, 28), 0);

	delete[] buffer;
}