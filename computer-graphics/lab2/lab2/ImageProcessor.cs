using System;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using FreeImageAPI;

namespace lab2
{
    public class ImageInfo
    {
        public string FileName { get; set; }
        public string Dimensions { get; set; }
        public string Resolution { get; set; }
        public string ColorDepth { get; set; }
        public string Compression { get; set; }
        public string Format { get; set; }
    }

    public class ImageProcessor
    {
        public ImageInfo GetImageInfo(string filePath)
        {
            try
            {
                var extension = Path.GetExtension(filePath).ToLower();

                if (extension == ".tif" || extension == ".tiff" || extension == ".pcx")
                {
                    return GetImageInfoWithFreeImage(filePath);
                }
                else
                {
                    return GetImageInfoWithSystemDrawing(filePath);
                }
            }
            catch (Exception ex)
            {
                return new ImageInfo
                {
                    FileName = Path.GetFileName(filePath),
                    Dimensions = "Ошибка",
                    Resolution = "Ошибка",
                    ColorDepth = "Ошибка",
                    Compression = $"Ошибка: {ex.Message}",
                    Format = "Unknown"
                };
            }
        }

        private ImageInfo GetImageInfoWithSystemDrawing(string filePath)
        {
            using (var image = Image.FromFile(filePath))
            {
                return new ImageInfo
                {
                    FileName = Path.GetFileName(filePath),
                    Dimensions = $"{image.Width} × {image.Height}",
                    Resolution = $"{image.HorizontalResolution:F0} × {image.VerticalResolution:F0} DPI",
                    ColorDepth = $"{Image.GetPixelFormatSize(image.PixelFormat)} бит",
                    Compression = GetCompressionInfo(filePath),
                    Format = Path.GetExtension(filePath).ToUpper().Replace(".", "")
                };
            }
        }

        private ImageInfo GetImageInfoWithFreeImage(string filePath)
        {
            FIBITMAP dib = FreeImage.LoadEx(filePath);
            if (dib.IsNull)
                throw new Exception("Не удалось загрузить изображение");

            try
            {
                uint width = FreeImage.GetWidth(dib);
                uint height = FreeImage.GetHeight(dib);
                uint bpp = FreeImage.GetBPP(dib);

                uint resX = FreeImage.GetDotsPerMeterX(dib);
                uint resY = FreeImage.GetDotsPerMeterY(dib);
                string resolution = $"{Math.Round(resX / 39.37)} × {Math.Round(resY / 39.37)} DPI";

                return new ImageInfo
                {
                    FileName = Path.GetFileName(filePath),
                    Dimensions = $"{width} × {height}",
                    Resolution = resolution,
                    ColorDepth = $"{bpp} бит",
                    Compression = GetFreeImageCompression(filePath),
                    Format = Path.GetExtension(filePath).ToUpper().Replace(".", "")
                };
            }
            finally
            {
                if (!dib.IsNull)
                    FreeImage.Unload(dib);
            }
        }

        private string GetCompressionInfo(string filePath)
        {
            var extension = Path.GetExtension(filePath).ToLower();

            if (extension == ".jpg" || extension == ".jpeg")
                return "JPEG";
            else if (extension == ".png")
                return "PNG";
            else if (extension == ".gif")
                return "LZW";
            else if (extension == ".bmp")
                return "None";
            else if (extension == ".tif" || extension == ".tiff")
                return "TIFF";
            else if (extension == ".pcx")
                return "RLE";
            else
                return "Unknown";
        }

        private string GetFreeImageCompression(string filePath)
        {
            var extension = Path.GetExtension(filePath).ToLower();

            if (extension == ".tif" || extension == ".tiff")
                return "TIFF Compression";
            else if (extension == ".pcx")
                return "RLE Compression";
            else
                return "Unknown";
        }
    }
}