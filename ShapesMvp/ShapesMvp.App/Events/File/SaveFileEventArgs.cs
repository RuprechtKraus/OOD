using System;
using ShapesMvp.App.Managers;

namespace ShapesMvp.App.Events.File
{
    public class SaveFileEventArgs : EventArgs
    {
        public readonly string FilePath;

        public SaveFileEventArgs( string filePath )
        {
            FilePath = filePath;
        }
    }
}
