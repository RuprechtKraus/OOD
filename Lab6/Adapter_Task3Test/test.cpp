#include "pch.h"

#include "ModernGraphicsLibAdapter/ModernGraphicsRendererAdapter.h"
#include "ShapeDrawingLib/ShapeDrawingLib.h"

namespace sdl = shape_drawing_lib;

TEST(ModernGraphicsRendererAdapterTest, Handles_SetColor_and_LineTo_methods)
{
	std::ostringstream out;

	{
		ModernGraphicsRendererAdapter rendererAdapter(out);

		rendererAdapter.SetColor(0x32CD32);
		rendererAdapter.LineTo(5, 5);
	}

	EXPECT_EQ(out.str(),
		R"(<draw>
  <line fromX="0" fromY="0" toX="5" toY="5">
    <color r="0.20" g="0.80" b="0.20" a="1.00"/>
  </line>
</draw>
)");
}

TEST(ModernGraphicsRendererAdapterTest, Handles_drawing_colored_triangle)
{
	std::ostringstream out;

	{
		ModernGraphicsRendererAdapter rendererAdapter(out);
		sdl::Triangle triangle({ 0, 0 }, { 5, 5 }, { 0, 5 }, 0x32CD32);

		triangle.Draw(rendererAdapter);
	}

	EXPECT_EQ(out.str(), R"(<draw>
  <line fromX="0" fromY="0" toX="5" toY="5">
    <color r="0.20" g="0.80" b="0.20" a="1.00"/>
  </line>
  <line fromX="5" fromY="5" toX="0" toY="5">
    <color r="0.20" g="0.80" b="0.20" a="1.00"/>
  </line>
  <line fromX="0" fromY="5" toX="0" toY="0">
    <color r="0.20" g="0.80" b="0.20" a="1.00"/>
  </line>
</draw>
)");
}

TEST(ModernGraphicsRendererAdapterTest, Handles_drawing_colored_rectangle)
{
	std::ostringstream out;

	{
		ModernGraphicsRendererAdapter renderAdapter(out);
		sdl::Rectangle rectangle({ 0, 0 }, 5, 5, 0x32CD32);

		rectangle.Draw(renderAdapter);
	}

	EXPECT_EQ(out.str(), R"(<draw>
  <line fromX="0" fromY="0" toX="5" toY="0">
    <color r="0.20" g="0.80" b="0.20" a="1.00"/>
  </line>
  <line fromX="5" fromY="0" toX="5" toY="5">
    <color r="0.20" g="0.80" b="0.20" a="1.00"/>
  </line>
  <line fromX="5" fromY="5" toX="0" toY="5">
    <color r="0.20" g="0.80" b="0.20" a="1.00"/>
  </line>
  <line fromX="0" fromY="5" toX="0" toY="0">
    <color r="0.20" g="0.80" b="0.20" a="1.00"/>
  </line>
</draw>
)");
}