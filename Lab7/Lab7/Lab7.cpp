#include "Canvas/ConsoleCanvas.h"
#include "Shape/Triangle.h"
#include <iostream>
#include <format>

int main()
{
	ConsoleCanvas canvas;
	Triangle triangle({ 2, 2 }, { 5, 0 }, { 5, 5 });

	triangle.GetOutlineStyle()->SetColor(0xDC143C);
	triangle.GetOutlineStyle()->SetLineWidth(2);
	triangle.GetFillStyle()->SetColor(0x761DCF);
	triangle.GetFillStyle()->Enable(false);

	triangle.Draw(canvas);

	FrameRect frame = triangle.GetFrame().value();

	std::cout << std::format("TopLeft: {} {}, width: {}, height: {}", 
		frame.topLeft.x, frame.topLeft.y, frame.width, frame.height);
	std::cout << std::endl;
	
	triangle.SetFrame({ { 2, 0 }, 3, 3 });

	frame = triangle.GetFrame().value();

	std::cout << std::format("TopLeft: {} {}, width: {}, height: {}",
		frame.topLeft.x, frame.topLeft.y, frame.width, frame.height);
}
