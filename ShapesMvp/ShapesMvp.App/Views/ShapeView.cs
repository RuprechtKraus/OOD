using SystemCanvas = System.Windows.Controls.Canvas;
using DomainShapes = ShapesMvp.Domain.Entities.ShapeModel;
using SystemShapes = System.Windows.Shapes;
using ShapesMvp.App.Dragging;
using ShapesMvp.Common;
using System.Windows.Input;
using System;
using ShapesMvp.App.Extensions;
using ShapesMvp.App.Builders;
using System.Windows;
using ShapesMvp.App.Adorners.Thumbs;

namespace ShapesMvp.App.Views
{
    public class ShapeViewEventArgs : EventArgs
    {
        public SystemShapes.Shape Shape { get; }

        public ShapeViewEventArgs( SystemShapes.Shape shape )
        {
            Shape = shape;
        }
    }

    public interface IShapeView
    {
        string Uid { get; }
        FrameRect FrameRect { get; set; }

        void SetFocus();
        void UnsetFocus();

        event EventHandler<ShapeViewEventArgs>? ShapeMouseDown;
        event EventHandler<ShapeViewEventArgs>? ShapeMouseUp;
        event EventHandler? ViewDestroyed;
    }

    public class ShapeView : IShapeView
    {
        private readonly SystemCanvas _canvas;
        private readonly ShapeDraggingManager _draggingManager;
        private readonly SystemShapes.Shape _widget;
        private readonly ResizeThumb _resizeThumb;

        private bool _isFocused = false;

        public event EventHandler<ShapeViewEventArgs>? ShapeMouseDown;
        public event EventHandler<ShapeViewEventArgs>? ShapeMouseUp;
        public event EventHandler? ViewDestroyed;

        public string Uid { get; }

        private FrameRect _frameRect;
        public FrameRect FrameRect
        {
            get => _frameRect;
            set
            {
                _frameRect.X = value.X;
                _frameRect.Y = value.Y;
                _frameRect.Width = value.Width;
                _frameRect.Height = value.Height;
            }
        }

        public ShapeView(
            DomainShapes.Shape shape,
            SystemCanvas canvas,
            ShapeDraggingManager draggingManager )
        {
            _canvas = canvas;
            _draggingManager = draggingManager;

            Uid = shape.Uid;
            FrameRect = shape.FrameRect;

            _widget = ShapeViewBuilder.BuildView( shape );
            _widget.Focusable = true;
            _widget.MouseDown += ShapeView_MouseDown;
            _widget.MouseUp += ShapeView_MouseUp;
            _widget.Unloaded += Widget_Unloaded;
            _draggingManager.EnableDrag( _widget );

            _resizeThumb = new ResizeThumb( _widget );
            _resizeThumb.IsEnabled = false;

            InitWidgetLayout();
            Display();

        }

        private void ShapeView_MouseUp( object sender, MouseButtonEventArgs e )
        {
            if ( ShapeMouseUp != null && e.OriginalSource is SystemShapes.Shape shape )
            {
                ShapeMouseUp( this, new ShapeViewEventArgs( shape ) );
            }
        }

        private void ShapeView_MouseDown( object sender, MouseButtonEventArgs e )
        {
            if ( ShapeMouseDown != null && e.OriginalSource is SystemShapes.Shape shape )
            {
                ShapeMouseDown( this, new ShapeViewEventArgs( shape ) );
            }
        }

        private void Widget_Unloaded( object sender, RoutedEventArgs e )
        {
            ViewDestroyed?.Invoke( this, EventArgs.Empty );
        }

        public void SetFocus()
        {
            if ( !_isFocused )
            {
                _isFocused = true;
                _widget.EnableSelectionAdorner();
                _widget.Focus();
                _resizeThumb.Enable();
            }
        }

        public void UnsetFocus()
        {
            if ( _isFocused )
            {
                _isFocused = false;
                _widget.DisableSelectionAdorner();
                _resizeThumb.Disable();
            }
        }

        private void InitWidgetLayout()
        {
            SystemCanvas.SetLeft( _widget, FrameRect.X );
            SystemCanvas.SetTop( _widget, FrameRect.Y );
            _widget.Width = FrameRect.Width;
            _widget.Height = FrameRect.Height;
        }

        private void Display()
        {
            _canvas.Children.Add( _widget );
            _canvas.Children.Add( _resizeThumb );
        }
    }
}
