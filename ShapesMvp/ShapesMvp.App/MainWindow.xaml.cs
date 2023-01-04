using System;
using System.Windows;
using System.Windows.Shapes;
using ShapesMvp.App.Events.Canvas;
using ShapesMvp.App.Factories;
using ShapesMvp.App.Presenters;
using ShapesMvp.Domain.Enums;
using SystemCanvas = System.Windows.Controls.Canvas;
using DomainCanvas = ShapesMvp.Domain.Entities.CanvasModel.Canvas;
using System.Windows.Input;
using System.Windows.Controls;
using ShapesMvp.Domain.Entities.CanvasModel;

namespace ShapesMvp.App
{
    public interface ICanvasView
    {
        void AddShape( Shape shape );
        void RemoveShape( Shape shape );
        Shape? GetShapeByUid( string uid );

        event EventHandler<CanvasViewShapeAddedEventArgs> ShapeAdded;
        event EventHandler<CanvasViewEventArgs> CanvasMouseDown;
        event EventHandler<CanvasViewEventArgs> CanvasKeyPressed;
        event EventHandler DeleteButtonPressed;
    }

    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window, ICanvasView
    {
        public readonly SystemCanvas Canvas;

        public event EventHandler<CanvasViewShapeAddedEventArgs>? ShapeAdded;
        public event EventHandler<CanvasViewEventArgs>? CanvasMouseDown;
        public event EventHandler<CanvasViewEventArgs>? CanvasKeyPressed;
        public event EventHandler? DeleteButtonPressed;

        public MainWindow()
        {
            InitializeComponent();
            Canvas = MainCanvas;
            CanvasPresenter presenter = new(
                new ShapeModelFactory(),
                this,
                new DomainCanvas() );
        }

        public void AddShape( Shape shape )
        {
            shape.Focusable = true;
            MainCanvas.Children.Add( shape );
            var resizeThumb = new ResizeThumb( shape );
            MainCanvas.Children.Add( resizeThumb );
        }

        public void RemoveShape( Shape shape )
        {
            MainCanvas.Children.Remove( shape );
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
            DeleteButtonPressed?.Invoke( this, new EventArgs() );
        }
    }
}
