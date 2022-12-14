using ShapesMvp.Common;
using ShapesMvp.Domain.Enums;

namespace ShapesMvp.Domain.Entities.ShapeModel
{
    public class ShapeEventArgs : EventArgs
    {
        public FrameRect FrameRect { get; }

        public ShapeEventArgs( FrameRect frameRect )
        {
            FrameRect = frameRect;
        }
    }

    public abstract class Shape
    {
        public readonly ShapeType ShapeType;

        private FrameRect _frameRect;
        public FrameRect FrameRect
        {
            get => _frameRect;
            set
            {
                _frameRect = value;
                ShapeChanged( this, new ShapeEventArgs( _frameRect ) );
            }
        }

        public event EventHandler<ShapeEventArgs> ShapeChanged = delegate { };

        public Shape( ShapeType shapeType, FrameRect frameRect )
        {
            ShapeType = shapeType;
            FrameRect = frameRect;
        }
    }
}
