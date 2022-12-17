using System;
using ShapesMvp.Domain.Enums;

namespace ShapesMvp.App.Events.Canvas
{
    public class CanvasViewShapeAddedEventArgs : EventArgs
    {
        public System.Windows.Controls.Canvas Canvas { get; }
        public ShapeType ShapeType { get; }

        public CanvasViewShapeAddedEventArgs( System.Windows.Controls.Canvas canvas, ShapeType shapeType )
        {
            Canvas = canvas;
            ShapeType = shapeType;
        }
    }
}
