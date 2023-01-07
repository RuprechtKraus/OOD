using ShapesMvp.App.Factories;
using ShapesMvp.App.Managers;
using ShapesMvp.App.Managers.Serialization;
using ShapesMvp.App.Views;
using DomainCanvas = ShapesMvp.Domain.Entities.CanvasModel.Canvas;

namespace ShapesMvp.App.Presenters
{
    public class MainCanvasPresenter : BaseCanvasPresenter
    {
        private readonly IMainCanvasView _canvasView;
        //private readonly ICanvasSerializer _canvasSerializer = new JsonSerializerAdapter();
        private readonly ICanvasSerializer _canvasSerializer = new XmlSerializerAdapter();

        public MainCanvasPresenter(
            IShapeModelFactory shapeModelFactory,
            ShapeSelectionManager selectionManager,
            IMainCanvasView canvasView,
            DomainCanvas canvasModel )
            : base( shapeModelFactory, selectionManager, canvasView, canvasModel )
        {
            _canvasView = canvasView;

            _canvasView.OpenFileButtonPressed += CanvasView_OpenFileButtonPressed;
            _canvasView.SaveFileButtonPressed += CanvasView_SaveFileButtonPressed;
            _canvasView.SaveFileAsButtonPressed += CanvasView_SaveFileAsButtonPressed;
        }

        private void CanvasView_OpenFileButtonPressed( object? sender, System.EventArgs e )
        {
            _canvasView.ShowOpenFileDialog();
        }

        private void CanvasView_SaveFileButtonPressed( object? sender, System.EventArgs e )
        {
            //_canvasView.ShowSaveFileDialog();
            _canvasSerializer.Serialize( CanvasModel, @"C:\Users\Ruprecht Kraus\Documents\MyShapes.xml" );
        }

        private void CanvasView_SaveFileAsButtonPressed( object? sender, System.EventArgs e )
        {
            _canvasView.ShowSaveFileAsDialog();
        }
    }
}
