using System;
using System.Windows;
using System.Windows.Input;
using System.Windows.Shapes;
using ShapesMvp.App.Dragging;
using ShapesMvp.App.Events.Canvas;
using ShapesMvp.App.Managers;
using ShapesMvp.App.Views;
using ShapesMvp.Domain.Enums;
using SystemCanvas = System.Windows.Controls.Canvas;
using DomainCanvas = ShapesMvp.Domain.Entities.CanvasModel.Canvas;
using DomainShapes = ShapesMvp.Domain.Entities.ShapeModel;
using ShapesMvp.App.Presenters;
using ShapesMvp.App.Factories;

namespace ShapesMvp.App
{
    /// <summary>
    /// Interaction logic for ChildWindow.xaml
    /// </summary>
    public partial class ChildWindow : Window, IBaseCanvasView
    {
        private readonly ShapeSelectionManager _selectionManager = new();
        private readonly ShapeDraggingManager _draggingManager = new();
        private readonly BaseCanvasPresenter _canvasPresenter;

        public event EventHandler<CanvasViewShapeAddedEventArgs>? ShapeAdded;
        public event EventHandler<CanvasViewEventArgs>? CanvasMouseDown;
        public event EventHandler<CanvasViewEventArgs>? CanvasKeyPressed;
        public event EventHandler? DeleteButtonPressed;
        public event EventHandler? ViewDestroyed;

        public ChildWindow( DomainCanvas canvas )
        {
            InitializeComponent();
            _canvasPresenter = new ChildCanvasPresenter(
                new ShapeModelFactory(),
                _selectionManager,
                this,
                canvas );
        }

        public void AddShape( DomainShapes.Shape shape )
        {
            var shapeView = new ShapeView(
                shape,
                MainCanvas,
                _draggingManager );
            _ = new ShapePresenter(
                shapeView,
                shape,
                _selectionManager );
        }

        public void RemoveShapeByUid( string uid )
        {
            Shape? shape = GetShapeByUid( uid );
            if ( shape != null )
            {
                MainCanvas.Children.Remove( shape );
            }
        }

        public Shape? GetShapeByUid( string uid )
        {
            foreach ( UIElement item in MainCanvas.Children )
            {
                if ( item is Shape shape && item.Uid == uid )
                {
                    return shape;
                }
            }
            return null;
        }

        private void AddEllipseButton_Click( object sender, RoutedEventArgs e )
        {
            ShapeAdded?.Invoke( this, new CanvasViewShapeAddedEventArgs( MainCanvas, ShapeType.Ellipse ) );
        }

        private void AddRectangleButton_Click( object sender, RoutedEventArgs e )
        {
            ShapeAdded?.Invoke( this, new CanvasViewShapeAddedEventArgs( MainCanvas, ShapeType.Rectangle ) );
        }

        private void AddTriangleButton_Click( object sender, RoutedEventArgs e )
        {
            ShapeAdded?.Invoke( this, new CanvasViewShapeAddedEventArgs( MainCanvas, ShapeType.Triangle ) );
        }

        private void Canvas_MouseDown( object sender, MouseButtonEventArgs e )
        {
            if ( CanvasMouseDown != null )
            {
                object source = e.OriginalSource;

                if ( source is SystemCanvas canvas )
                {
                    CanvasMouseDown( this, new CanvasViewEventArgs( null ) );
                    canvas.Focus();
                }
            }
        }

        private void Canvas_KeyDown( object sender, KeyEventArgs e )
        {
            if ( CanvasKeyPressed != null )
            {
                var args = new CanvasViewEventArgs( e.OriginalSource is Shape ? e.OriginalSource as Shape : null )
                {
                    KeyPressed = e.Key
                };
                CanvasKeyPressed( this, args );
            }
        }

        private void DeleteButton_Click( object sender, RoutedEventArgs e )
        {
            DeleteButtonPressed?.Invoke( this, EventArgs.Empty );
        }

        private void Window_Closed( object sender, EventArgs e )
        {
            ViewDestroyed?.Invoke( this, EventArgs.Empty );
        }
    }
}
