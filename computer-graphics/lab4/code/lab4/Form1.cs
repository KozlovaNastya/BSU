using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace lab4
{
    public partial class Form1 : Form
    {
        private List<LineSegment> lines = new List<LineSegment>();
        private Bitmap canvas;
        private Graphics graphics;
        private int scale = 10;
        private bool drawingLine = false;
        private Point startPoint;

        private class LineSegment
        {
            public Point Start { get; set; }
            public Point End { get; set; }
            public int AlgorithmType { get; set; }
            public Color Color { get; set; }

            public int Thickness { get; set; }
        }

        public Form1()
        {
            InitializeComponent();
            numericUpDown1.ValueChanged += numericUpDown1_ValueChanged;
            checkBox1.CheckedChanged += checkBox1_CheckedChanged;
            panel1.Resize += panel1_Resize;
            panel1.MouseClick += panel1_MouseClick;
            InitializeCanvas();
        }

        private void InitializeCanvas()
        {
            if (panel1.Width > 0 && panel1.Height > 0)
            {
                canvas = new Bitmap(panel1.Width, panel1.Height);
                graphics = Graphics.FromImage(canvas);
                RedrawAll();
            }
        }

        private void RedrawAll()
        {
            if (graphics == null) return;

            graphics.Clear(Color.White);

            DrawCoordinateSystem();

            foreach (var line in lines)
            {
                DrawLineSegment(line);
            }

            panel1.BackgroundImage = canvas;
            panel1.Invalidate();
        }

        private void DrawCoordinateSystem()
        {
            if (graphics == null) return;

            int centerX = panel1.Width / 2;
            int centerY = panel1.Height / 2;


            if (checkBox1.Checked)
            {
                Pen gridPen = new Pen(Color.LightGray, 1);

                for (int x = centerX; x < panel1.Width; x += scale)
                {
                    graphics.DrawLine(gridPen, x, 0, x, panel1.Height);
                    int mirrorX = centerX - (x - centerX);
                    if (mirrorX > 0)
                        graphics.DrawLine(gridPen, mirrorX, 0, mirrorX, panel1.Height);
                }

                for (int y = centerY; y < panel1.Height; y += scale)
                {
                    graphics.DrawLine(gridPen, 0, y, panel1.Width, y);
                    int mirrorY = centerY - (y - centerY);
                    if (mirrorY > 0)
                        graphics.DrawLine(gridPen, 0, mirrorY, panel1.Width, mirrorY);
                }
            }

            Pen axisPen = new Pen(Color.Black, 2);
            graphics.DrawLine(axisPen, 0, centerY, panel1.Width, centerY);
            graphics.DrawLine(axisPen, centerX, 0, centerX, panel1.Height);

            Font font = new Font("Arial", 8, FontStyle.Bold);
            graphics.DrawString("X", font, Brushes.Black, panel1.Width - 15, centerY - 15);
            graphics.DrawString("Y", font, Brushes.Black, centerX + 5, 5);
        }

        private void panel1_MouseClick(object sender, MouseEventArgs e)
        {
            if (!drawingLine)
            {
                startPoint = ConvertToLogicalCoordinates(e.Location);
                drawingLine = true;
                label1.Text = $"Начальная точка:\nX: {startPoint.X}\nY: {startPoint.Y}";
            }
            else
            {
                Point endPoint = ConvertToLogicalCoordinates(e.Location);
                drawingLine = false;
                label1.Text = $"Отрезок:\nНачало: ({startPoint.X}, {startPoint.Y})\nКонец: ({endPoint.X}, {endPoint.Y})";

                DrawAndSaveLine(startPoint, endPoint);
            }
        }

        private Point ConvertToLogicalCoordinates(Point screenPoint)
        {
            int centerX = panel1.Width / 2;
            int centerY = panel1.Height / 2;

            int logicalX = (screenPoint.X - centerX) / scale;
            int logicalY = (centerY - screenPoint.Y) / scale;

            return new Point(logicalX, logicalY);
        }

        private Point ConvertToScreenCoordinates(Point logicalPoint)
        {
            int centerX = panel1.Width / 2;
            int centerY = panel1.Height / 2;

            int screenX = centerX + logicalPoint.X * scale;
            int screenY = centerY - logicalPoint.Y * scale;

            return new Point(screenX, screenY);
        }

        
        private void DrawPixel(int x, int y, Color color)
        {
            if (graphics == null) return;

            Point screenPoint = ConvertToScreenCoordinates(new Point(x, y));

            if (screenPoint.X >= 0 && screenPoint.X < panel1.Width &&
                screenPoint.Y >= 0 && screenPoint.Y < panel1.Height)
            {
                graphics.FillRectangle(new SolidBrush(color),
                    screenPoint.X - scale / 2,
                    screenPoint.Y - scale / 2,
                    scale, scale);
            }
        }

        private void DrawAndSaveLine(Point start, Point end)
        {
            if (comboBox1.SelectedIndex == -1)
            {
                MessageBox.Show("Выберите алгоритм");
                return;
            }

            Stopwatch stopwatch = new Stopwatch();
            stopwatch.Start();

            var line = new LineSegment
            {
                Start = start,
                End = end,
                AlgorithmType = comboBox1.SelectedIndex,
                Color = GetAlgorithmColor(comboBox1.SelectedIndex),
            };

            DrawLineSegment(line);

            lines.Add(line);

            stopwatch.Stop();

            panel1.Invalidate();

            MessageBox.Show($"Алгоритм '{comboBox1.SelectedItem}' выполнен за {stopwatch.ElapsedTicks} тиков");
        }

        private void DrawLineSegment(LineSegment line)
        {
            switch (line.AlgorithmType)
            {
                case 0: StepByStepAlgorithm(line.Start, line.End, line.Color); break;
                case 1: DDAAlgorithm(line.Start, line.End, line.Color); break;
                case 2: BresenhamLineAlgorithm(line.Start, line.End, line.Color); break;
                case 3: BresenhamCircleAlgorithm(line.Start, line.End, line.Color); break;
                case 4: WuLineAlgorithm(line.Start, line.End, line.Color); break;
                case 5: CastlePitwayAlgorithm(line.Start, line.End, line.Color, line.Thickness); break;
            }
        }

        private Color GetAlgorithmColor(int algorithmIndex)
        {
            switch (algorithmIndex)
            {
                case 0: return Color.Red;
                case 1: return Color.Blue;
                case 2: return Color.Green;
                case 3: return Color.Purple;
                case 4: return Color.Orange;
                case 5: return Color.Magenta;
                default: return Color.Black;
            }
        }

        // 1. Пошаговый алгоритм
        private void StepByStepAlgorithm(Point start, Point end, Color color)
        {
            int x1 = start.X, y1 = start.Y;
            int x2 = end.X, y2 = end.Y;

            if (x1 == x2 && y1 == y2)
            {
                DrawPixel(x1, y1, color);
                return;
            }

            double k = (double)(y2 - y1) / (x2 - x1);
            double b = y1 - k * x1;

            if (Math.Abs(x2 - x1) >= Math.Abs(y2 - y1))
            {
                if (x1 > x2) { Swap(ref x1, ref x2); }
                for (int x = x1; x <= x2; x++)
                {
                    int y = (int)Math.Round(k * x + b);
                    DrawPixel(x, y, color);
                }
            }
            else
            {
                if (y1 > y2) { Swap(ref y1, ref y2); }
                for (int y = y1; y <= y2; y++)
                {
                    int x = (int)Math.Round((y - b) / k);
                    DrawPixel(x, y, color);
                }
            }
        }

        // 2. Алгоритм ЦДА
        private void DDAAlgorithm(Point start, Point end, Color color)
        {
            int x1 = start.X, y1 = start.Y;
            int x2 = end.X, y2 = end.Y;

            int dx = x2 - x1;
            int dy = y2 - y1;
            int steps = Math.Max(Math.Abs(dx), Math.Abs(dy));

            if (steps == 0)
            {
                DrawPixel(x1, y1, color);
                return;
            }

            float xIncrement = (float)dx / steps;
            float yIncrement = (float)dy / steps;

            float x = x1;
            float y = y1;

            for (int i = 0; i <= steps; i++)
            {
                DrawPixel((int)Math.Round(x), (int)Math.Round(y), color);
                x += xIncrement;
                y += yIncrement;
            }
        }

        // 3. Алгоритм Брезенхема для отрезка
        private void BresenhamLineAlgorithm(Point start, Point end, Color color)
        {
            int x1 = start.X, y1 = start.Y;
            int x2 = end.X, y2 = end.Y;

            int dx = Math.Abs(x2 - x1);
            int dy = Math.Abs(y2 - y1);
            int sx = x1 < x2 ? 1 : -1;
            int sy = y1 < y2 ? 1 : -1;
            int err = dx - dy;

            while (true)
            {
                DrawPixel(x1, y1, color);

                if (x1 == x2 && y1 == y2) break;

                int e2 = 2 * err;
                if (e2 > -dy)
                {
                    err -= dy;
                    x1 += sx;
                }
                if (e2 < dx)
                {
                    err += dx;
                    y1 += sy;
                }
            }
        }

        // 4. Алгоритм Брезенхема для окружности
        private void BresenhamCircleAlgorithm(Point start, Point end, Color color)
        {
            int x0 = start.X, y0 = start.Y;
            int radius = (int)Math.Sqrt(Math.Pow(end.X - start.X, 2) + Math.Pow(end.Y - start.Y, 2));

            if (radius == 0)
            {
                DrawPixel(x0, y0, color);
                return;
            }

            int x = 0;
            int y = radius;
            int delta = 1 - 2 * radius;
            int error = 0;

            while (y >= 0)
            {
                DrawCirclePoints(x0, y0, x, y, color);

                error = 2 * (delta + y) - 1;

                if (delta < 0 && error <= 0)
                {
                    x++;
                    delta += 2 * x + 1;
                    continue;
                }

                if (delta > 0 && error > 0)
                {
                    y--;
                    delta -= 2 * y + 1;
                    continue;
                }

                x++;
                delta += 2 * (x - y);
                y--;
            }
        }

        // 5. Алгоритм Ву
        private void WuLineAlgorithm(Point start, Point end, Color baseColor)
        {
            int x0 = start.X, y0 = start.Y;
            int x1 = end.X, y1 = end.Y;

            void DrawPixelWithAlpha(int xx, int yy, float alpha)
            {
                Color blendedColor = BlendColors(baseColor, Color.White, alpha);
                DrawPixel(xx, yy, blendedColor);
            }

            if (x0 == x1)
            {
                if (y0 > y1) Swap(ref y0, ref y1);
                for (int yCoord = y0; yCoord <= y1; yCoord++)
                {
                    DrawPixel(x0, yCoord, baseColor);
                }
                return;
            }

            if (y0 == y1)
            {
                if (x0 > x1) Swap(ref x0, ref x1);
                for (int xCoord = x0; xCoord <= x1; xCoord++)
                {
                    DrawPixel(xCoord, y0, baseColor);
                }
                return;
            }

            bool steep = Math.Abs(y1 - y0) > Math.Abs(x1 - x0);

            if (steep)
            {
                Swap(ref x0, ref y0);
                Swap(ref x1, ref y1);
            }

            if (x0 > x1)
            {
                Swap(ref x0, ref x1);
                Swap(ref y0, ref y1);
            }

            float dx = x1 - x0;
            float dy = y1 - y0;
            float gradient = dy / dx;

            float currentY = y0 + gradient;

            if (steep)
            {
                DrawPixelWithAlpha((int)y0, x0, 1 - (y0 - (int)y0));
                DrawPixelWithAlpha((int)y0 + 1, x0, y0 - (int)y0);
            }
            else
            {
                DrawPixelWithAlpha(x0, (int)y0, 1 - (y0 - (int)y0));
                DrawPixelWithAlpha(x0, (int)y0 + 1, y0 - (int)y0);
            }

            for (int x = x0 + 1; x < x1; x++)
            {
                if (steep)
                {
                    DrawPixelWithAlpha((int)currentY, x, 1 - (currentY - (int)currentY));
                    DrawPixelWithAlpha((int)currentY + 1, x, currentY - (int)currentY);
                }
                else
                {
                    DrawPixelWithAlpha(x, (int)currentY, 1 - (currentY - (int)currentY));
                    DrawPixelWithAlpha(x, (int)currentY + 1, currentY - (int)currentY);
                }
                currentY += gradient;
            }

            if (steep)
            {
                DrawPixelWithAlpha((int)y1, x1, 1 - (y1 - (int)y1));
                DrawPixelWithAlpha((int)y1 + 1, x1, y1 - (int)y1);
            }
            else
            {
                DrawPixelWithAlpha(x1, (int)y1, 1 - (y1 - (int)y1));
                DrawPixelWithAlpha(x1, (int)y1 + 1, y1 - (int)y1);
            }
        }

        // 6. Алгоритм Кастла-Питвея
        //private void CastlePitwayAlgorithm(Point start, Point end, Color color, int thickness)
        //{
        //    int x0 = start.X, y0 = start.Y;
        //    int x1 = end.X, y1 = end.Y;

        //    int a = Math.Abs(x1 - x0);
        //    int b = Math.Abs(y1 - y0);

        //    int sx = x0 < x1 ? 1 : -1;
        //    int sy = y0 < y1 ? 1 : -1;

        //    if (a == 0 && b == 0)
        //    {
        //        DrawPixel(x0, y0, color);
        //        return;
        //    }

        //    if (a == 0)
        //    {
        //        for (int yCoord = Math.Min(y0, y1); yCoord <= Math.Max(y0, y1); yCoord++)
        //        {
        //            DrawPixel(x0, yCoord, color);
        //        }
        //        return;
        //    }

        //    if (b == 0)
        //    {
        //        for (int xCoord = Math.Min(x0, x1); xCoord <= Math.Max(x0, x1); xCoord++)
        //        {
        //            DrawPixel(xCoord, y0, color);
        //        }
        //        return;
        //    }
        //    int f = 0;
        //    if (a < b)
        //    {
        //        f = 1;
        //        a ^= b;
        //        b ^= a;
        //        a ^= b;
        //    }// a > b

        //    string m1 = "s";
        //    string m2 = "d";

        //    int xVal = a-b;
        //    int yVal = b;

        //    while (xVal != yVal)
        //    {
        //        if (xVal > yVal)
        //        {
        //            xVal = xVal - yVal;
        //            m2 = Concatenate(m1, Invert(m2));
        //        }
        //        else
        //        {
        //            yVal = yVal - xVal;
        //            m1 = Concatenate(m2, Invert(m1));
        //        }
        //    }

        //    string m = Concatenate(m2, Invert(m1));
        //    string code = "";
        //    for (int i = 0; i < xVal; i++)
        //        code = Concatenate(code, m);
        //    Console.WriteLine(code);
        //    int currentX = x0;
        //    int currentY = y0;

        //    DrawPixel(currentX, currentY, color);

        //    foreach (char move in code)
        //    {
        //        if (move == 's')
        //        {
        //            if (f==1)
        //             currentY += sy;
        //            else
        //                currentX += sx;
        //        }
        //        else
        //        {
        //            currentX += sx;
        //            currentY += sy;
        //        }
        //        DrawPixel(currentX, currentY, color);
        //    }
        //}

        private void CastlePitwayAlgorithm(Point start, Point end, Color color, int thickness)
        {
            int x0 = start.X, y0 = start.Y;
            int x1 = end.X, y1 = end.Y;

            int dx = Math.Abs(x1 - x0);
            int dy = Math.Abs(y1 - y0);

            int sx = x0 < x1 ? 1 : -1;
            int sy = y0 < y1 ? 1 : -1;

            if (dx == 0 && dy == 0)
            {
                DrawPixel(x0, y0, color);
                return;
            }

            if (dx == 0)
            {
                for (int y = y0; y != y1 + sy; y += sy)
                {
                    DrawPixel(x0, y, color);
                }
                return;
            }

            if (dy == 0)
            {
                for (int x = x0; x != x1 + sx; x += sx)
                {
                    DrawPixel(x, y0, color);
                }
                return;
            }

            bool steep = dy > dx;
            if (steep)
            {
                (dx, dy) = (dy, dx);
            }

            string pattern = GenerateCastlePitwayPattern(dx, dy);

            int currentX = x0;
            int currentY = y0;

            DrawPixel(currentX, currentY, color);

            foreach (char move in pattern)
            {
                if (steep)
                {
                    if (move == 's')
                        currentY += sy;
                    else
                    {
                        currentX += sx;
                        currentY += sy;
                    }
                }
                else
                {
                    if (move == 's')
                        currentX += sx;
                    else
                    {
                        currentX += sx;
                        currentY += sy;
                    }
                }

                DrawPixel(currentX, currentY, color);
            }

            if (currentX != x1 || currentY != y1)
            {
                DrawPixel(x1, y1, color);
            }
        }

        private string GenerateCastlePitwayPattern(int dx, int dy)
        {
            if (dy == 0) return new string('s', dx);
            if (dx == dy) return new string('d', dx);

            StringBuilder pattern = new StringBuilder();
            int error = dx / 2;

            for (int i = 0; i < dx; i++)
            {
                error -= dy;
                if (error < 0)
                {
                    pattern.Append('d');
                    error += dx;
                }
                else
                {
                    pattern.Append('s');
                }
            }

            return pattern.ToString();
        }

        private Color BlendColors(Color color1, Color color2, float ratio)
        {
            if (ratio < 0) ratio = 0;
            if (ratio > 1) ratio = 1;

            float invRatio = 1 - ratio;

            int r = (int)(color1.R * ratio + color2.R * invRatio);
            int g = (int)(color1.G * ratio + color2.G * invRatio);
            int b = (int)(color1.B * ratio + color2.B * invRatio);

            r = Math.Min(255, Math.Max(0, r));
            g = Math.Min(255, Math.Max(0, g));
            b = Math.Min(255, Math.Max(0, b));

            return Color.FromArgb(r, g, b);
        }

        private void DrawCirclePoints(int x0, int y0, int x, int y, Color color)
        {
            DrawPixel(x0 + x, y0 + y, color);
            DrawPixel(x0 + x, y0 - y, color);
            DrawPixel(x0 - x, y0 + y, color);
            DrawPixel(x0 - x, y0 - y, color);
        }

        private void Swap(ref int a, ref int b)
        {
            int temp = a;
            a = b;
            b = temp;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Point start = new Point(-10, -5);
            Point end = new Point(15, 10);
            DrawAndSaveLine(start, end);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            lines.Clear();
            RedrawAll();
        }

        private void numericUpDown1_ValueChanged(object sender, EventArgs e)
        {
            scale = (int)numericUpDown1.Value;
            RedrawAll();
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            RedrawAll();
        }

        private void panel1_Resize(object sender, EventArgs e)
        {
            InitializeCanvas();
        }
    }
}