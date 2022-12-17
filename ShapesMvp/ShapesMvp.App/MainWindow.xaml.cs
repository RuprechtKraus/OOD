using System;
using System.Windows;
using System.Windows.Shapes;
using ShapesMvp.App.Events.Canvas;
using ShapesMvp.App.Factories;
using ShapesMvp.App.Presenters;
using ShapesMvp.Domain.Enums;
using ShapesMvp.Domain.Events.CanvasModel;

namespace ShapesMvp.App
{
    public interface ICanvasView
    {
        void AddShape( Shape shape );
        event EventHandler<CanvasViewShapeAddedEventArgs> ShapeAdded;
    }

    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window, ICanvasView
    {
        public event EventHandler<CanvasViewShapeAddedEventArgs>? ShapeAdded;

        public MainWindow()
        {
            InitializeComponent();
            CanvasPresenter presenter = new( 
                new ShapeModelFactory(), 
                this, 
                new Domain.Entities.CanvasModel.Canvas() );
        }

        public void AddShape( Shape shape )
        {
            MainCanvas.Children.Add( shape );
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
    }
}
