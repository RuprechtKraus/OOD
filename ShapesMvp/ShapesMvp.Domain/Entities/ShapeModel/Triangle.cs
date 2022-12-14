using ShapesMvp.Common;
using ShapesMvp.Domain.Enums;

namespace ShapesMvp.Domain.Entities.ShapeModel
{
    public class Triangle : Shape
    {
        public Triangle( FrameRect frameRect )
            : base( ShapeType.Triangle, frameRect )
        {
        }

        public Triangle( double x, double y, double width, double height )
            : base( ShapeType.Triangle, new FrameRect( x, y, width, height ) )
        {
        }
    }
}
