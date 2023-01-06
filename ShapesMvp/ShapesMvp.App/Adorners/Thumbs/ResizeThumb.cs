using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Shapes;

namespace ShapesMvp.App.Adorners.Thumbs
{
    public class ResizeThumb : Thumb
    {
        private const int ResizedElementMinWidth = 50;
        private const int ResizedElementMinHeight = 50;
        private const int ThumbWidth = 10;
        private const int ThumbHeight = 10;

        private readonly Shape _shape;
        private Canvas? _canvas;

        public ResizeThumb( Shape shape )
        {
            _shape = shape;

            Width = ThumbWidth;
            Height = ThumbHeight;
            Opacity = 0;
            Cursor = Cursors.SizeNWSE;

            Canvas.SetLeft( this, Canvas.GetLeft( _shape ) + _shape.Width - ThumbWidth / 2 );
            Canvas.SetTop( this, Canvas.GetTop( _shape ) + _shape.Height - ThumbHeight / 2 );

            DragStarted += ResizeThumb_DragStarted;
            DragDelta += ResizeThumb_DragDelta;
            DragCompleted += ResizeThumb_DragCompleted;
            _shape.LayoutUpdated += Shape_LayoutUpdated;
        }

        public void Enable() => IsEnabled = true;

        public void Disable() => IsEnabled = false;

        private void ResizeThumb_DragStarted( object sender, DragStartedEventArgs e )
        {
            _canvas = VisualTreeHelper.GetParent( _shape ) as Canvas;
        }

        private void ResizeThumb_DragDelta( object sender, DragDeltaEventArgs e )
        {
            if ( _canvas != null )
            {
                double x = Canvas.GetLeft( _shape );
                double y = Canvas.GetTop( _shape );
                double dX = e.HorizontalChange;
                double dY = e.VerticalChange;
                double newWidth = Math.Max( _shape.Width + dX, ResizedElementMinWidth );
                double newHeight = Math.Max( _shape.Height + dY, ResizedElementMinHeight );

                newWidth = x + newWidth >= _canvas.ActualWidth ? _canvas.ActualWidth - x : newWidth;
                newHeight = y + newHeight >= _canvas.ActualHeight ? _canvas.ActualHeight - y : newHeight;

                _shape.Width = newWidth;
                _shape.Height = newHeight;
            }
        }

        private void ResizeThumb_DragCompleted( object sender, DragCompletedEventArgs e )
        {
            _canvas = null;
            var args = new MouseButtonEventArgs( Mouse.PrimaryDevice, 0, MouseButton.Left )
            {
                RoutedEvent = MouseUpEvent
            };
            _shape.RaiseEvent( args );
        }

        private void Shape_LayoutUpdated( object? sender, EventArgs e )
        {
            Canvas.SetLeft( this, Canvas.GetLeft( _shape ) + _shape.Width - 5 );
            Canvas.SetTop( this, Canvas.GetTop( _shape ) + _shape.Height - 5 );
        }
    }
}
