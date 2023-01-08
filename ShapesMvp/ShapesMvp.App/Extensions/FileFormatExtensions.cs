using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ShapesMvp.App.Helpers.Files;

namespace ShapesMvp.App.Extensions
{
    public static class FileFormatExtensions
    {
        public static string ToFileExtensionString( this FileFormat fileFormat )
        {
            return fileFormat switch
            {
                FileFormat.Json => FileFormatString.Json,
                FileFormat.Xml => FileFormatString.Xml,
                _ => throw new InvalidEnumArgumentException()
            };
        }
    }
}
