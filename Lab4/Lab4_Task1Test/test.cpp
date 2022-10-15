#include "MockObjects/MockCanvas.h"
#include "MockObjects/MockShape.h"
#include "Shapes/Ellipse.h"
#include "Shapes/PictureDraft.h"
#include "Shapes/Rectangle.h"
#include "Shapes/RegularPolygon.h"
#include "Shapes/Triangle.h"
#include "Shapes/ShapeFactory.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <numbers>

using ::testing::Exactly;

TEST(ShapeTest, ShapeHasCorrectColor)
{
	MockShape shape(Color::Black);
	EXPECT_EQ(shape.GetColor(), Color::Black);
}

TEST(RectangleTest, ThrowsOnIncorrectVertices)
{
	EXPECT_THROW(Rectangle(Point{ 5, 0 }, Point{ 0, 5 }, Color::Black),
		std::invalid_argument);
	EXPECT_THROW(Rectangle(Point{ 0, 5 }, Point{ 5, 0 }, Color::Black),
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

TEST(EllipseTest, ThrowsOnNegativeRadius)
{
	EXPECT_THROW(Ellipse(Point{ 0, 0 }, -5, 5, Color::Black), std::invalid_argument);
	EXPECT_THROW(Ellipse(Point{ 0, 0 }, 5, -5, Color::Black), std::invalid_argument);
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
	Point expectedCenter{ 15, 15 };

	EXPECT_EQ(ellipse.GetCenter(), expectedCenter);
}

TEST(EllipseTest, HandlesDrawing)
{
	MockCanvas canvas;
	Ellipse ellipse(Point{ 0, 0 }, 10, 5, Color::Black);

	EXPECT_CALL(canvas, SetColor(Color::Black)).Times(Exactly(1));
	EXPECT_CALL(canvas, DrawEllipse(Point{ 0, 0 }, 10, 5)).Times(Exactly(1));

	ellipse.Draw(canvas);
}

TEST(RegularPolygonTest, ThrowsOnNegativeRadius)
{
	EXPECT_THROW(RegularPolygon(Point{ 0, 0 }, -5, 5, Color::Black), std::invalid_argument);
}

TEST(RegularPolygonTest, ThrowsOnVertexCountLessThanThree)
{
	EXPECT_THROW(RegularPolygon(Point{ 0, 0 }, 5, 2, Color::Black), std::invalid_argument);
}

TEST(RegularPolygonTest, HasCorrectRadius)
{
	RegularPolygon polygon(Point{ 0, 0 }, 5, 5, Color::Black);

	EXPECT_EQ(polygon.GetRadius(), 5);
}

TEST(RegularPolygonTest, HasCorrectCenter)
{
	RegularPolygon polygon(Point{ 3, 3 }, 5, 5, Color::Black);
	Point expectedCenter{ 3, 3 };

	EXPECT_EQ(polygon.GetCenter(), expectedCenter);
}

TEST(RegularPolygonTest, HasCorrectVertexCount)
{
	RegularPolygon polygon(Point{ 3, 3 }, 5, 5, Color::Black);

	EXPECT_EQ(polygon.GetVertexCount(), 5);
}

TEST(RegularPolygonTest, HandlesDrawing)
{
	MockCanvas canvas;
	RegularPolygon polygon(Point{ 3, 3 }, 5, 5, Color::Black);

	EXPECT_CALL(canvas, DrawLine).Times(Exactly(5));

	polygon.Draw(canvas);
}

TEST(PictureDraftTest, HandlesAddingShapes)
{
	PictureDraft draft;

	draft.AddShape(std::make_unique<Triangle>(
		Point{ 0, 0 }, Point{ 6, 0 }, Point{ 3, 6 }, Color::Black));
	draft.AddShape(std::make_unique<Rectangle>(
		Point{ 0, 0 }, Point{ 5, 5 }, Color::Black));

	EXPECT_FALSE(draft.IsEmpty());
	EXPECT_EQ(draft.GetShapeCount(), 2);
}

TEST(PictureDraftTest, ThrowsOnGettingShapeByIndexOutOfBounds)
{
	PictureDraft draft;

	EXPECT_THROW(draft.GetShape(2), std::out_of_range);
}

TEST(ShapeFactoryTest, HandlesRectangleCreating)
{
	ShapeFactory factory;
	std::unique_ptr<Shape> shape(factory.CreateShape("rectangle 0 0 5 5 Black"));
	Rectangle* rectangle = dynamic_cast<Rectangle*>(shape.get());
	Point expectedTopLeft{ 0, 0 };
	Point expectedBottomRight{ 5, 5 };

	ASSERT_NE(rectangle, nullptr);
	EXPECT_EQ(rectangle->GetTopLeft(), expectedTopLeft);
	EXPECT_EQ(rectangle->GetBottomRight(), expectedBottomRight);
	EXPECT_EQ(rectangle->GetColor(), Color::Black);
}

TEST(ShapeFactoryTest, HandlesTriangleCreating)
{
	ShapeFactory factory;
	std::unique_ptr<Shape> shape(factory.CreateShape("triangle 0 0 6 0 3 6 Black"));
	Triangle* triangle = dynamic_cast<Triangle*>(shape.get());
	Point expectedV1{ 0, 0 };
	Point expectedV2{ 6, 0 };
	Point expectedV3{ 3, 6 };

	ASSERT_NE(triangle, nullptr);
	EXPECT_EQ(triangle->GetVertex1(), expectedV1);
	EXPECT_EQ(triangle->GetVertex2(), expectedV2);
	EXPECT_EQ(triangle->GetVertex3(), expectedV3);
	EXPECT_EQ(triangle->GetColor(), Color::Black);
}

TEST(ShapeFactoryTest, HandlesEllipseCreating)
{
	ShapeFactory factory;
	std::unique_ptr<Shape> shape(factory.CreateShape("ellipse 5 5 2 3 Black"));
	Ellipse* ellipse = dynamic_cast<Ellipse*>(shape.get());
	Point expectedCenter{ 5, 5 };

	ASSERT_NE(ellipse, nullptr);
	EXPECT_EQ(ellipse->GetCenter(), expectedCenter);
	EXPECT_EQ(ellipse->GetHorizontalRadius(), 2);
	EXPECT_EQ(ellipse->GetVerticalRadius(), 3);
	EXPECT_EQ(ellipse->GetColor(), Color::Black);
}

TEST(ShapeFactoryTest, HandlesRegularPolygonCreating)
{
	ShapeFactory factory;
	std::unique_ptr<Shape> shape(factory.CreateShape("regular_polygon 3 3 5 7 Black"));
	RegularPolygon* polygon = dynamic_cast<RegularPolygon*>(shape.get());
	Point expectedCenter{ 3, 3 };

	ASSERT_NE(polygon, nullptr);
	EXPECT_EQ(polygon->GetCenter(), expectedCenter);
	EXPECT_EQ(polygon->GetRadius(), 5);
	EXPECT_EQ(polygon->GetVertexCount(), 7);
	EXPECT_EQ(polygon->GetColor(), Color::Black);
}