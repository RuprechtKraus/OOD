using System.IO;
using System.Linq;
using System.Windows.Documents;
using System.Xml.Serialization;
using ShapesMvp.App.Managers.Serialization.XmlSerializables;
using ShapesMvp.Domain.Entities.CanvasModel;
using ShapesMvp.Domain.Entities.ShapeModel;

namespace ShapesMvp.App.Managers.Serialization
{
    public class XmlSerializerAdapter : ICanvasSerializer
    {
        public void Serialize( Canvas canvas, string path )
        {
            var xmlCanvas = new XmlSerializableCanvas
            {
                Shapes = canvas.Shapes.Select( x => new XmlSerializableShape()
                {
                    Color = x.Color,
                    FrameRect = x.FrameRect,
                    ShapeType = x.ShapeType,
                    Uid = x.Uid,
                } ).ToList()
            };

            var serializer = new XmlSerializer( typeof( XmlSerializableCanvas ) );
            using var fs = new FileStream( path, FileMode.OpenOrCreate );
            serializer.Serialize( fs, xmlCanvas );
        }
    }
}
