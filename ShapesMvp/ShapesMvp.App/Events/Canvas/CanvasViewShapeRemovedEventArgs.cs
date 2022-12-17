using System;

namespace ShapesMvp.App.Events.Canvas
{
    public class CanvasViewShapeRemovedEventArgs : EventArgs
    {
        public string Uid { get; }

        public CanvasViewShapeRemovedEventArgs( string uid )
        {
            Uid = uid;
        }
    }
}
