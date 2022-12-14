using ShapesMvp.Common;
using ShapesMvp.Domain.Enums;

namespace ShapesMvp.Domain.Entities.ShapeModel
{
    public class Rectangle : Shape
    {
        public Rectangle( FrameRect frameRect )
            : base( ShapeType.Rectangle, frameRect )
        {
        }

        public Rectangle( double x, double y, double width, double height )
            : base( ShapeType.Rectangle, new FrameRect( x, y, width, height ) )
        {
        }
    }
}
