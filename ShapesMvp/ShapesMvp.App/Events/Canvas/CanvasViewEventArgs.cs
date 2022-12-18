using System;
using System.Windows.Input;
using System.Windows.Shapes;

namespace ShapesMvp.App.Events.Canvas
{
    public class CanvasViewEventArgs : EventArgs
    {
        public Shape? SelectedShape { get; }
        public Key KeyPressed { get; set; } = Key.None;

        public CanvasViewEventArgs( Shape? selectedShape )
        {
            SelectedShape = selectedShape;
        }
    }
}
