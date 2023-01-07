using ShapesMvp.Domain.Entities.CanvasModel;

namespace ShapesMvp.App.Managers.Serialization
{
    public interface ICanvasSerializer
    {
        void Serialize( Canvas canvas, string filePath );
    }
}
