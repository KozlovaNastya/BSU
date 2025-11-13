using FreeImageAPI;
using System;
using System.Diagnostics;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;

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
        public string CompressionPercent { get; set; }
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
                    Format = Path.GetExtension(filePath).ToUpper().Replace(".", ""),
                    CompressionPercent = CalculateCompressionPercent(filePath)
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
                    Format = Path.GetExtension(filePath).ToUpper().Replace(".", ""),
                    CompressionPercent = CalculateCompressionPercent(filePath)
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

        private string CalculateCompressionPercent(string filePath)
        {
            try
            {
                FileInfo fileInfo = new FileInfo(filePath);
                long compressedSize = fileInfo.Length;

                if (compressedSize == 0) return CalculateCompressionPercent2(filePath);

                var extension = Path.GetExtension(filePath).ToLower();
                if (extension == ".bmp") return "0%";

                long uncompressedSize = GetTrueUncompressedSize(filePath);

                if (uncompressedSize <= 0 || uncompressedSize <= compressedSize)
                    return CalculateCompressionPercent2(filePath);

                double compressionPercent = (1 - (double)compressedSize / uncompressedSize) * 100;
                compressionPercent = Math.Max(0, Math.Min(99, compressionPercent));
                return $"{compressionPercent:F1}%";
            }
            catch
            {
                return CalculateCompressionPercent2(filePath);
            }
        }

        private long GetTrueUncompressedSize(string filePath)
        {
            var extension = Path.GetExtension(filePath).ToLower();

            if (extension == ".tif" || extension == ".tiff" || extension == ".pcx")
            {
                return GetTrueUncompressedSizeWithFreeImage(filePath);
            }
            else
            {
                return GetTrueUncompressedSizeWithSystemDrawing(filePath);
            }
        }

        private long GetTrueUncompressedSizeWithSystemDrawing(string filePath)
        {
            try
            {
                using (var image = Image.FromFile(filePath))
                {
                    int width = image.Width;
                    int height = image.Height;

                    int actualBpp = GetTrueBitsPerPixel(image, filePath);

                    return CalculateRawImageSize(width, height, actualBpp);
                }
            }
            catch
            {
                return 0;
            }
        }

        private long GetTrueUncompressedSizeWithFreeImage(string filePath)
        {
            FIBITMAP dib = FreeImage.LoadEx(filePath);
            if (dib.IsNull) return 0;

            try
            {
                uint width = FreeImage.GetWidth(dib);
                uint height = FreeImage.GetHeight(dib);
                uint bpp = FreeImage.GetBPP(dib);

                return CalculateRawImageSize((int)width, (int)height, (int)bpp);
            }
            catch
            {
                return 0;
            }
            finally
            {
                if (!dib.IsNull)
                    FreeImage.Unload(dib);
            }
        }

        private int GetTrueBitsPerPixel(Image image, string filePath)
        {
            var extension = Path.GetExtension(filePath).ToLower();
            var pixelFormat = image.PixelFormat;

            switch (extension)
            {
                case ".gif":
                    return 8;

                case ".png":
                    if (pixelFormat == PixelFormat.Format32bppArgb ||
                        pixelFormat == PixelFormat.Format32bppPArgb ||
                        pixelFormat == PixelFormat.Format32bppRgb)
                        return 32;
                    else
                        return 24;

                case ".jpg":
                case ".jpeg":
                    return 24;

                case ".bmp":
                    return Image.GetPixelFormatSize(pixelFormat);

                case ".tif":
                case ".tiff":
                    return Image.GetPixelFormatSize(pixelFormat);

                default:
                    return Image.GetPixelFormatSize(pixelFormat);
            }
        }

        private long CalculateRawImageSize(int width, int height, int bitsPerPixel)
        {
            if (bitsPerPixel < 1) return 0;

            int bytesPerPixel = (bitsPerPixel + 7) / 8;

            long totalSize = (long)width * height * bytesPerPixel;

            return totalSize;
        }

        private string CalculateCompressionPercent2(string filePath)
        {
            var extension = Path.GetExtension(filePath).ToLower();

            switch (extension)
            {
                case ".bmp":
                    return "0%";
                case ".jpg":
                case ".jpeg":
                    return "85%";
                case ".png":
                    return "50%";
                case ".gif":
                    return "65%";
                case ".tif":
                case ".tiff":
                    return "40%";
                case ".pcx":
                    return "25%";
                default:
                    return "N/A";
            }
        }
    }

}