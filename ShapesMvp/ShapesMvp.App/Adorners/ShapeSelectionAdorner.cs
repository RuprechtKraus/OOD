using System.Windows.Controls.Primitives;
using System.Windows;
using System.Windows.Documents;
using System.Windows.Media;
using System.Windows.Input;
using System;
using System.Windows.Controls;
using System.Windows.Shapes;

namespace ShapesMvp.App.Adorners
{
    public class ShapeSelectionAdorner : Adorner
    {
        private const double AdornedElementMinWidth = 50;
        private const double AdornedElementMinHeight = 50;
        private const double ResizeThumbWidth = 10.0;
        private const double ResizeThumbHeight = 10.0;

        private Thumb? _resizeThumb, _moveThumb;
        private readonly Canvas _canvas;
        private readonly VisualCollection _visualChildren;
        private readonly FrameworkElement _adornedElement;

        public ShapeSelectionAdorner( UIElement adornedElement )
           : base( adornedElement )
        {
            _visualChildren = new VisualCollection( this );
            _adornedElement = (FrameworkElement) adornedElement;
            _canvas = (Canvas) _adornedElement.Parent;

            AddMoveThumb();
            AddResizeThumb();
        }

        protected override void OnRender( DrawingContext drawingContext )
        {
            Rect adornedElementRect = new( AdornedElement.DesiredSize );

            SolidColorBrush renderBrush = new( Colors.Gray );
            renderBrush.Opacity = 0;
            Pen renderPen = new( new SolidColorBrush( Colors.DarkGray ), 1 );
            renderPen.DashStyle = DashStyles.Dash;

            drawingContext.DrawRectangle( renderBrush, renderPen, adornedElementRect );

            renderBrush = new( Colors.Gray );
            renderPen = new( new SolidColorBrush( Colors.DarkGray ), 1 );
            const double renderRadius = ResizeThumbHeight / 2;

            drawingContext.DrawEllipse(
                renderBrush,
                renderPen,
                adornedElementRect.BottomRight,
                renderRadius,
                renderRadius );
        }

        private void AddResizeThumb()
        {
            _resizeThumb = new Thumb
            {
                Width = ResizeThumbWidth,
                Height = ResizeThumbHeight,
                Opacity = 0
            };
            _resizeThumb.DragDelta += DragDeltaResizeThumb;
            _resizeThumb.DragCompleted += DragCompleted;
            _resizeThumb.Cursor = Cursors.SizeNWSE;
            _visualChildren.Add( _resizeThumb );
        }

        private void AddMoveThumb()
        {
            _moveThumb = new Thumb
            {
                Width = _adornedElement.Width,
                Height = _adornedElement.Height,
                Opacity = 0
            };
            _moveThumb.DragDelta += DragDeltaMoveThumb;
            _moveThumb.DragCompleted += DragCompleted;
            _moveThumb.Cursor = Cursors.SizeAll;
            _visualChildren.Add( _moveThumb );
        }

        private void DragDeltaResizeThumb( object sender, DragDeltaEventArgs e )
        {
            double x = Canvas.GetLeft( _adornedElement );
            double y = Canvas.GetTop( _adornedElement );
            double dX = e.HorizontalChange;
            double dY = e.VerticalChange;
            double newWidth = Math.Max( _adornedElement.Width + dX, AdornedElementMinWidth );
            double newHeight = Math.Max( _adornedElement.Height + dY, AdornedElementMinHeight );

            newWidth = x + newWidth >= _canvas.ActualWidth ? _canvas.ActualWidth - x : newWidth;
            newHeight = y + newHeight >= _canvas.ActualHeight ? _canvas.ActualHeight - y : newHeight;

            _moveThumb!.Width = newWidth;
            _moveThumb.Height = newHeight;
            _adornedElement.Width = newWidth;
            _adornedElement.Height = newHeight;
        }

        private void DragDeltaMoveThumb( object sender, DragDeltaEventArgs e )
        {
            double dX = e.HorizontalChange;
            double dY = e.VerticalChange;
            double newX = Canvas.GetLeft( _adornedElement ) + dX;
            double newY = Canvas.GetTop( _adornedElement ) + dY;

            newX = newX <= 0 ? 0 : newX;
            newY = newY <= 0 ? 0 : newY;
            newX = newX + _adornedElement.Width >= _canvas.ActualWidth ?
                _canvas.ActualWidth - _adornedElement.Width : newX;
            newY = newY + _adornedElement.Height >= _canvas.ActualHeight ?
                _canvas.ActualHeight - _adornedElement.Height : newY;

            Canvas.SetLeft( _adornedElement, newX );
            Canvas.SetTop( _adornedElement, newY );
        }

        private void DragCompleted( object sender, DragCompletedEventArgs e )
        {
            var args = new MouseButtonEventArgs( Mouse.PrimaryDevice, 0, MouseButton.Left )
            {
                RoutedEvent = MouseUpEvent
            };
            _adornedElement.RaiseEvent( args );
        }

        protected override Size ArrangeOverride( Size finalSize )
        {
            _resizeThumb?.Arrange(
                new Rect(
                    _adornedElement.Width - ResizeThumbWidth / 2,
                    _adornedElement.Height - ResizeThumbHeight / 2,
                    ResizeThumbWidth,
                    ResizeThumbHeight
                ) );

            _moveThumb?.Arrange(
                new Rect(
                    0,
                    0,
                    _adornedElement.Width,
                    _adornedElement.Height
                ) );

            return finalSize;
        }

        protected override int VisualChildrenCount => _visualChildren.Count;
        protected override Visual GetVisualChild( int index ) => _visualChildren[ index ];
    }
}
