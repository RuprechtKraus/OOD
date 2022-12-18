using System.Windows;
using ShapesMvp.App.Events.Canvas;
using ShapesMvp.App.Factories;
using ShapesMvp.Common;
using ShapesMvp.Domain.Events.CanvasModel;
using SystemCanvas = System.Windows.Controls.Canvas;
using DomainCanvas = ShapesMvp.Domain.Entities.CanvasModel.Canvas;
using SystemShapes = System.Windows.Shapes;
using DomainShapes = ShapesMvp.Domain.Entities.ShapeModel;
using System.Windows.Documents;
using ShapesMvp.App.Adorners;
using System.Linq;
using ShapesMvp.App.Extensions;
using System.Windows.Input;
using ShapesMvp.App.Dragging;

namespace ShapesMvp.App.Presenters
{
    public class CanvasPresenter
    {
        private const double InitialShapeWidth = 50;
        private const double InitialShapeHeight = 50;
        private const string InitialShapeColor = "Crimson";

        private readonly IShapeModelFactory _shapeModelFactory;
        private readonly ICanvasView _canvasView;
        private readonly DomainCanvas _canvasModel;
        private readonly ShapeDraggingManager _draggingManager;

        private string? _selectedShapeUid = null;

        public CanvasPresenter(
            IShapeModelFactory shapeModelFactory,
            ICanvasView canvasView,
            DomainCanvas canvas )
        {
            _shapeModelFactory = shapeModelFactory;
            _canvasView = canvasView;
            _canvasModel = canvas;
            _draggingManager = new ShapeDraggingManager();

            _canvasView.ShapeAdded += View_ShapeAdded;
            _canvasView.CanvasMouseDown += View_MouseDown;
            _canvasView.CanvasMouseUp += View_MouseUp;
            _canvasView.CanvasKeyPressed += View_KeyPressed;
            _canvasView.DeleteButtonPressed += View_DeleteButtonPressed;

            _canvasModel.ShapeAdded += Model_ShapeAdded;
            _canvasModel.ShapeRemoved += Model_ShapeRemoved;
        }

        private void View_KeyPressed( object? sender, CanvasViewEventArgs e )
        {
            switch ( e.KeyPressed )
            {
                case Key.Delete:
                    RemoveShapeByUid( _selectedShapeUid! );
                    break;
                default:
                    break;
            }
        }

        private void View_DeleteButtonPressed( object? sender, System.EventArgs e )
        {
            RemoveShapeByUid( _selectedShapeUid! );
        }

        private void View_ShapeAdded( object? sender, CanvasViewShapeAddedEventArgs e )
        {
            FrameRect frameRect = GetInitialShapeFrameRect( e.Canvas );
            DomainShapes.Shape shape = _shapeModelFactory.CreateShape( e.ShapeType, frameRect );
            shape.Color = InitialShapeColor;
            _canvasModel.AddShape( shape );
        }

        private void View_MouseDown( object? sender, CanvasViewEventArgs e )
        {
            if ( _selectedShapeUid != null )
            {
                _canvasView.GetShapeByUid( _selectedShapeUid )?.DisableSelectionAdorner();
            }

            if ( e.SelectedShape != null )
            {
                _selectedShapeUid = e.SelectedShape.Uid;
                _canvasView.GetShapeByUid( _selectedShapeUid )?.EnableSelectionAdorner();
            }
            else
            {
                _selectedShapeUid = null;
            }
        }

        private void View_MouseUp( object? sender, CanvasViewEventArgs e )
        {
            if ( e.SelectedShape != null )
            {
                DomainShapes.Shape? shape = _canvasModel.GetShapeByUid( e.SelectedShape.Uid );
                if ( shape != null )
                {
                    SystemShapes.Shape selectedShape = e.SelectedShape;
                    shape.FrameRect = new FrameRect(
                        SystemCanvas.GetLeft( selectedShape ),
                        SystemCanvas.GetTop( selectedShape ),
                        selectedShape.ActualWidth,
                        selectedShape.ActualHeight );
                }
            }
        }

        private void Model_ShapeAdded( object? sender, CanvasModelShapeAddedEventArgs e )
        {
            e.Shape.ShapeChanged += Shape_ShapeChanged;
            SystemShapes.Shape shape = ShapeConverter.ConvertToView( e.Shape );
            SystemCanvas.SetLeft( shape, e.Shape.FrameRect.X );
            SystemCanvas.SetTop( shape, e.Shape.FrameRect.Y );
            _draggingManager.EnableDrag( shape );
            _canvasView.AddShape( shape );
        }

        private void Model_ShapeRemoved( object? sender, CanvasModelShapeRemovedEventArgs e )
        {
            SystemShapes.Shape? shape = _canvasView.GetShapeByUid( e.Uid );
            if ( shape != null )
            {
                _canvasView.RemoveShape( shape );
            }
        }

        private void Shape_ShapeChanged( object? sender, Domain.Events.ShapeModel.ShapeModelChangedEventArgs e )
        {
            SystemShapes.Shape? shape = _canvasView.GetShapeByUid( e.Shape.Uid );
            if ( shape != null )
            {
                FrameRect frameRect = e.Shape.FrameRect;
                SystemCanvas.SetLeft( shape, frameRect.X );
                SystemCanvas.SetTop( shape, frameRect.Y );
                shape.Width = frameRect.Width;
                shape.Height = frameRect.Height;
            }
        }

        private void RemoveShapeByUid( string uid )
        {
            if ( uid != null )
            {
                DomainShapes.Shape? shape = _canvasModel.GetShapeByUid( uid );
                if ( shape != null )
                {
                    _canvasModel.RemoveShape( shape );
                }
            }
        }

        private static FrameRect GetInitialShapeFrameRect( SystemCanvas canvas )
        {
            Point point = GetInitialShapePosition( canvas );
            return new FrameRect(
                point.X,
                point.Y,
                InitialShapeWidth,
                InitialShapeHeight
                );
        }

        private static Point GetInitialShapePosition( SystemCanvas canvas )
        {
            return new Point(
                canvas.ActualWidth / 2 - InitialShapeWidth / 2,
                canvas.ActualHeight / 2 - InitialShapeHeight / 2 );
        }
    }
}
