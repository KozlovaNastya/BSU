using System;
using System.Drawing;
using System.Linq;
using System.Reflection.Emit;
using System.Windows.Forms;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;
using static System.Windows.Forms.VisualStyles.VisualStyleElement.Button;

namespace lab3
{
    public partial class Form1 : Form
    {
        private Bitmap originalImage;
        private Bitmap processedImage;

        public Form1()
        {
            InitializeComponent();
            SetupControls();
        }

        private void SetupControls()
        {
            trackBar1.Value = 0;
            trackBar2.Value = 255;
            UpdateMinMaxLabels();

            trackBar3.Value = 50;
            UpdateThresholdLabel();
        }

        private void UpdateMinMaxLabels()
        {
            label1.Text = $"Min: {trackBar1.Value}, Max: {trackBar2.Value}";
        }

        private void UpdateThresholdLabel()
        {
            label2.Text = $"Порог: {trackBar3.Value}";
        }

        private void открытьToolStripMenuItem_Click(object sender, EventArgs e)
        {
            using (OpenFileDialog ofd = new OpenFileDialog())
            {
                ofd.Filter = "Image Files|*.jpg;*.jpeg;*.png;*.bmp";
                if (ofd.ShowDialog() == DialogResult.OK)
                {
                    originalImage = new Bitmap(ofd.FileName);
                    processedImage = new Bitmap(originalImage);

                    UpdateAllTabImages();

                    this.Text = $"Обработчик изображений - {originalImage.Width}×{originalImage.Height}";
                }
            }
        }

        private void UpdateAllTabImages()
        {
            pictureBox1.Image = originalImage;  // Исходное
            pictureBox2.Image = processedImage; // Обработанное

            pictureBox3.Image = originalImage;  // Исходное
            pictureBox4.Image = processedImage; // Обработанное
        }

        private void UpdateProcessedImages()
        {
            pictureBox2.Image = processedImage;
            pictureBox4.Image = processedImage;
        }

        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            if (trackBar1.Value >= trackBar2.Value)
                trackBar1.Value = trackBar2.Value - 1;
            UpdateMinMaxLabels();
        }

        private void trackBar2_Scroll(object sender, EventArgs e)
        {
            if (trackBar2.Value <= trackBar1.Value)
                trackBar2.Value = trackBar1.Value + 1;
            UpdateMinMaxLabels();
        }

        private void trackBar3_Scroll(object sender, EventArgs e)
        {
            UpdateThresholdLabel();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (originalImage != null)
            {
                ShowHistogram(originalImage, "Исходное изображение");
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (processedImage != null)
            {
                ShowHistogram(processedImage, "Обработанное изображение");
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (originalImage != null)
            {
                processedImage = ApplyLinearContrast(originalImage, trackBar1.Value, trackBar2.Value);
                UpdateProcessedImages();
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            if (originalImage != null)
            {
                if (radioButton1.Checked)
                    processedImage = EqualizeHistogramRGB(originalImage);
                else
                    processedImage = EqualizeHistogramHSV(originalImage);

                UpdateProcessedImages();
            }
        }

        private void button5_Click(object sender, EventArgs e)
        {
            if (originalImage != null)
            {
                processedImage = DetectPoints(originalImage);
                UpdateProcessedImages();
            }
        }

        private void button6_Click(object sender, EventArgs e)
        {
            if (originalImage != null)
            {
                processedImage = DetectLines(originalImage);
                UpdateProcessedImages();
            }
        }

        private void button7_Click(object sender, EventArgs e)
        {
            if (originalImage != null)
            {
                processedImage = DetectEdges(originalImage, trackBar3.Value);
                UpdateProcessedImages();
            }
        }

        private void ShowHistogram(Bitmap image, string title)
        {
            Form histForm = new Form();
            histForm.Text = title;
            histForm.Size = new Size(300, 200);

            PictureBox histPictureBox = new PictureBox();
            histPictureBox.Dock = DockStyle.Fill;
            histPictureBox.SizeMode = PictureBoxSizeMode.Zoom;

            Bitmap histogram = CreateHistogramBitmap(image, 280, 150);
            histPictureBox.Image = histogram;

            histForm.Controls.Add(histPictureBox);
            histForm.Show();
        }

        private Bitmap CreateHistogramBitmap(Bitmap image, int width, int height)
        {
            Bitmap histogram = new Bitmap(width, height);
            using (Graphics g = Graphics.FromImage(histogram))
            {
                g.Clear(Color.White);

                int[] histData = new int[256];
                for (int x = 0; x < image.Width; x++)
                {
                    for (int y = 0; y < image.Height; y++)
                    {
                        Color pixel = image.GetPixel(x, y);
                        int brightness = (int)(pixel.R * 0.299 + pixel.G * 0.587 + pixel.B * 0.114);
                        histData[brightness]++;
                    }
                }

                int max = histData.Max();
                if (max == 0) max = 1;

                Pen pen = new Pen(Color.Blue);
                for (int i = 0; i < 256; i++)
                {
                    if (i < width)
                    {
                        int barHeight = (int)((histData[i] / (float)max) * (height - 20));
                        g.DrawLine(pen, i, height - 10, i, height - 10 - barHeight);
                    }
                }

                Font font = new Font("Arial", 8);
                g.DrawString("0", font, Brushes.Black, 0, height - 20);
                g.DrawString("255", font, Brushes.Black, width - 20, height - 20);
            }

            return histogram;
        }

        private Bitmap ApplyLinearContrast(Bitmap image, int min, int max)
        {
            Bitmap result = new Bitmap(image.Width, image.Height);

            if (min == max) return new Bitmap(image);

            double contrastFactor = 255.0 / (max - min);

            for (int x = 0; x < image.Width; x++)
            {
                for (int y = 0; y < image.Height; y++)
                {
                    Color pixel = image.GetPixel(x, y);

                    int r = ApplyContrastToChannel(pixel.R, min, max, contrastFactor);
                    int g = ApplyContrastToChannel(pixel.G, min, max, contrastFactor);
                    int b = ApplyContrastToChannel(pixel.B, min, max, contrastFactor);

                    r = Math.Max(0, Math.Min(255, r));
                    g = Math.Max(0, Math.Min(255, g));
                    b = Math.Max(0, Math.Min(255, b));

                    result.SetPixel(x, y, Color.FromArgb(r, g, b));
                }
            }

            return result;
        }

        private int ApplyContrastToChannel(int channelValue, int min, int max, double contrastFactor)
        {
            if (channelValue < min) return 0;
            if (channelValue > max) return 255;

            return (int)((channelValue - min) * contrastFactor);
        }

        private Bitmap EqualizeHistogramRGB(Bitmap image)
        {
            Bitmap result = new Bitmap(image.Width, image.Height);

            int[] histR = new int[256];
            int[] histG = new int[256];
            int[] histB = new int[256];

            for (int x = 0; x < image.Width; x++)
            {
                for (int y = 0; y < image.Height; y++)
                {
                    Color pixel = image.GetPixel(x, y);
                    histR[pixel.R]++;
                    histG[pixel.G]++;
                    histB[pixel.B]++;
                }
            }

            int[] cumR = CalculateCumulativeHistogram(histR, image.Width * image.Height);
            int[] cumG = CalculateCumulativeHistogram(histG, image.Width * image.Height);
            int[] cumB = CalculateCumulativeHistogram(histB, image.Width * image.Height);

            for (int x = 0; x < image.Width; x++)
            {
                for (int y = 0; y < image.Height; y++)
                {
                    Color pixel = image.GetPixel(x, y);
                    int newR = cumR[pixel.R];
                    int newG = cumG[pixel.G];
                    int newB = cumB[pixel.B];

                    result.SetPixel(x, y, Color.FromArgb(newR, newG, newB));
                }
            }

            return result;
        }

        private int[] CalculateCumulativeHistogram(int[] histogram, int totalPixels)
        {
            int[] cumulative = new int[256];
            cumulative[0] = histogram[0];

            for (int i = 1; i < 256; i++)
            {
                cumulative[i] = cumulative[i - 1] + histogram[i];
            }

            for (int i = 0; i < 256; i++)
            {
                cumulative[i] = (int)(cumulative[i] * 255.0 / totalPixels);
            }

            return cumulative;
        }

        private Bitmap EqualizeHistogramHSV(Bitmap image)
        {
            Bitmap result = new Bitmap(image.Width, image.Height);

            int[] histV = new int[256];
            double[,] hsvPixels = new double[image.Width, image.Height];

            for (int x = 0; x < image.Width; x++)
            {
                for (int y = 0; y < image.Height; y++)
                {
                    Color pixel = image.GetPixel(x, y);
                    double h, s, v;
                    RGBtoHSV(pixel.R, pixel.G, pixel.B, out h, out s, out v);

                    hsvPixels[x, y] = v;
                    histV[(int)(v * 255)]++;
                }
            }

            int totalPixels = image.Width * image.Height;
            int[] cumV = CalculateCumulativeHistogram(histV, totalPixels);

            for (int x = 0; x < image.Width; x++)
            {
                for (int y = 0; y < image.Height; y++)
                {
                    Color originalPixel = image.GetPixel(x, y);
                    double h, s, v;
                    RGBtoHSV(originalPixel.R, originalPixel.G, originalPixel.B, out h, out s, out v);

                    double newV = cumV[(int)(v * 255)] / 255.0;

                    Color newColor = HSVtoRGB(h, s, newV);
                    result.SetPixel(x, y, newColor);
                }
            }

            return result;
        }

        private void RGBtoHSV(int r, int g, int b, out double h, out double s, out double v)
        {
            double rd = r / 255.0;
            double gd = g / 255.0;
            double bd = b / 255.0;

            double max = Math.Max(rd, Math.Max(gd, bd));
            double min = Math.Min(rd, Math.Min(gd, bd));
            double delta = max - min;

            v = max;

            if (max == 0)
            {
                s = 0;
                h = 0;
            }
            else
            {
                s = delta / max;

                if (delta == 0)
                {
                    h = 0;
                }
                else
                {
                    if (rd == max) h = (gd - bd) / delta;
                    else if (gd == max) h = 2 + (bd - rd) / delta;
                    else h = 4 + (rd - gd) / delta;

                    h *= 60;
                    if (h < 0) h += 360;
                }
            }
        }

        private Color HSVtoRGB(double h, double s, double v)
        {
            if (s == 0)
            {
                int val = (int)(v * 255);
                return Color.FromArgb(val, val, val);
            }

            h /= 60;
            int i = (int)Math.Floor(h);
            double f = h - i;
            double p = v * (1 - s);
            double q = v * (1 - s * f);
            double t = v * (1 - s * (1 - f));

            double r, g, b;
            switch (i)
            {
                case 0: r = v; g = t; b = p; break;
                case 1: r = q; g = v; b = p; break;
                case 2: r = p; g = v; b = t; break;
                case 3: r = p; g = q; b = v; break;
                case 4: r = t; g = p; b = v; break;
                default: r = v; g = p; b = q; break;
            }

            return Color.FromArgb(
                (int)(r * 255),
                (int)(g * 255),
                (int)(b * 255)
            );
        }

        private Bitmap DetectPoints(Bitmap image)
        {
            Bitmap result = new Bitmap(image);

            int[,] pointMask = {
        { -1, -1, -1 },
        { -1,  8, -1 },
        { -1, -1, -1 }
    };

            for (int x = 1; x < image.Width - 1; x++)
            {
                for (int y = 1; y < image.Height - 1; y++)
                {
                    int sum = 0;

                    for (int i = -1; i <= 1; i++)
                    {
                        for (int j = -1; j <= 1; j++)
                        {
                            Color pixel = image.GetPixel(x + i, y + j);
                            int brightness = (pixel.R + pixel.G + pixel.B) / 3;
                            sum += brightness * pointMask[i + 1, j + 1];
                        }
                    }

                    if (Math.Abs(sum) > 100)
                    {
                        result.SetPixel(x, y, Color.Red);
                        for (int i = -1; i <= 1; i++)
                        {
                            for (int j = -1; j <= 1; j++)
                            {
                                if (x + i >= 0 && x + i < result.Width &&
                                    y + j >= 0 && y + j < result.Height)
                                {
                                    result.SetPixel(x + i, y + j, Color.Red);
                                }
                            }
                        }
                    }
                }
            }

            return result;
        }
        private Bitmap DetectLines(Bitmap image)
        {
            Bitmap result = new Bitmap(image);

            int[][,] lineMasks = new int[4][,]
            {
        // Горизонтальные линии
        new int[,] { { -1, -1, -1 }, {  2,  2,  2 }, { -1, -1, -1 } },
        // Вертикальные линии
        new int[,] { { -1,  2, -1 }, { -1,  2, -1 }, { -1,  2, -1 } },
        // Диагональные 45°
        new int[,] { { -1, -1,  2 }, { -1,  2, -1 }, {  2, -1, -1 } },
        // Диагональные 135°
        new int[,] { {  2, -1, -1 }, { -1,  2, -1 }, { -1, -1,  2 } }
            };

            Color[] lineColors = { Color.Red, Color.Blue, Color.Green, Color.Orange };

            for (int x = 1; x < image.Width - 1; x++)
            {
                for (int y = 1; y < image.Height - 1; y++)
                {
                    int maxResponse = 0;
                    int bestDirection = -1;

                    for (int direction = 0; direction < 4; direction++)
                    {
                        int sum = 0;

                        for (int i = -1; i <= 1; i++)
                        {
                            for (int j = -1; j <= 1; j++)
                            {
                                Color pixel = image.GetPixel(x + i, y + j);
                                int brightness = (pixel.R + pixel.G + pixel.B) / 3;
                                sum += brightness * lineMasks[direction][i + 1, j + 1];
                            }
                        }

                        if (Math.Abs(sum) > maxResponse)
                        {
                            maxResponse = Math.Abs(sum);
                            bestDirection = direction;
                        }
                    }

                    if (maxResponse > 150)
                    {
                        result.SetPixel(x, y, lineColors[bestDirection]);
                    }
                }
            }

            return result;
        }

        private Bitmap DetectEdges(Bitmap image, int threshold)
        {
            Bitmap result = new Bitmap(image.Width, image.Height);

            // Оператор Собеля
            int[,] sobelX = { { -1, 0, 1 }, { -2, 0, 2 }, { -1, 0, 1 } };
            int[,] sobelY = { { -1, -2, -1 }, { 0, 0, 0 }, { 1, 2, 1 } };

            Bitmap grayscale = ToGrayscale(image);

            int maxGradient = 0;
            int[,] gradients = new int[image.Width, image.Height];

            for (int x = 1; x < image.Width - 1; x++)
            {
                for (int y = 1; y < image.Height - 1; y++)
                {
                    int gx = 0, gy = 0;

                    for (int i = -1; i <= 1; i++)
                    {
                        for (int j = -1; j <= 1; j++)
                        {
                            Color pixel = grayscale.GetPixel(x + i, y + j);
                            int brightness = pixel.R;

                            gx += brightness * sobelX[i + 1, j + 1];
                            gy += brightness * sobelY[i + 1, j + 1];
                        }
                    }

                    int gradient = (int)Math.Sqrt(gx * gx + gy * gy);
                    gradients[x, y] = gradient;
                    if (gradient > maxGradient) maxGradient = gradient;
                }
            }

            double scale = maxGradient > 0 ? 255.0 / maxGradient : 1;

            for (int x = 0; x < image.Width; x++)
            {
                for (int y = 0; y < image.Height; y++)
                {
                    int gradient = gradients[x, y];
                    int normalizedGradient = (int)(gradient * scale);

                    if (normalizedGradient > threshold)
                    {
                        result.SetPixel(x, y, Color.White);
                    }
                    else
                    {
                        result.SetPixel(x, y, Color.Black);
                    }
                }
            }

            return result;
        }

        private Bitmap ToGrayscale(Bitmap image)
        {
            Bitmap result = new Bitmap(image.Width, image.Height);

            for (int x = 0; x < image.Width; x++)
            {
                for (int y = 0; y < image.Height; y++)
                {
                    Color pixel = image.GetPixel(x, y);
                    int brightness = (int)(pixel.R * 0.299 + pixel.G * 0.587 + pixel.B * 0.114);
                    result.SetPixel(x, y, Color.FromArgb(brightness, brightness, brightness));
                }
            }

            return result;
        }
        private void сохранитьToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (processedImage != null)
            {
                using (SaveFileDialog sfd = new SaveFileDialog())
                {
                    sfd.Filter = "JPEG Image|*.jpg|PNG Image|*.png|BMP Image|*.bmp";
                    if (sfd.ShowDialog() == DialogResult.OK)
                    {
                        processedImage.Save(sfd.FileName);
                    }
                }
            }
        }

        private void сбросToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (originalImage != null)
            {
                processedImage = new Bitmap(originalImage);
                UpdateProcessedImages();

                trackBar1.Value = 0;
                trackBar2.Value = 255;
                trackBar3.Value = 50;
                UpdateMinMaxLabels();
                UpdateThresholdLabel();
            }
        }
    }
}