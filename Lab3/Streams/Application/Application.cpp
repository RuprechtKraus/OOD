#include "Application.h"
#include "Compression/RLECompressor.h"
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

namespace
{
template <typename Wrapper, typename... Args>
decltype(auto) WrapStream(const Args&... args)
{
	return [=](auto&& stream) {
		return std::make_unique<Wrapper>(std::forward<decltype(stream)>(stream), args...);
	};
}

template <typename Stream, typename Wrapper>
decltype(auto) operator<<(Stream&& stream, const Wrapper& wrap)
{
	return wrap(std::forward<Stream>(stream));
}
} // namespace

Application::Application(int argc, char* argv[])
{
	SetupAppication(argc, argv);
}

void Application::Run()
{
	char* buffer = new char[8192];
	std::streamsize gcount{};
	
	gcount = m_inputStream->ReadBlock(buffer, 8192);
	buffer[gcount] = '\0';

	m_outputStream->WriteBlock(buffer, gcount);

	delete[] buffer;
}

void Application::SetupAppication(int argc, char* argv[])
{
	po::parsed_options options{ ParseOptions(argc, argv) };
	SetupStreams(options);
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

void Application::SetupStreams(const po::parsed_options& options)
{
	std::string inFileName;
	std::string outFileName;

	for (const auto& option : options.options)
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

	std::vector<std::pair<std::string, std::string>> inputWrappers;
	std::vector<std::pair<std::string, std::string>> outputWrappers;

	for (const auto& option : options.options)
	{
		if (option.string_key == "encrypt")
		{
			outputWrappers.push_back(std::pair("encrypt", option.value[0]));
		}

		if (option.string_key == "decrypt")
		{
			inputWrappers.push_back(std::pair("decrypt", option.value[0]));
		}

		if (option.string_key == "compress")
		{
			outputWrappers.push_back(std::pair("compress", ""));
		}

		if (option.string_key == "decompress")
		{
			inputWrappers.push_back(std::pair("decompress", ""));
		}
	}

	for (int i = outputWrappers.size() - 1; i >= 0; i--)
	{
		if (outputWrappers[i].first == "encrypt")
		{
			m_outputStream = std::make_unique<EncryptionOutputStream>(std::move(m_outputStream),
				std::make_unique<Cryptographer>(std::stoi(outputWrappers[i].second)));
		}

		if (outputWrappers[i].first == "compress")
		{
			m_outputStream = std::make_unique<CompressionOutputStream>(std::move(m_outputStream),
				std::make_unique<RLECompressor>());
		}
	}

	for (size_t i = 0; i < inputWrappers.size(); i++)
	{
		if (inputWrappers[i].first == "decrypt")
		{
			m_inputStream = std::make_unique<DecryptionInputStream>(std::move(m_inputStream),
				std::make_unique<Cryptographer>(std::stoi(inputWrappers[i].second)));
		}

		if (inputWrappers[i].first == "decompress")
		{
			m_inputStream = std::make_unique<DecompressionInputStream>(std::move(m_inputStream),
				std::make_unique<RLECompressor>());
		}
	}
}