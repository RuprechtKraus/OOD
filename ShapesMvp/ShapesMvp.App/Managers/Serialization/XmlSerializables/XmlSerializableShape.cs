using System.Xml.Serialization;
using ShapesMvp.Common;
using ShapesMvp.Domain.Enums;

namespace ShapesMvp.App.Managers.Serialization.XmlSerializables
{
    [XmlType( "Shape" )]
    public class XmlSerializableShape
    {
        public ShapeType ShapeType { get; set; }
        public string? Uid { get; set; }
        public string? Color { get; set; }
        public FrameRect FrameRect { get; set; }

        public XmlSerializableShape() { }
    }
}
