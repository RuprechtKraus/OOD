#pragma once
#include "InputStream/IInputStream.h"
#include "OutputStream/IOutputStream.h"
#include "boost/program_options.hpp"

namespace po = boost::program_options;

class Application
{
public:
	Application(int argc, char* argv[]);
	void Run();

private:
	void SetupAppication(int argc, char* argv[]);
	po::parsed_options ParseOptions(int argc, char* argv[]);
	void SetupStreams(const po::parsed_options& options);

	InputStreamPtr m_inputStream;
	OutputStreamPtr m_outputStream;
};