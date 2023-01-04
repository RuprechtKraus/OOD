using System.Windows;
using System.Windows.Documents;
using System.Windows.Media;

namespace ShapesMvp.App.Adorners
{
    public class ShapeSelectionAdorner : Adorner
    {
        private const double ResizeThumbHeight = 10.0;
        private readonly VisualCollection _visualChildren;

        public ShapeSelectionAdorner( UIElement adornedElement )
           : base( adornedElement )
        {
            _visualChildren = new VisualCollection( this );
            IsHitTestVisible = false;
        }

        protected override void OnRender( DrawingContext drawingContext )
        {
            Rect adornedElementRect = new( AdornedElement.DesiredSize );

            SolidColorBrush renderBrush = new( Colors.Gray );
            renderBrush.Opacity = 0;
            Pen renderPen = new( new SolidColorBrush( Colors.DarkGray ), 1 );
            renderPen.DashStyle = DashStyles.Dash;

            drawingContext.DrawRectangle( renderBrush, renderPen, adornedElementRect );

            renderBrush = new( Colors.Gray );
            renderPen = new( new SolidColorBrush( Colors.DarkGray ), 1 );
            const double renderRadius = ResizeThumbHeight / 2;

            drawingContext.DrawEllipse(
                renderBrush,
                renderPen,
                adornedElementRect.BottomRight,
                renderRadius,
                renderRadius );
        }

        protected override int VisualChildrenCount => _visualChildren.Count;
        protected override Visual GetVisualChild( int index ) => _visualChildren[ index ];
    }
}
