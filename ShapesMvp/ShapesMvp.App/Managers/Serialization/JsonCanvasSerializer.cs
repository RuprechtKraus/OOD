using System.IO;
using System.Linq;
using System.Text.Json;
using ShapesMvp.App.Managers.Serialization.SerializationDtos;
using ShapesMvp.Domain.Entities.CanvasModel;
using ShapesMvp.Domain.Entities.ShapeModel;

namespace ShapesMvp.App.Managers.Serialization
{
    public class JsonCanvasSerializer : ISerializer<Canvas>
    {
        public string Serialize( Canvas target )
        {
            var jsonCanvas = new CanvasSerializationDto
            {
                Shapes = target.Shapes.Select( x => new ShapeSerializationDto()
                {
                    Color = x.Color,
                    FrameRect = x.FrameRect,
                    ShapeType = x.ShapeType,
                    Uid = x.Uid,
                } ).ToList()
            };

            return JsonSerializer.Serialize( jsonCanvas, new JsonSerializerOptions()
            {
                IncludeFields = true
            } );
        }

        public Canvas Deserialize( string target )
        {
            var canvasDto = JsonSerializer.Deserialize<CanvasSerializationDto>( target, new JsonSerializerOptions()
            {
                IncludeFields = true
            } )!;
            Canvas canvas = new Canvas();
            //foreach ( var shape in canvasDto.Shapes )
            //{
            //    Shape _shape = shape 
            //    canvas.AddShape(  );
            //};

            return canvas;
        }
    }
}
