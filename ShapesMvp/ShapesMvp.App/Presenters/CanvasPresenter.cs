using System.Windows;
using ShapesMvp.App.Events.Canvas;
using ShapesMvp.App.Factories;
using ShapesMvp.Common;
using ShapesMvp.Domain.Events.CanvasModel;
using SystemCanvas = System.Windows.Controls.Canvas;
using DomainCanvas = ShapesMvp.Domain.Entities.CanvasModel.Canvas;
using SystemShapes = System.Windows.Shapes;
using DomainShapes = ShapesMvp.Domain.Entities.ShapeModel;
using System.Windows.Input;
using ShapesMvp.App.Managers;
using ShapesMvp.App.Views;

namespace ShapesMvp.App.Presenters
{
    public class CanvasPresenter
    {
        private const double InitialShapeWidth = 50;
        private const double InitialShapeHeight = 50;
        private const string InitialShapeColor = "Crimson";

        private readonly IShapeModelFactory _shapeModelFactory;
        private readonly ShapeSelectionManager _selectionManager;
        private readonly ICanvasView _canvasView;
        private readonly DomainCanvas _canvasModel;

        public DomainCanvas GetDomainCanvas() => _canvasModel;

        public CanvasPresenter(
            IShapeModelFactory shapeModelFactory,
            ShapeSelectionManager selectionManager,
            ICanvasView canvasView,
            DomainCanvas canvasModel )
        {
            _shapeModelFactory = shapeModelFactory;
            _selectionManager = selectionManager;
            _canvasView = canvasView;
            _canvasModel = canvasModel;

            _canvasView.ShapeAdded += CanvasView_ShapeAdded;
            _canvasView.CanvasMouseDown += CanvasView_MouseDown;
            _canvasView.CanvasKeyPressed += CanvasView_KeyPressed;
            _canvasView.DeleteButtonPressed += CanvasView_DeleteButtonPressed;
            _canvasView.ViewDestroyed += CanvasView_ViewDestroyed;

            _canvasModel.ShapeAdded += CanvasModel_ShapeAdded;
            _canvasModel.ShapeRemoved += CanvasModel_ShapeRemoved;

            LoadShapes();
        }

        private void LoadShapes()
        {
            foreach ( DomainShapes.Shape shape in _canvasModel.Shapes )
            {
                _canvasView.AddShape( shape );
            }
        }

        private void CanvasView_KeyPressed( object? sender, CanvasViewEventArgs e )
        {
            switch ( e.KeyPressed )
            {
                case Key.Delete:
                    RemoveShapeByUid( _selectionManager.SelectedShapeUid! );
                    break;
                default:
                    break;
            }
        }

        private void CanvasView_DeleteButtonPressed( object? sender, System.EventArgs e )
        {
            RemoveShapeByUid( _selectionManager.SelectedShapeUid! );
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
            _selectionManager.SelectedShapeUid = null;
        }

        private void CanvasView_ViewDestroyed( object? sender, System.EventArgs e )
        {
            _canvasModel.ShapeAdded -= CanvasModel_ShapeAdded;
            _canvasModel.ShapeRemoved -= CanvasModel_ShapeRemoved;
        }

        private void CanvasModel_ShapeAdded( object? sender, CanvasModelShapeAddedEventArgs e )
        {
            _canvasView.AddShape( e.Shape );
        }

        private void CanvasModel_ShapeRemoved( object? sender, CanvasModelShapeRemovedEventArgs e )
        {
            SystemShapes.Shape? shape = _canvasView.GetShapeByUid( e.Uid );
            if ( shape != null )
            {
                _canvasView.RemoveShapeByUid( shape.Uid );
            }
        }

        private void RemoveShapeByUid( string uid )
        {
            if ( uid != null )
            {
                if ( _selectionManager.SelectedShapeUid == uid )
                {
                    _selectionManager.SelectedShapeUid = null;
                }

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
