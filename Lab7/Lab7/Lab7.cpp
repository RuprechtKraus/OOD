#include "Canvas/ConsoleCanvas.h"
#include "Shape/Ellipse.h"
#include "Shape/Group/ShapeGroup.h"
#include "Shape/Rectangle.h"
#include "Shape/Triangle.h"
#include <format>
#include <iostream>

int main()
try
{
	ConsoleCanvas canvas;

	std::shared_ptr<IShape> triangle1 = std::make_shared<Triangle>(Point{ 1, 6 }, Point{ 4, 3 }, Point{ 4, 6 });
	triangle1->GetOutlineStyle()->SetColor(0xDC143C);
	triangle1->GetOutlineStyle()->SetLineWidth(2);
	triangle1->GetFillStyle()->SetColor(0x761DCF);

	std::shared_ptr<IShape> triangle2 = std::make_shared<Triangle>(Point{ 3, 1 }, Point{ 6, 4 }, Point{ 3, 7 });
	triangle2->GetOutlineStyle()->SetColor(0xDC143C);
	triangle2->GetFillStyle()->Enable(false);

	std::shared_ptr<IShape> triangle3 = std::make_shared<Triangle>(Point{ 3, 1 }, Point{ 6, 4 }, Point{ 3, 7 });
	triangle3->GetOutlineStyle()->SetColor(0xFF0000);
	triangle3->GetFillStyle()->Enable(true);

	std::shared_ptr<IShapeGroup> group = std::make_shared<ShapeGroup>();
	group->InsertShape(triangle1);
	group->InsertShape(triangle2);
	group->InsertShape(triangle3);

	std::shared_ptr<IShape> ellipse = std::make_shared<Ellipse>(Point{ 3, 4 }, 1, 1);
	ellipse->GetOutlineStyle()->Enable(false);
	ellipse->GetFillStyle()->SetColor(0xABCDFAF);

	std::shared_ptr<IShapeGroup> group2 = std::make_shared<ShapeGroup>();
	group2->InsertShape(group);
	group2->InsertShape(ellipse, 0);

	group2->Draw(canvas);
}
catch (const std::exception& e)
{
	std::cerr << e.what();
}
