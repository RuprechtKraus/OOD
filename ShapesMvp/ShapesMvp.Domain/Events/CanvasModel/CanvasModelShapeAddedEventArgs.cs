using ShapesMvp.Domain.Entities.ShapeModel;

namespace ShapesMvp.Domain.Events.CanvasModel
{
    public class CanvasModelShapeAddedEventArgs
    {
        public Shape Shape { get; }

        public CanvasModelShapeAddedEventArgs( Shape shape )
        {
            Shape = shape;
        }
    }
}
