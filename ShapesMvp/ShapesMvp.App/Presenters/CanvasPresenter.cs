using System.Windows;
using System.Windows.Media;
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

        private string? _selectedShapeUid = null;

        public CanvasPresenter(
            IShapeModelFactory shapeModelFactory,
            ICanvasView canvasView,
            DomainCanvas canvas )
        {
            _shapeModelFactory = shapeModelFactory;
            _canvasView = canvasView;
            _canvasModel = canvas;

            _canvasView.ShapeAdded += View_ShapeAdded;
            _canvasView.CanvasMouseDown += View_MouseDown;
            _canvasModel.ShapeAdded += Model_ShapeAdded;
        }

        private void View_ShapeAdded( object? sender, CanvasViewShapeAddedEventArgs e )
        {
            FrameRect frameRect = GetInitialShapeFrameRect( e.Canvas );
            DomainShapes.Shape shape = _shapeModelFactory.CreateShape( e.ShapeType, frameRect );
            shape.Color = InitialShapeColor;
            _canvasModel.AddShape( shape );
        }

        private void Model_ShapeAdded( object? sender, CanvasModelShapeAddedEventArgs e )
        {
            SystemShapes.Shape shape = ShapeConverter.ConvertToView( e.Shape );
            SystemCanvas.SetLeft( shape, e.Shape.FrameRect.X );
            SystemCanvas.SetTop( shape, e.Shape.FrameRect.Y );
            _canvasView.AddShape( shape );
        }

        private void View_MouseDown( object? sender, CanvasViewEventArgs e )
        {
            if ( _selectedShapeUid != null )
            {
                SystemShapes.Shape? selectedShape = _canvasView.GetShape( _selectedShapeUid );
                var adornerLayer = AdornerLayer.GetAdornerLayer( selectedShape );
                var adorners = adornerLayer.GetAdorners( selectedShape );
                adornerLayer.Remove( adorners.First( x => x is SelectedShapeAdorner ) );
            }

            if ( e.SelectedShape != null )
            {
                _selectedShapeUid = e.SelectedShape.Uid;
                SystemShapes.Shape? selectedShape = _canvasView.GetShape( _selectedShapeUid );
                if ( selectedShape != null )
                {
                    AdornerLayer.GetAdornerLayer( selectedShape )
                        .Add( new SelectedShapeAdorner( selectedShape ) );
                }
            }
            else
            {
                _selectedShapeUid = null;
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
