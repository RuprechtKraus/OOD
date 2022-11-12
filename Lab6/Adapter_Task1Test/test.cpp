#include "Fakes/StubRenderer.h"
#include "ModernGraphicsLibAdapter/ModernGraphicsRendererAdapter.h"
#include "ShapeDrawingLib/ShapeDrawingLib.h"
#include "gtest/gtest.h"
#include <sstream>

namespace mgl = modern_graphics_lib;
namespace sdl = shape_drawing_lib;

using ::testing::Exactly;

TEST(ModernGraphicsRendererAdapterTest, Handles_LineTo_method)
{
	std::ostringstream out;

	{
		mgl::ModernGraphicsRenderer renderer(out);
		ModernGraphicsRendererAdapter rendererAdapter(renderer);

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
		mgl::ModernGraphicsRenderer renderer(out);
		ModernGraphicsRendererAdapter rendererAdapter(renderer);
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
		mgl::ModernGraphicsRenderer renderer(out);
		ModernGraphicsRendererAdapter renderAdapter(renderer);
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