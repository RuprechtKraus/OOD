using DomainShapes = ShapesMvp.Domain.Entities.ShapeModel;
using ShapesMvp.App.Managers;
using ShapesMvp.App.Views;

namespace ShapesMvp.App.Presenters
{
    public class ShapePresenter
    {
        private readonly IShapeView _view;
        private readonly DomainShapes.Shape _model;
        private readonly ShapeSelectionManager _selectionManager;
        private bool _isViewSelected = false;

        public ShapePresenter( 
            IShapeView view, 
            DomainShapes.Shape model, 
            ShapeSelectionManager selectionManager )
        {
            _view = view;
            _model = model;
            _selectionManager = selectionManager;

            _view.ShapeMouseUp += View_ShapeMouseUp;
            _view.ShapeMouseDown += View_ShapeMouseDown;
            _view.ViewDestroyed += View_ViewDestroyed;
            _model.ShapeChanged += Model_ShapeChanged;

            _selectionManager.SelectionChanged += SelectionManager_SelectionChanged;
        }

        private void Model_ShapeChanged( object? sender, Domain.Events.ShapeModel.ShapeModelChangedEventArgs e )
        {
            _view.FrameRect = e.Shape.FrameRect;
        }

        private void SelectionManager_SelectionChanged( object? sender, ShapeSelectionEventArgs e )
        {
            if ( e.SelectedShapeUid == _view.Uid && !_isViewSelected )
            {
                _isViewSelected = true;
                _view.SetFocus();
            }
            else if ( e.SelectedShapeUid != _view.Uid && _isViewSelected )
            {
                _isViewSelected = false;
                _view.UnsetFocus();
            }
        }

        private void View_ShapeMouseDown( object? sender, ShapeViewEventArgs e )
        {
            _selectionManager.SelectedShapeUid = _view.Uid;
        }

        private void View_ShapeMouseUp( object? sender, ShapeViewEventArgs e )
        {
            _model.FrameRect = _view.FrameRect;
        }

        private void View_ViewDestroyed( object? sender, System.EventArgs e )
        {
            _model.ShapeChanged -= Model_ShapeChanged;
        }
    }
}
