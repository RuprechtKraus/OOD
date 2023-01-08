using System.Collections.Generic;
using System.Xml.Serialization;

namespace ShapesMvp.App.Managers.Serialization.SerializationDtos
{
    [XmlType( "Canvas" )]
    public class CanvasSerializationDto
    {
        public List<ShapeSerializationDto> Shapes = new();

        public CanvasSerializationDto() { }
    }
}
