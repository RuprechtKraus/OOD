using System.IO;
using System.Text.Json;

namespace ShapesMvp.App.Managers.Serialization
{
    public class JsonSerializerAdapter<T> : ISerializer<T>
        where T : class
    {
        public string Serialize( T target )
        {
            return JsonSerializer.Serialize( target, new JsonSerializerOptions()
            {
                IncludeFields = true
            } );
        }
    }
}
