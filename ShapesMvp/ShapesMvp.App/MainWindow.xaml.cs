using System;
using System.Windows;
using System.Windows.Shapes;
using ShapesMvp.App.Events.Canvas;
using ShapesMvp.App.Factories;
using ShapesMvp.App.Presenters;
using ShapesMvp.Domain.Enums;
using System.Linq;
using DomainCanvas = ShapesMvp.Domain.Entities.CanvasModel.Canvas;
using System.Windows.Input;
using System.Windows.Controls;

namespace ShapesMvp.App
{
    public interface ICanvasView
    {
        void AddShape( Shape shape );
        Shape? GetShape( string uid );

        event EventHandler<CanvasViewShapeAddedEventArgs> ShapeAdded;
        event EventHandler<CanvasViewEventArgs> CanvasMouseDown;
    }

    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window, ICanvasView
    {
        public event EventHandler<CanvasViewShapeAddedEventArgs>? ShapeAdded;
        public event EventHandler<CanvasViewEventArgs>? CanvasMouseDown;

        public MainWindow()
        {
            InitializeComponent();
            CanvasPresenter presenter = new(
                new ShapeModelFactory(),
                this,
                new DomainCanvas() );
        }

        public void AddShape( Shape shape )
        {
            MainCanvas.Children.Add( shape );
        }

        public Shape? GetShape( string uid )
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

                if ( source is Shape shape )
                {
                    CanvasMouseDown( this, new CanvasViewEventArgs( shape ) );
                }
                else if ( source is Canvas )
                {
                    CanvasMouseDown( this, new CanvasViewEventArgs( null ) );
                }
            }
        }
    }
}
