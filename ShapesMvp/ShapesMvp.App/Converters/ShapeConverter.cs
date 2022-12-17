using System.ComponentModel;
using ShapesMvp.Domain.Enums;
using SystemShapes = System.Windows.Shapes;
using DomainShapes = ShapesMvp.Domain.Entities.ShapeModel;
using System.Windows.Media;
using System.Windows;

namespace ShapesMvp.App.Factories
{
    public class ShapeConverter
    {
        public static SystemShapes.Shape ConvertToView( DomainShapes.Shape shape )
        {
            SystemShapes.Shape _shape = shape.ShapeType switch
            {
                ShapeType.Ellipse => ConvertToEllipseView( shape ),
                ShapeType.Rectangle => ConvertToRectangleView( shape ),
                ShapeType.Triangle => ConvertToTriangleView( shape ),
                _ => throw new InvalidEnumArgumentException( "Unknown shape type" ),
            };
            return _shape;
        }

        private static SystemShapes.Ellipse ConvertToEllipseView( DomainShapes.Shape shape )
        {
            return new SystemShapes.Ellipse()
            {
                Fill = (Brush) new BrushConverter().ConvertFromString( shape.Color ),
                Uid = shape.Uid,
                Height = shape.FrameRect.Height,
                Width = shape.FrameRect.Width,
            };
        }

        private static SystemShapes.Rectangle ConvertToRectangleView( DomainShapes.Shape shape )
        {
            return new SystemShapes.Rectangle()
            {
                Fill = (Brush) new BrushConverter().ConvertFromString( shape.Color ),
                Uid = shape.Uid,
                Height = shape.FrameRect.Height,
                Width = shape.FrameRect.Width,
            };
        }

        private static SystemShapes.Polygon ConvertToTriangleView( DomainShapes.Shape shape )
        {
            SystemShapes.Polygon triangle = new()
            {
                Fill = (Brush) new BrushConverter().ConvertFromString( shape.Color ),
                Uid = shape.Uid,
                Height = shape.FrameRect.Height,
                Width = shape.FrameRect.Width,
            };
            triangle.Points.Add( new Point( 0, triangle.Height ) );
            triangle.Points.Add( new Point( triangle.Width / 2, 0 ) );
            triangle.Points.Add( new Point( triangle.Width, triangle.Height ) );

            return triangle;
        }
    }
}
