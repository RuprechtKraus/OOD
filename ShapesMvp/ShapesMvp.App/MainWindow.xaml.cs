using System;
using System.Windows;
using System.Windows.Shapes;
using ShapesMvp.App.Events.Canvas;
using ShapesMvp.App.Factories;
using ShapesMvp.App.Presenters;
using ShapesMvp.Domain.Enums;
using SystemCanvas = System.Windows.Controls.Canvas;
using DomainCanvas = ShapesMvp.Domain.Entities.CanvasModel.Canvas;
using DomainShapes = ShapesMvp.Domain.Entities.ShapeModel;
using System.Windows.Input;
using ShapesMvp.App.Managers;
using ShapesMvp.App.Dragging;
using ShapesMvp.App.Views;
using ShapesMvp.App.Events.File;
using Microsoft.Win32;
using ShapesMvp.App.Helpers.Files;
using System.ComponentModel;

namespace ShapesMvp.App
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window, IMainCanvasView
    {
        private readonly ShapeSelectionManager _selectionManager = new();
        private readonly ShapeDraggingManager _draggingManager = new();
        private readonly BaseCanvasPresenter _canvasPresenter;

        public event EventHandler<CanvasViewShapeAddedEventArgs>? ShapeAdded;
        public event EventHandler<CanvasViewEventArgs>? CanvasMouseDown;
        public event EventHandler<CanvasViewEventArgs>? CanvasKeyPressed;
        public event EventHandler? SaveFileButtonPressed;
        public event EventHandler? FileOpened;
        public event EventHandler<SaveFileEventArgs>? FileSaved;
        public event EventHandler? DeleteButtonPressed;
        public event EventHandler? ViewDestroyed;

        public MainWindow()
        {
            InitializeComponent();
            _canvasPresenter = new MainCanvasPresenter(
                new ShapeModelFactory(),
                _selectionManager,
                this,
                new DomainCanvas() );
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

        public void ShowSaveFileDialog( FileFormat defaultFileFormat )
        {
            switch ( defaultFileFormat )
            {
                case FileFormat.Json:
                    ShowSaveFileDialog( 1 );
                    break;
                case FileFormat.Xml:
                    ShowSaveFileDialog( 2 );
                    break;
                default:
                    throw new InvalidEnumArgumentException( $"Unknown file format: {defaultFileFormat}" );
            }
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

        private void AddWindow_Click( object sender, RoutedEventArgs e )
        {
            var window = new ChildWindow( _canvasPresenter.CanvasModel );
            window.Owner = this;
            window.Show();
        }

        private void OpenFile_Click( object sender, RoutedEventArgs e )
        {

        }

        private void SaveFile_Click( object sender, RoutedEventArgs e )
        {
            SaveFileButtonPressed?.Invoke( this, EventArgs.Empty );
        }

        private void SaveAsJson_Click( object sender, RoutedEventArgs e ) => ShowSaveFileDialog( 1 );

        private void SaveAsXml_Click( object sender, RoutedEventArgs e ) => ShowSaveFileDialog( 2 );

        private void ShowSaveFileDialog( int filterIndex = 1 )
        {
            var dialog = new SaveFileDialog
            {
                Filter = "Json files (*.json)|*.json|Xml files (*.xml)|*.xml",
                FilterIndex = filterIndex
            };

            if ( dialog.ShowDialog() ?? false )
            {
                FileSaved?.Invoke( this, new SaveFileEventArgs( dialog.FileName ) );
            }
        }
    }
}
