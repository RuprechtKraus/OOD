using System;
using System.Windows.Shapes;

namespace ShapesMvp.App.Events.Canvas
{
    public class CanvasViewEventArgs : EventArgs
    {
        public Shape? SelectedShape { get; }

        public CanvasViewEventArgs( Shape? selectedShape )
        {
            SelectedShape = selectedShape;
        }
    }
}
