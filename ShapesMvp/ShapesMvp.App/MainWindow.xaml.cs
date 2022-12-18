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
        event EventHandler<CanvasViewEventArgs> CanvasMouseUp;
        event EventHandler<CanvasViewEventArgs> CanvasKeyPressed;
        event EventHandler DeleteButtonPressed;
    }

    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window, ICanvasView
    {
        public event EventHandler<CanvasViewShapeAddedEventArgs>? ShapeAdded;
        public event EventHandler<CanvasViewEventArgs>? CanvasMouseDown;
        public event EventHandler<CanvasViewEventArgs>? CanvasMouseUp;
        public event EventHandler<CanvasViewEventArgs>? CanvasKeyPressed;
        public event EventHandler? DeleteButtonPressed;

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
            shape.Focusable = true;
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

                if ( source is Shape shape )
                {
                    CanvasMouseDown( this, new CanvasViewEventArgs( shape ) );
                    Keyboard.Focus( shape );
                }
                else if ( source is SystemCanvas )
                {
                    CanvasMouseDown( this, new CanvasViewEventArgs( null ) );
                    Keyboard.ClearFocus();
                }
            }
        }

        private void Canvas_MouseUp( object sender, MouseButtonEventArgs e )
        {
            if ( CanvasMouseUp != null )
            {
                object source = e.OriginalSource;

                if ( source is Shape shape )
                {
                    CanvasMouseUp( this, new CanvasViewEventArgs( shape ) );
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
