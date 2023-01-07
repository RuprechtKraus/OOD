using System.Xml.Serialization;
using ShapesMvp.Common;
using ShapesMvp.Domain.Enums;
using ShapesMvp.Domain.Events.ShapeModel;

namespace ShapesMvp.Domain.Entities.ShapeModel
{
    public abstract class Shape
    {
        public readonly ShapeType ShapeType;
        public readonly string Uid;

        public string Color { get; set; } = "Black";

        private FrameRect _frameRect;
        public FrameRect FrameRect
        {
            get => _frameRect;
            set
            {
                _frameRect = value;
                ShapeChanged?.Invoke( this, new ShapeModelChangedEventArgs( this ) );
            }
        }

        public event EventHandler<ShapeModelChangedEventArgs>? ShapeChanged;

        public Shape( ShapeType shapeType, FrameRect frameRect )
        {
            ShapeType = shapeType;
            FrameRect = frameRect;
            Uid = Guid.NewGuid().ToString();
        }
    }
}
