using System.ComponentModel;
using ShapesMvp.Common;
using ShapesMvp.Domain.Entities.ShapeModel;
using ShapesMvp.Domain.Enums;

namespace ShapesMvp.App.Factories
{
    public interface IShapeModelFactory
    {
        Shape CreateShape( ShapeType shapeType, FrameRect frameRect );
    }

    public class ShapeModelFactory : IShapeModelFactory
    {
        public Shape CreateShape( ShapeType shapeType, FrameRect frameRect )
        {
            Shape shape = shapeType switch
            {
                ShapeType.Ellipse => new Ellipse( frameRect ),
                ShapeType.Rectangle => new Rectangle( frameRect ),
                ShapeType.Triangle => new Triangle( frameRect ),
                _ => throw new InvalidEnumArgumentException( "Unknown shape type" ),
            };
            return shape;
        }
    }
}
