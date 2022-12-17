using ShapesMvp.Common;
using ShapesMvp.Domain.Enums;

namespace ShapesMvp.Domain.Entities.ShapeModel
{
    public class CreateShapeArgs : EventArgs
    {
        public ShapeType ShapeType { get; }

        public CreateShapeArgs( ShapeType shapeType )
        {
            ShapeType = shapeType;
        }
    }

    public class ShapeEventArgs : EventArgs
    {
        public FrameRect FrameRect { get; }
        public string Uid { get; }

        public ShapeEventArgs( string uid, FrameRect frameRect )
        {
            Uid = uid;
            FrameRect = frameRect;
        }
    }

    public abstract class Shape
    {
        public readonly ShapeType ShapeType;
        public readonly string Uid;

        private FrameRect _frameRect;
        public FrameRect FrameRect
        {
            get => _frameRect;
            set
            {
                _frameRect = value;
                ShapeChanged?.Invoke( this, new ShapeEventArgs( Uid, _frameRect ) );
            }
        }

        public event EventHandler<ShapeEventArgs>? ShapeChanged;

        public Shape( ShapeType shapeType, FrameRect frameRect )
        {
            ShapeType = shapeType;
            FrameRect = frameRect;
            Uid = Guid.NewGuid().ToString();
        }
    }
}
