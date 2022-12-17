using ShapesMvp.Domain.Entities.ShapeModel;
using ShapesMvp.Domain.Events.CanvasModel;

namespace ShapesMvp.Domain.Entities.CanvasModel
{
    public class Canvas
    {
        private readonly List<Shape> _shapes = new();
        public IReadOnlyList<Shape> Shapes => _shapes;

        public event EventHandler<CanvasModelShapeAddedEventArgs>? ShapeAdded;
        public event EventHandler<CanvasModelShapeRemovedEventArgs>? ShapeRemoved;

        public void AddShape( Shape shape )
        {
            _shapes.Add( shape );
            ShapeAdded?.Invoke( this, new CanvasModelShapeAddedEventArgs( shape ) );
        }

        public void RemoveShape( Shape shape )
        {
            _shapes.Remove( shape );
            ShapeRemoved?.Invoke( this, new CanvasModelShapeRemovedEventArgs( shape.Uid ) );
        }

        public void RemoveShapeAt( int index )
        {
            RemoveShape( _shapes[ index ] );
        }

        public Shape GetShapeAt( int index )
        {
            return _shapes.ElementAt( index );
        }
    }
}
