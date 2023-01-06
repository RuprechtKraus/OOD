using ShapesMvp.Domain.Enums;
using System.ComponentModel;
using System.Windows;
using System.Windows.Media;
using DomainShapes = ShapesMvp.Domain.Entities.ShapeModel;
using SystemShapes = System.Windows.Shapes;

namespace ShapesMvp.App.Builders
{
    public static class ShapeViewBuilder
    {
        public static SystemShapes.Shape BuildView( DomainShapes.Shape shape )
        {
            SystemShapes.Shape _shape = shape.ShapeType switch
            {
                ShapeType.Ellipse => BuildEllipseView( shape ),
                ShapeType.Rectangle => BuildRectangleView( shape ),
                ShapeType.Triangle => BuildTriangleView( shape ),
                _ => throw new InvalidEnumArgumentException( "Unknown shape type" ),
            };
            return _shape;
        }

        private static SystemShapes.Ellipse BuildEllipseView( DomainShapes.Shape shape )
        {
            return new SystemShapes.Ellipse()
            {
                Fill = StringToBrushOrDefault( shape.Color ),
                Uid = shape.Uid,
                Height = shape.FrameRect.Height,
                Width = shape.FrameRect.Width,
                Focusable = true
            };
        }

        private static SystemShapes.Rectangle BuildRectangleView( DomainShapes.Shape shape )
        {
            return new SystemShapes.Rectangle()
            {
                Fill = StringToBrushOrDefault( shape.Color ),
                Uid = shape.Uid,
                Height = shape.FrameRect.Height,
                Width = shape.FrameRect.Width,
                Focusable = true
            };
        }

        private static SystemShapes.Polygon BuildTriangleView( DomainShapes.Shape shape )
        {
            SystemShapes.Polygon triangle = new()
            {
                Fill = StringToBrushOrDefault( shape.Color ),
                Uid = shape.Uid,
                Height = shape.FrameRect.Height,
                Width = shape.FrameRect.Width,
                Focusable = true,
                Stretch = Stretch.Fill
            };
            triangle.Points.Add( new Point( 0, triangle.Height ) );
            triangle.Points.Add( new Point( triangle.Width / 2, 0 ) );
            triangle.Points.Add( new Point( triangle.Width, triangle.Height ) );

            return triangle;
        }

        private static Brush StringToBrushOrDefault( string color )
        {
            Brush? brush = null;

            try
            {
                brush = new BrushConverter().ConvertFromString( color ) as Brush;
            }
            catch
            {
            }

            return brush ?? Brushes.Crimson;
        }
    }
}
