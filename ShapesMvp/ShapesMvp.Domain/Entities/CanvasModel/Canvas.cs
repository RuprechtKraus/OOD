using ShapesMvp.Domain.Entities.ShapeModel;

namespace ShapesMvp.Domain.Entities.CanvasModel
{
    public class CanvasEventArgs : EventArgs
    {
        public Shape Shape { get; }

        public CanvasEventArgs( Shape shape )
        {
            Shape = shape;
        }
    }

    public class Canvas
    {
        private readonly List<Shape> _shapes = new();
        public IReadOnlyList<Shape> Shapes => _shapes;

        public event EventHandler<CanvasEventArgs> ShapeAdded = delegate { };
        public event EventHandler<CanvasEventArgs> ShapeRemoved = delegate { };

        public void AddShape( Shape shape )
        {
            _shapes.Add( shape );
            ShapeAdded( this, new CanvasEventArgs( shape ) );
        }

        public void RemoveShape( Shape shape )
        {
            _shapes.Remove( shape );
            ShapeRemoved( this, new CanvasEventArgs( shape ) );
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
