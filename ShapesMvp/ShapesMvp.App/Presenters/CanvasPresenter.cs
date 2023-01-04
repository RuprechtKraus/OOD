using System.Windows;
using ShapesMvp.App.Events.Canvas;
using ShapesMvp.App.Factories;
using ShapesMvp.Common;
using ShapesMvp.Domain.Events.CanvasModel;
using SystemCanvas = System.Windows.Controls.Canvas;
using DomainCanvas = ShapesMvp.Domain.Entities.CanvasModel.Canvas;
using SystemShapes = System.Windows.Shapes;
using DomainShapes = ShapesMvp.Domain.Entities.ShapeModel;
using ShapesMvp.App.Extensions;
using System.Windows.Input;
using System.Collections.Generic;

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
        private readonly List<ShapeView> _shapeViews;

        public CanvasPresenter(
            IShapeModelFactory shapeModelFactory,
            ICanvasView canvasView,
            DomainCanvas canvasModel )
        {
            _shapeModelFactory = shapeModelFactory;
            _canvasView = canvasView;
            _canvasModel = canvasModel;
            _shapeViews = new List<ShapeView>();

            _canvasView.ShapeAdded += CanvasView_ShapeAdded;
            _canvasView.CanvasMouseDown += CanvasView_MouseDown;
            _canvasView.CanvasKeyPressed += CanvasView_KeyPressed;
            _canvasView.DeleteButtonPressed += CanvasView_DeleteButtonPressed;

            _canvasModel.ShapeAdded += CanvasModel_ShapeAdded;
            _canvasModel.ShapeRemoved += CanvasModel_ShapeRemoved;

            LoadShapes();
        }

        private void LoadShapes()
        {
            foreach ( DomainShapes.Shape shape in _canvasModel.Shapes )
            {
                _shapeViews.Add( new ShapeView( shape, _canvasView ) );
            }
        }

        private void CanvasView_KeyPressed( object? sender, CanvasViewEventArgs e )
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

        private void CanvasView_DeleteButtonPressed( object? sender, System.EventArgs e )
        {
            RemoveShapeByUid( _selectedShapeUid! );
        }

        private void CanvasView_ShapeAdded( object? sender, CanvasViewShapeAddedEventArgs e )
        {
            FrameRect frameRect = GetInitialShapeFrameRect( e.Canvas );
            DomainShapes.Shape shape = _shapeModelFactory.CreateShape( e.ShapeType, frameRect );
            shape.Color = InitialShapeColor;
            _canvasModel.AddShape( shape );
        }

        private void CanvasView_MouseDown( object? sender, CanvasViewEventArgs e )
        {
            if ( _selectedShapeUid != null )
            {
                _canvasView.GetShapeByUid( _selectedShapeUid )?.DisableSelectionAdorner();
                _selectedShapeUid = null;
            }
        }

        private void CanvasModel_ShapeAdded( object? sender, CanvasModelShapeAddedEventArgs e )
        {
            var shapeView = new ShapeView( e.Shape, _canvasView );
            shapeView.ShapeMouseDown += ShapeView_MouseDown;
            shapeView.ShapeMouseUp += ShapeView_MouseUp;
            _shapeViews.Add( shapeView );
        }

        private void ShapeView_MouseDown( object? sender, ShapeViewEventArgs e )
        {
            if ( _selectedShapeUid != null )
            {
                _canvasView.GetShapeByUid( _selectedShapeUid )?.DisableSelectionAdorner();
            }

            _selectedShapeUid = e.Shape.Uid;
            _canvasView.GetShapeByUid( _selectedShapeUid )?.EnableSelectionAdorner();
        }

        private void ShapeView_MouseUp( object? sender, ShapeViewEventArgs e )
        {
            DomainShapes.Shape? shape = _canvasModel.GetShapeByUid( e.Shape.Uid );
            if ( shape != null )
            {
                SystemShapes.Shape shapeView = e.Shape;
                shape.FrameRect = new FrameRect(
                    SystemCanvas.GetLeft( shapeView ),
                    SystemCanvas.GetTop( shapeView ),
                    shapeView.ActualWidth,
                    shapeView.ActualHeight );
            }
        }

        private void CanvasModel_ShapeRemoved( object? sender, CanvasModelShapeRemovedEventArgs e )
        {
            SystemShapes.Shape? shape = _canvasView.GetShapeByUid( e.Uid );
            if ( shape != null )
            {
                _canvasView.RemoveShape( shape );
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

                ShapeView? shapeView = _shapeViews.Find( x => x.Uid == uid );
                if ( shapeView != null )
                {
                    _shapeViews.Remove( shapeView );
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
