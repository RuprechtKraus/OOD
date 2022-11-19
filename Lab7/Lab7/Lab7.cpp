#include "Canvas/ConsoleCanvas.h"
#include "Shape/Triangle.h"
#include "Shape/Rectangle.h"
#include <iostream>
#include <format>

int main()
{
	ConsoleCanvas canvas;
	Rectangle rectangle({ 2, 2 }, 4, 4);

	rectangle.GetOutlineStyle()->SetColor(0xDC143C);
	rectangle.GetOutlineStyle()->SetLineWidth(2);
	rectangle.GetFillStyle()->SetColor(0x761DCF);

	rectangle.Draw(canvas);

	FrameRect frame = rectangle.GetFrame().value();

	std::cout << std::format("TopLeft: {} {}, width: {}, height: {}", 
		frame.topLeft.x, frame.topLeft.y, frame.width, frame.height);
	std::cout << std::endl;
	
	rectangle.SetFrame({ { 1, 1 }, 3, 6 });

	frame = rectangle.GetFrame().value();

	std::cout << std::format("TopLeft: {} {}, width: {}, height: {}",
		frame.topLeft.x, frame.topLeft.y, frame.width, frame.height);
}
