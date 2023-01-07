using ShapesMvp.App.Factories;
using ShapesMvp.App.Managers;
using ShapesMvp.App.Views;
using DomainCanvas = ShapesMvp.Domain.Entities.CanvasModel.Canvas;

namespace ShapesMvp.App.Presenters
{
    public class ChildCanvasPresenter : BaseCanvasPresenter
    {
        public ChildCanvasPresenter(
            IShapeModelFactory shapeModelFactory,
            ShapeSelectionManager selectionManager,
            IBaseCanvasView canvasView,
            DomainCanvas canvasModel )
            : base( shapeModelFactory, selectionManager, canvasView, canvasModel )
        {
        }
    }
}
