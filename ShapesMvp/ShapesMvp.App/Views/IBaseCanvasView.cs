using System;
using System.Windows.Shapes;
using DomainShapes = ShapesMvp.Domain.Entities.ShapeModel;
using ShapesMvp.App.Events.Canvas;

namespace ShapesMvp.App.Views
{
    public interface IBaseCanvasView
    {
        void AddShape( DomainShapes.Shape shape );
        void RemoveShapeByUid( string uid );
        Shape? GetShapeByUid( string uid );

        event EventHandler<CanvasViewShapeAddedEventArgs> ShapeAdded;
        event EventHandler<CanvasViewEventArgs> CanvasMouseDown;
        event EventHandler<CanvasViewEventArgs> CanvasKeyPressed;
        event EventHandler DeleteButtonPressed;
        event EventHandler ViewDestroyed;
    }
}
