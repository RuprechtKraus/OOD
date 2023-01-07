using System;

namespace ShapesMvp.App.Views
{
    public interface IMainCanvasView : IBaseCanvasView
    {
        void ShowOpenFileDialog();
        void ShowSaveFileDialog();
        void ShowSaveFileAsDialog();

        event EventHandler OpenFileButtonPressed;
        event EventHandler SaveFileButtonPressed;
        event EventHandler SaveFileAsButtonPressed;
    }
}
