using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;
using ShapesMvp.Domain.Entities.ShapeModel;

namespace ShapesMvp.App.Managers.Serialization.XmlSerializables
{
    [XmlType( "Canvas" )]
    public class XmlSerializableCanvas
    {
        public List<XmlSerializableShape> Shapes = new();

        public XmlSerializableCanvas() { }
    }
}
