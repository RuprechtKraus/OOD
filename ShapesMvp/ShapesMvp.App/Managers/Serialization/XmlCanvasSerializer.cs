using System;
using System.IO;
using System.Linq;
using System.Windows.Documents;
using System.Xml.Serialization;
using ShapesMvp.App.Managers.Serialization.SerializationDtos;
using ShapesMvp.Domain.Entities.CanvasModel;
using ShapesMvp.Domain.Entities.ShapeModel;

namespace ShapesMvp.App.Managers.Serialization
{
    public class XmlCanvasSerializer : ISerializer<Canvas>
    {
        public string Serialize( Canvas target )
        {
            var xmlCanvas = new CanvasSerializationDto
            {
                Shapes = target.Shapes.Select( x => new ShapeSerializationDto()
                {
                    Color = x.Color,
                    FrameRect = x.FrameRect,
                    ShapeType = x.ShapeType,
                    Uid = x.Uid,
                } ).ToList()
            };
            var serializer = new XmlSerializer( xmlCanvas.GetType() );
            using var sf = new StringWriter();

            serializer.Serialize( sf, xmlCanvas );
            return sf.ToString();
        }

        public Canvas Deserialize( string taget )
        {
            throw new NotImplementedException();
        }
    }
}
