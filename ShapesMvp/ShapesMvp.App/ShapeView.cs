using System.Windows.Media;
using ShapesMvp.App.Factories;
using SystemCanvas = System.Windows.Controls.Canvas;
using DomainShapes = ShapesMvp.Domain.Entities.ShapeModel;
using SystemShapes = System.Windows.Shapes;
using ShapesMvp.App.Dragging;
using ShapesMvp.Common;
using System.Windows;
using ShapesMvp.Domain.Enums;
using System.ComponentModel;
using System.Windows.Input;
using System;

namespace ShapesMvp.App
{
    public class ShapeViewEventArgs : EventArgs
    {
        public SystemShapes.Shape Shape { get; }

        public ShapeViewEventArgs( SystemShapes.Shape shape )
        {
            Shape = shape;
        }
    }

    public class ShapeView
    {
        private readonly ICanvasView _canvas;
        private readonly DomainShapes.Shape _model;
        private readonly SystemShapes.Shape _view;
        private readonly ShapeDraggingManager _draggingManager;

        public event EventHandler<ShapeViewEventArgs>? ShapeMouseDown;
        public event EventHandler<ShapeViewEventArgs>? ShapeMouseUp;

        public readonly string Uid;

        public ShapeView( DomainShapes.Shape shape, ICanvasView canvas )
        {
            _draggingManager = new ShapeDraggingManager();
            Uid = shape.Uid;

            _canvas = canvas;
            _model = shape;
            _view = BuildView( _model );

            InitView();
        }

        private void InitView()
        {
            _view.MouseDown += ShapeView_MouseDown;
            _view.MouseUp += ShapeView_MouseUp;
            _model.ShapeChanged += ShapeModel_ShapeChanged;

            SystemCanvas.SetLeft( _view, _model.FrameRect.X );
            SystemCanvas.SetTop( _view, _model.FrameRect.Y );

            _draggingManager.EnableDrag( _view );
            _canvas.AddShape( _view );
        }

        private void ShapeView_MouseUp( object sender, MouseButtonEventArgs e )
        {
            if ( ShapeMouseUp != null && e.OriginalSource is SystemShapes.Shape shape )
            {
                ShapeMouseUp( this, new ShapeViewEventArgs( shape ) );
            }
        }

        private void ShapeView_MouseDown( object sender, MouseButtonEventArgs e )
        {
            if ( ShapeMouseDown != null && e.OriginalSource is SystemShapes.Shape shape )
            {
                ShapeMouseDown( this, new ShapeViewEventArgs( shape ) );
                shape.Focus();
            }
        }

        private void ShapeModel_ShapeChanged( object? sender, Domain.Events.ShapeModel.ShapeModelChangedEventArgs e )
        {
            SystemShapes.Shape? shapeView = _canvas.GetShapeByUid( e.Shape.Uid );
            if ( shapeView != null )
            {
                FrameRect frameRect = e.Shape.FrameRect;
                SystemCanvas.SetLeft( shapeView, frameRect.X );
                SystemCanvas.SetTop( shapeView, frameRect.Y );
                shapeView.Width = frameRect.Width;
                shapeView.Height = frameRect.Height;
            }
        }

        public static SystemShapes.Shape BuildView( DomainShapes.Shape shape )
        {
            SystemShapes.Shape _shape = shape.ShapeType switch
            {
                ShapeType.Ellipse => BuildEllipseView( shape ),
                ShapeType.Rectangle => BuildRectangleView( shape ),
                ShapeType.Triangle => BuildTriangleView( shape ),
                _ => throw new InvalidEnumArgumentException( "Unknown shape type" ),
            };
            return _shape;
        }

        private static SystemShapes.Ellipse BuildEllipseView( DomainShapes.Shape shape )
        {
            return new SystemShapes.Ellipse()
            {
                Fill = StringToBrushOrDefault( shape.Color ),
                Uid = shape.Uid,
                Height = shape.FrameRect.Height,
                Width = shape.FrameRect.Width,
                Focusable = true
            };
        }

        private static SystemShapes.Rectangle BuildRectangleView( DomainShapes.Shape shape )
        {
            return new SystemShapes.Rectangle()
            {
                Fill = StringToBrushOrDefault( shape.Color ),
                Uid = shape.Uid,
                Height = shape.FrameRect.Height,
                Width = shape.FrameRect.Width,
                Focusable = true
            };
        }

        private static SystemShapes.Polygon BuildTriangleView( DomainShapes.Shape shape )
        {
            SystemShapes.Polygon triangle = new()
            {
                Fill = StringToBrushOrDefault( shape.Color ),
                Uid = shape.Uid,
                Height = shape.FrameRect.Height,
                Width = shape.FrameRect.Width,
                Focusable = true,
                Stretch = Stretch.Fill
            };
            triangle.Points.Add( new Point( 0, triangle.Height ) );
            triangle.Points.Add( new Point( triangle.Width / 2, 0 ) );
            triangle.Points.Add( new Point( triangle.Width, triangle.Height ) );

            return triangle;
        }

        private static Brush StringToBrushOrDefault( string color )
        {
            Brush? brush = null;

            try
            {
                brush = new BrushConverter().ConvertFromString( color ) as Brush;
            }
            catch
            {
            }

            return brush ?? Brushes.Crimson;
        }
    }
}
