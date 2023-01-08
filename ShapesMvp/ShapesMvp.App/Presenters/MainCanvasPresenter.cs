using System;
using ShapesMvp.App.Events.File;
using ShapesMvp.App.Factories;
using ShapesMvp.App.Helpers.Files;
using ShapesMvp.App.Managers;
using ShapesMvp.App.Views;
using DomainCanvas = ShapesMvp.Domain.Entities.CanvasModel.Canvas;

namespace ShapesMvp.App.Presenters
{
    public class MainCanvasPresenter : BaseCanvasPresenter
    {
        private readonly IMainCanvasView _canvasView;
        private readonly ShapeFileManager _shapeFileManager;

        public MainCanvasPresenter(
            IShapeModelFactory shapeModelFactory,
            ShapeSelectionManager selectionManager,
            IMainCanvasView canvasView,
            DomainCanvas canvasModel )
            : base( shapeModelFactory, selectionManager, canvasView, canvasModel )
        {
            _canvasView = canvasView;
            _shapeFileManager = new ShapeFileManager();

            _canvasView.OpenFileButtonPressed += CanvasView_OpenFileButtonPressed;
            _canvasView.SaveFileButtonPressed += CanvasView_SaveFileButtonPressed;
            _canvasView.FileOpened += CanvasView_FileOpened;
            _canvasView.FileSaved += CanvasView_FileSaved;
        }

        private void CanvasView_OpenFileButtonPressed( object? sender, EventArgs e )
        {
            _canvasView.ShowOpenFileDialog();
        }

        private void CanvasView_SaveFileButtonPressed( object? sender, EventArgs e )
        {
            string? lastSaveLocation = _shapeFileManager.LastFileName;

            if ( lastSaveLocation == null )
            {
                _canvasView.ShowSaveFileDialog( FileFormat.Json );
            }
            else
            {
                _shapeFileManager.Save( CanvasModel, lastSaveLocation );
            }
        }

        private void CanvasView_FileOpened( object? sender, FileEventArgs e )
        {
            _shapeFileManager.Open( e.FilePath );
        }

        private void CanvasView_FileSaved( object? sender, FileEventArgs e )
        {
            _shapeFileManager.Save( CanvasModel, e.FilePath );
        }
    }
}
