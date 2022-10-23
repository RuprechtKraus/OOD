#pragma once
#include "Painter/Painter.h"
#include "Shapes/PictureDraft.h"
#include <string>

class Application
{
public:
	Application(const std::string& inputFilename);
	void Run();

private:
	static void VisualizeDraftUsingStreamCanvas(const PictureDraft& draft);
	static void VisualizeDraftUsingSfmlCanvas(const PictureDraft& draft);

	std::string m_inputFilename;
};
