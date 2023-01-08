using System;
using ShapesMvp.App.Events.File;
using ShapesMvp.App.Helpers.Files;

namespace ShapesMvp.App.Views
{
    public interface IMainCanvasView : IBaseCanvasView
    {
        void ShowSaveFileDialog( FileFormat defaultFileFormat );

        event EventHandler SaveFileButtonPressed;
        event EventHandler FileOpened;
        event EventHandler<SaveFileEventArgs> FileSaved;
    }
}
