using System.Xml.Serialization;
using ShapesMvp.Common;
using ShapesMvp.Domain.Enums;

namespace ShapesMvp.App.Managers.Serialization.SerializationDtos
{
    [XmlType( "Shape" )]
    public class ShapeSerializationDto
    {
        public ShapeType ShapeType { get; set; }
        public string? Uid { get; set; }
        public string? Color { get; set; }
        public FrameRect FrameRect { get; set; }

        public ShapeSerializationDto() { }
    }
}
