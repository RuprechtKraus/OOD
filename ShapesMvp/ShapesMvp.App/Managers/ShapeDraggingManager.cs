using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Shapes;
using System.Xml.Linq;

namespace ShapesMvp.App.Dragging
{
    public class ShapeDraggingManager
    {
        private Point? _dragStart = null;
        private Canvas? _canvas = null;
        private Shape? _shape = null;

        public void EnableDrag( Shape shape )
        {
            if ( shape != null )
            {
                shape.MouseDown += OnMouseDown;
                shape.MouseUp += OnMouseUp;
                shape.MouseMove += OnMouseMove;
            }
        }

        private void OnMouseDown( object sender, MouseButtonEventArgs e )
        {
            _shape = (Shape) sender;
            _shape.Cursor = Cursors.SizeAll;
            _canvas = (Canvas) _shape.Parent;
            _dragStart = e.GetPosition( _shape );
            _shape.CaptureMouse();
        }

        private void OnMouseUp( object sender, MouseButtonEventArgs e )
        {
            if ( _shape != null )
            {
                _shape.Cursor = Cursors.Arrow;
                _dragStart = null;
                _canvas = null;
                _shape.ReleaseMouseCapture();
                _shape = null;
            }
        }

        private void OnMouseMove( object sender, MouseEventArgs e )
        {
            if ( _dragStart != null && e.LeftButton == MouseButtonState.Pressed )
            {
                Point pos = e.GetPosition( _shape );
                double dX = pos.X - _dragStart.Value.X;
                double dY = pos.Y - _dragStart.Value.Y;
                double newX = Canvas.GetLeft( _shape ) + dX;
                double newY = Canvas.GetTop( _shape ) + dY;

                newX = newX <= 0 ? 0 : newX;
                newY = newY <= 0 ? 0 : newY;
                newX = newX + _shape!.Width >= _canvas!.ActualWidth ?
                    _canvas.ActualWidth - _shape.Width : newX;
                newY = newY + _shape.Height >= _canvas.ActualHeight ?
                    _canvas.ActualHeight - _shape.Height : newY;

                Canvas.SetLeft( _shape, newX );
                Canvas.SetTop( _shape, newY );
            }
        }
    }
}
