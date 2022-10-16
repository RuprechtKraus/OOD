#pragma once
#include <string>

class Application
{
public:
	Application(const std::string& inputFilename);
	void Run();

private:
	std::string m_inputFilename;
};
