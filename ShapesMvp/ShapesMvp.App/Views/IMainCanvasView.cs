using System;
using ShapesMvp.App.Events.File;
using ShapesMvp.App.Helpers.Files;

namespace ShapesMvp.App.Views
{
    public interface IMainCanvasView : IBaseCanvasView
    {
        void ShowSaveFileDialog( FileFormat defaultFileFormat );
        void ShowOpenFileDialog();

        event EventHandler SaveFileButtonPressed;
        event EventHandler OpenFileButtonPressed;
        event EventHandler<FileEventArgs> FileOpened;
        event EventHandler<FileEventArgs> FileSaved;
    }
}
