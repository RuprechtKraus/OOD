using System.IO;
using System.Text.Json;
using ShapesMvp.Domain.Entities.CanvasModel;

namespace ShapesMvp.App.Managers.Serialization
{
    public class JsonSerializerAdapter : ICanvasSerializer
    {
        public void Serialize( Canvas canvas, string path )
        {
            using var fs = new FileStream( path, FileMode.OpenOrCreate );
            JsonSerializer.Serialize( fs, canvas, new JsonSerializerOptions()
            {
                IncludeFields = true
            } );
        }
    }
}
