using System;
using ShapesMvp.App.Managers;

namespace ShapesMvp.App.Events.File
{
    public class FileEventArgs : EventArgs
    {
        public readonly string FilePath;

        public FileEventArgs( string filePath )
        {
            FilePath = filePath;
        }
    }
}
