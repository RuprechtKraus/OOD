#include "MockObjects/MockCanvas.h"
#include "MockObjects/MockShape.h"
#include "Shapes/Ellipse.h"
#include "Shapes/Rectangle.h"
#include "Shapes/Triangle.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::Exactly;

TEST(ShapeTest, ShapeHasCorrectColor)
{
	MockShape shape(Color::Black);
	EXPECT_EQ(shape.GetColor(), Color::Black);
}

TEST(RectangleTest, ThrowsOnIncorrectVertices)
{
	EXPECT_THROW(Rectangle rectangle(Point{ 5, 0 }, Point{ 0, 5 }, Color::Black),
		std::invalid_argument);
	EXPECT_THROW(Rectangle rectangle(Point{ 0, 5 }, Point{ 5, 0 }, Color::Black),
		std::invalid_argument);
}

TEST(RectangleTest, HasCorrectVertices)
{
	Rectangle rectangle(Point{ 0, 0 }, Point{ 5, 5 }, Color::Black);
	Point expectedTopLeft{ 0, 0 };
	Point expectedBottomRight{ 5, 5 };

	EXPECT_EQ(rectangle.GetTopLeft(), expectedTopLeft);
	EXPECT_EQ(rectangle.GetBottomRight(), expectedBottomRight);
}

TEST(RectangleTest, HandlesDrawing)
{
	MockCanvas canvas;
	Rectangle rectangle(Point{ 0, 0 }, Point{ 5, 5 }, Color::Black);

	EXPECT_CALL(canvas, SetColor(Color::Black)).Times(Exactly(1));
	EXPECT_CALL(canvas, DrawLine(Point{ 0, 0 }, Point{ 5, 0 })).Times(Exactly(1));
	EXPECT_CALL(canvas, DrawLine(Point{ 5, 0 }, Point{ 5, 5 })).Times(Exactly(1));
	EXPECT_CALL(canvas, DrawLine(Point{ 5, 5 }, Point{ 0, 5 })).Times(Exactly(1));
	EXPECT_CALL(canvas, DrawLine(Point{ 0, 5 }, Point{ 0, 0 })).Times(Exactly(1));

	rectangle.Draw(canvas);
}

TEST(TriangleTest, HasCorrectVertices)
{
	Triangle triangle(Point{ 0, 0 }, Point{ 6, 0 }, Point{ 3, 6 }, Color::Black);
	Point expectedV1{ 0, 0 };
	Point expectedV2{ 6, 0 };
	Point expectedV3{ 3, 6 };

	EXPECT_EQ(triangle.GetVertex1(), expectedV1);
	EXPECT_EQ(triangle.GetVertex2(), expectedV2);
	EXPECT_EQ(triangle.GetVertex3(), expectedV3);
}

TEST(TriangleTest, HandlesDrawing)
{
	MockCanvas canvas;
	Triangle triangle(Point{ 0, 0 }, Point{ 6, 0 }, Point{ 3, 6 }, Color::Black);

	EXPECT_CALL(canvas, SetColor(Color::Black)).Times(Exactly(1));
	EXPECT_CALL(canvas, DrawLine(Point{ 0, 0 }, Point{ 6, 0 })).Times(Exactly(1));
	EXPECT_CALL(canvas, DrawLine(Point{ 6, 0 }, Point{ 3, 6 })).Times(Exactly(1));
	EXPECT_CALL(canvas, DrawLine(Point{ 3, 6 }, Point{ 0, 0 })).Times(Exactly(1));

	triangle.Draw(canvas);
}

TEST(EllipseTest, HasCorrectRadiuses)
{
	Ellipse ellipse(Point{ 0, 0 }, 10, 5, Color::Black);

	EXPECT_EQ(ellipse.GetHorizontalRadius(), 10);
	EXPECT_EQ(ellipse.GetVerticalRadius(), 5);
}

TEST(EllipseTest, HasCorrectCenter)
{
	Ellipse ellipse(Point{ 15, 15 }, 10, 5, Color::Black);
	Point expectedRadius{ 15, 15 };

	EXPECT_EQ(ellipse.GetCenter(), expectedRadius);
}

TEST(EllipseTest, HandlesDrawing)
{
	MockCanvas canvas;
	Ellipse ellipse(Point{ 0, 0 }, 10, 5, Color::Black);

	EXPECT_CALL(canvas, SetColor(Color::Black)).Times(Exactly(1));
	EXPECT_CALL(canvas, DrawEllipse(Point{ 0, 0 }, 10, 5)).Times(Exactly(1));

	ellipse.Draw(canvas);
}