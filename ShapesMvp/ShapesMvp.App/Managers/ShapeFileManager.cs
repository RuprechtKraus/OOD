using System;
using System.IO;
using System.Text.Json;
using System.Xml.Serialization;
using ShapesMvp.App.Managers.Serialization;
using ShapesMvp.Domain.Entities.CanvasModel;

namespace ShapesMvp.App.Managers
{
    public class ShapeFileManager
    {
        private string? _lastSaveLocation;
        public string? LastSaveLocation => _lastSaveLocation;

        private readonly ICanvasSerializer _serializer;

        public ShapeFileManager( ICanvasSerializer serializer )
        {
            _serializer = serializer;
        }

        public void Open( string path )
        {
        }

        public void Save( Canvas canvas, string path )
        {
            _serializer.Serialize( canvas, path );
            _lastSaveLocation = path;
        }
    }
}
