#include <iostream>
#include "Canvas/ConsoleCanvas.h"

int main()
{
	ConsoleCanvas canvas;

	canvas.SetFillColor(0x761DCF);
	canvas.SetLineColor(0xDC143C);
	canvas.SetLineWidth(2);

	canvas.DrawEllipse({ 10, 10 }, 3, 6);
}
