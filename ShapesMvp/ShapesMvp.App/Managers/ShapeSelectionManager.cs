using System;

namespace ShapesMvp.App.Managers
{
    public class ShapeSelectionEventArgs : EventArgs
    {
        public string? SelectedShapeUid { get; }

        public ShapeSelectionEventArgs( string? selectedShapeUid )
        {
            SelectedShapeUid = selectedShapeUid;
        }
    }

    public class ShapeSelectionManager
    {
        private string? _selectedShapeUid;
        public string? SelectedShapeUid
        {
            get => _selectedShapeUid;
            set
            {
                _selectedShapeUid = value;
                SelectionChanged?.Invoke( this, new ShapeSelectionEventArgs( _selectedShapeUid ) );
            }
        }

        public event EventHandler<ShapeSelectionEventArgs>? SelectionChanged;
    }
}
