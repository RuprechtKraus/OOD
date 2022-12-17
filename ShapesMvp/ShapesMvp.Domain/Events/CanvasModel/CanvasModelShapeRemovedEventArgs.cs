namespace ShapesMvp.Domain.Events.CanvasModel
{
    public class CanvasModelShapeRemovedEventArgs : EventArgs
    {
        public string Uid { get; }

        public CanvasModelShapeRemovedEventArgs( string uid )
        {
            Uid = uid;
        }
    }
}
