using System.Windows;
using System.Windows.Media;
using ShapesMvp.App.Events.Canvas;
using ShapesMvp.Common;
using ShapesMvp.Domain.Entities.CanvasModel;
using ShapesMvp.Domain.Entities.ShapeModel;
using ShapesMvp.Domain.Enums;
using ShapesMvp.Domain.Events.CanvasModel;
using SystemCanvas = System.Windows.Controls.Canvas;

namespace ShapesMvp.App.Presenters
{
    public class CanvasPresenter
    {
        private const double InitialShapeWidth = 50;
        private const double InitialShapeHeight = 50;
        private readonly ICanvasView _canvasView;
        private readonly Canvas _canvasModel;

        public CanvasPresenter( ICanvasView canvasView, Canvas canvas )
        {
            _canvasView = canvasView;
            _canvasModel = canvas;

            _canvasView.ShapeAdded += View_ShapeAdded;
            _canvasModel.ShapeAdded += Model_ShapeAdded;
        }

        private void View_ShapeAdded( object? sender, CanvasViewShapeAddedEventArgs e )
        {
            FrameRect frameRect = GetInitialShapeFrameRect( e.Canvas );

            switch ( e.ShapeType )
            {
                case ShapeType.Ellipse:
                    _canvasModel.AddShape( new Ellipse( frameRect ) );
                    break;
                case ShapeType.Rectangle:
                    _canvasModel.AddShape( new Rectangle( frameRect ) );
                    break;
                case ShapeType.Triangle:
                    _canvasModel.AddShape( new Triangle( frameRect ) );
                    break;
                default:
                    break;
            }
        }

        private void Model_ShapeAdded( object? sender, CanvasModelShapeAddedEventArgs e )
        {
            switch ( e.Shape.ShapeType )
            {
                case ShapeType.Ellipse:
                    System.Windows.Shapes.Ellipse ellipse = new()
                    {
                        Fill = Brushes.Crimson,
                        Uid = e.Shape.Uid,
                        Height = e.Shape.FrameRect.Height,
                        Width = e.Shape.FrameRect.Width,
                    };
                    SystemCanvas.SetLeft( ellipse, e.Shape.FrameRect.X );
                    SystemCanvas.SetTop( ellipse, e.Shape.FrameRect.Y );
                    _canvasView.AddShape( ellipse );
                    break;
                case ShapeType.Rectangle:
                    System.Windows.Shapes.Rectangle rectangle = new()
                    {
                        Fill = Brushes.Crimson,
                        Uid = e.Shape.Uid,
                        Height = e.Shape.FrameRect.Height,
                        Width = e.Shape.FrameRect.Width,
                    };
                    SystemCanvas.SetLeft( rectangle, e.Shape.FrameRect.X );
                    SystemCanvas.SetTop( rectangle, e.Shape.FrameRect.Y );
                    _canvasView.AddShape( rectangle );
                    break;
                case ShapeType.Triangle:
                    System.Windows.Shapes.Polygon triangle = new()
                    {
                        Fill = Brushes.Crimson,
                        Uid = e.Shape.Uid,
                        Height = e.Shape.FrameRect.Height,
                        Width = e.Shape.FrameRect.Width,
                    };
                    triangle.Points.Add( new Point( 0, triangle.Height ) );
                    triangle.Points.Add( new Point( triangle.Width / 2, 0 ) );
                    triangle.Points.Add( new Point( triangle.Width, triangle.Height ) );
                    SystemCanvas.SetLeft( triangle, e.Shape.FrameRect.X );
                    SystemCanvas.SetTop( triangle, e.Shape.FrameRect.Y );
                    _canvasView.AddShape( triangle );
                    break;
                default:
                    break;
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
