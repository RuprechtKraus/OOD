#include "pch.h"

#include "ModernGraphicsLibAdapter/ModernGraphicsRendererAdapter.h"
#include "ShapeDrawingLib/ShapeDrawingLib.h"

namespace sdl = shape_drawing_lib;

TEST(ModernGraphicsRendererAdapterTest, Handles_LineTo_method)
{
	std::ostringstream out;

	{
		ModernGraphicsRendererAdapter rendererAdapter(out);

		rendererAdapter.LineTo(5, 5);
	}

	EXPECT_EQ(out.str(),
		R"(<draw>
  <line fromX="0" fromY="0" toX="5" toY="5"/>
</draw>
)");
}

TEST(ModernGraphicsRendererAdapterTest, Handles_drawing_triangle)
{
	std::ostringstream out;

	{
		ModernGraphicsRendererAdapter rendererAdapter(out);
		sdl::Triangle triangle({ 0, 0 }, { 5, 5 }, { 0, 5 });

		triangle.Draw(rendererAdapter);
	}

	EXPECT_EQ(out.str(), R"(<draw>
  <line fromX="0" fromY="0" toX="5" toY="5"/>
  <line fromX="5" fromY="5" toX="0" toY="5"/>
  <line fromX="0" fromY="5" toX="0" toY="0"/>
</draw>
)");
}

TEST(ModernGraphicsRendererAdapterTest, Handles_drawing_rectangle)
{
	std::ostringstream out;

	{
		ModernGraphicsRendererAdapter renderAdapter(out);
		sdl::Rectangle rectangle({ 0, 0 }, 5, 5);

		rectangle.Draw(renderAdapter);
	}

	EXPECT_EQ(out.str(), R"(<draw>
  <line fromX="0" fromY="0" toX="5" toY="0"/>
  <line fromX="5" fromY="0" toX="5" toY="5"/>
  <line fromX="5" fromY="5" toX="0" toY="5"/>
  <line fromX="0" fromY="5" toX="0" toY="0"/>
</draw>
)");
}