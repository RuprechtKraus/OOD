using System;
using System.IO;
using ShapesMvp.App.Helpers.Files;
using ShapesMvp.App.Managers.Serialization;
using ShapesMvp.Domain.Entities.CanvasModel;

namespace ShapesMvp.App.Managers
{
    public class ShapeFileManager
    {
        private string? _lastFileName;
        public string? LastFileName => _lastFileName;

        private FileFormat? _lastFileFormat;
        public FileFormat? LastFileFormat => _lastFileFormat;

        public void Open( string path )
        {
        }

        public void Save( Canvas canvas, string path )
        {
            FileFormat fileFormat = GetFileFormatFromFileName( path );
            ISerializer<Canvas>? serializer = CanvasSerializerFactory.GetSerializer( fileFormat );
            if ( serializer == null )
            {
                throw new ArgumentException( "Unsupported file format", nameof( path ) );
            }

            File.WriteAllText( path, serializer!.Serialize( canvas ) );

            _lastFileName = path;
            _lastFileFormat = fileFormat;
        }

        private static FileFormat GetFileFormatFromFileName( string fileName )
        {
            string? extension = Path.GetExtension( fileName );

            return extension.ToLower() switch
            {
                FileFormatString.Json => FileFormat.Json,
                FileFormatString.Xml => FileFormat.Xml,
                _ => throw new ArgumentException( "Unsupported file format", nameof( fileName ) )
            };
        }
    }
}
