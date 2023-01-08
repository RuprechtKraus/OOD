using System.ComponentModel;
using System.IO;
using ShapesMvp.App.Helpers.Files;
using ShapesMvp.Domain.Entities.CanvasModel;

namespace ShapesMvp.App.Managers.Serialization
{
    public static class CanvasSerializerFactory
    {
        public static ISerializer<Canvas>? GetSerializer( FileFormat fileFormat )
        {
            return fileFormat switch
            {
                FileFormat.Json => new JsonCanvasSerializer(),
                FileFormat.Xml => new XmlCanvasSerializer(),
                _ => null
            };
        }

        public static ISerializer<Canvas>? GetSerializer( string fileFormat )
        {
            return fileFormat switch
            {
                FileFormatString.Json => new JsonCanvasSerializer(),
                FileFormatString.Xml => new XmlCanvasSerializer(),
                _ => null
            };
        }
    }
}
