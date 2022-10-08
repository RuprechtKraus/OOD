#pragma once
#include "InputStream/IInputStream.h"
#include "OutputStream/IOutputStream.h"
#include "boost/program_options.hpp"

namespace po = boost::program_options;

class Application
{
private:
	using WrappingParams = std::vector<std::pair<std::string, std::string>>;

public:
	Application(int argc, char* argv[]);
	void Run();

private:
	void SetUpAppication(int argc, char* argv[]);
	po::parsed_options ParseOptions(int argc, char* argv[]);
	void InitStreams();
	void SetUpStreams();
	void SetWrappersParams(WrappingParams& inputWrapParams, WrappingParams& outputWrapParams);
	void WrapInputStream(const WrappingParams& inputWrapParams);
	void WrapOutputStream(const WrappingParams& outputWrapParams);

	InputStreamPtr m_inputStream;
	OutputStreamPtr m_outputStream;
	po::parsed_options m_options;
};