#include "ModernGraphicsLib/ModernGraphicsLib.h"
#include "ModernGraphicsLibAdapter/ModernGraphicsRendererAdapter.h"
#include "ShapeDrawingLib/ShapeDrawingLib.h"
#include <iostream>

// Пространство имен приложения (доступно для модификации)
namespace app
{
void PaintPicture(shape_drawing_lib::CanvasPainter& painter)
{
	using namespace shape_drawing_lib;

	Triangle triangle({ 10, 15 }, { 100, 200 }, { 150, 250 });
	Rectangle rectangle({ 30, 40 }, 18, 24);

	painter.Draw(triangle);
	painter.Draw(rectangle);
}

void PaintPictureOnCanvas()
{
	graphics_lib::Canvas simpleCanvas;
	shape_drawing_lib::CanvasPainter painter(simpleCanvas);
	PaintPicture(painter);
}

void PaintPictureOnModernGraphicsRenderer()
{
	ModernGraphicsRendererAdapter rendererAdapter(std::cout);
	shape_drawing_lib::CanvasPainter painter(rendererAdapter);
	PaintPicture(painter);
}
} // namespace app

int main()
{
	std::cout << "Should we use new API (y)?";
	std::string userInput;

	if (std::getline(std::cin, userInput) && (userInput == "y" || userInput == "Y"))
	{
		app::PaintPictureOnModernGraphicsRenderer();
	}
	else
	{
		app::PaintPictureOnCanvas();
	}
}
