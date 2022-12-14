using ShapesMvp.Common;
using ShapesMvp.Domain.Enums;

namespace ShapesMvp.Domain.Entities.ShapeModel
{
    public class Ellipse : Shape
    {
        public Ellipse( FrameRect frameRect )
            : base( ShapeType.Ellipse, frameRect )
        {
        }

        public Ellipse( double x, double y, double width, double height )
            : base( ShapeType.Ellipse, new FrameRect( x, y, width, height ) )
        {
        }
    }
}
