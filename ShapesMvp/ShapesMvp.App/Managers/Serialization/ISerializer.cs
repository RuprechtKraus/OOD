using ShapesMvp.Domain.Entities.CanvasModel;

namespace ShapesMvp.App.Managers.Serialization
{
    public interface ISerializer<T> where T : class
    {
        string Serialize( T target );
        T Deserialize( string target );
    }
}
