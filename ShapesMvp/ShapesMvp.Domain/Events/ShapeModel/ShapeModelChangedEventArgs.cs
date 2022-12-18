using ShapesMvp.Domain.Entities.ShapeModel;

namespace ShapesMvp.Domain.Events.ShapeModel
{
    public class ShapeModelChangedEventArgs : EventArgs
    {
        public Shape Shape { get; }

        public ShapeModelChangedEventArgs( Shape shape )
        {
            Shape = shape;
        }
    }
}
