#include "Canvas/ConsoleCanvas.h"
#include "Shape/Triangle.h"
#include "Shape/Rectangle.h"
#include "Shape/Ellipse.h"
#include <iostream>
#include <format>

int main()
{
	ConsoleCanvas canvas;
	Ellipse ellipse({ 3, 3 }, 1, 3);

	ellipse.GetOutlineStyle()->SetColor(0xDC143C);
	ellipse.GetOutlineStyle()->SetLineWidth(2);
	ellipse.GetFillStyle()->SetColor(0x761DCF);

	ellipse.Draw(canvas);

	FrameRect frame = ellipse.GetFrame().value();

	std::cout << std::format("TopLeft: {} {}, width: {}, height: {}", 
		frame.topLeft.x, frame.topLeft.y, frame.width, frame.height);
	std::cout << std::endl;
	
	ellipse.SetFrame({ { 1, 2 }, 2, 2 });

	frame = ellipse.GetFrame().value();

	std::cout << std::format("TopLeft: {} {}, width: {}, height: {}",
		frame.topLeft.x, frame.topLeft.y, frame.width, frame.height);
}
