#include "Application.h"
#include "Cryptography/Cryptographer.h"
#include "InputStream/DecompressionInputStream.h"
#include "InputStream/DecryptionInputStream.h"
#include "InputStream/FileInputStream.h"
#include "InputStream/MemoryInputStream.h"
#include "OutputStream/CompressionOutputStream.h"
#include "OutputStream/EncryptionOutputStream.h"
#include "OutputStream/FileOutputStream.h"
#include "OutputStream/MemoryOutputStream.h"
#include <string>

Application::Application(int argc, char* argv[])
	: m_options(ParseOptions(argc, argv))
{
	SetUpAppication(argc, argv);
}

void Application::Run()
{
	while (true)
	{
		uint8_t byte = m_inputStream->ReadByte();

		if (m_inputStream->IsEOF())
		{
			break;
		}

		m_outputStream->WriteByte(byte);
	}
}

void Application::SetUpAppication(int argc, char* argv[])
{
	InitStreams();
	SetUpStreams();
}

po::parsed_options Application::ParseOptions(int argc, char* argv[])
{
	po::options_description desc;

	desc.add_options()("encrypt", po::value<int>())("decrypt", po::value<int>());
	desc.add_options()("compress", "Add compression step")("decompress", "Add decompression step");
	desc.add_options()("input",
		po::value<std::string>()->required(), "Set input file")("output",
		po::value<std::string>()->required(), "Set output file");

	return po::parse_command_line(argc, argv, desc);
}

void Application::SetUpStreams()
{
	WrappingParams inputWrapParams;
	WrappingParams outputWrapParams;

	SetWrappersParams(inputWrapParams, outputWrapParams);
	WrapInputStream(inputWrapParams);
	WrapOutputStream(outputWrapParams);
}

void Application::InitStreams()
{
	std::string inFileName;
	std::string outFileName;

	for (const auto& option : m_options.options)
	{
		if (option.string_key == "input")
		{
			inFileName = option.value[0];
		}
		else if (option.string_key == "output")
		{
			outFileName = option.value[0];
		}
	}

	m_inputStream = std::make_unique<FileInputStream>(inFileName);
	m_outputStream = std::make_unique<FileOutputStream>(outFileName);
}

void Application::SetWrappersParams(WrappingParams& inputWrapParams, WrappingParams& outputWrapParams)
{
	for (const auto& option : m_options.options)
	{
		if (option.string_key == "encrypt")
		{
			outputWrapParams.push_back(std::pair("encrypt", option.value[0]));
		}

		if (option.string_key == "decrypt")
		{
			inputWrapParams.push_back(std::pair("decrypt", option.value[0]));
		}

		if (option.string_key == "compress")
		{
			outputWrapParams.push_back(std::pair("compress", ""));
		}

		if (option.string_key == "decompress")
		{
			inputWrapParams.push_back(std::pair("decompress", ""));
		}
	}
}

void Application::WrapInputStream(const WrappingParams& inputWrapParams)
{
	for (size_t i = 0; i < inputWrapParams.size(); i++)
	{
		if (inputWrapParams[i].first == "decrypt")
		{
			m_inputStream = std::make_unique<DecryptionInputStream>(std::move(m_inputStream),
				std::make_unique<Cryptographer>(std::stoi(inputWrapParams[i].second)));
		}

		if (inputWrapParams[i].first == "decompress")
		{
			m_inputStream = std::make_unique<DecompressionInputStream>(std::move(m_inputStream));
		}
	}
}

void Application::WrapOutputStream(const WrappingParams& outputWrapParams)
{
	for (int i = outputWrapParams.size() - 1; i >= 0; i--)
	{
		if (outputWrapParams[i].first == "encrypt")
		{
			m_outputStream = std::make_unique<EncryptionOutputStream>(std::move(m_outputStream),
				std::make_unique<Cryptographer>(std::stoi(outputWrapParams[i].second)));
		}

		if (outputWrapParams[i].first == "compress")
		{
			m_outputStream = std::make_unique<CompressionOutputStream>(std::move(m_outputStream));
		}
	}
}