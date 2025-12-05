using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Windows.Forms;

namespace lab5
{
    public partial class Form1 : Form
    {
        private List<Line> segments = new List<Line>();
        private Rectangle clippingWindow;
        private Polygon clippingPolygon = null;
        private List<Polygon> polygons = new List<Polygon>();

        private readonly Color originalColor = Color.Blue;
        private readonly Color clippedColor = Color.Red;
        private readonly Color windowColor = Color.Green;

        public Form1()
        {
            InitializeComponent();
        }

        private void очисттьToolStripMenuItem_Click(object sender, EventArgs e)
        {
            segments.Clear();
            polygons.Clear();
            clippingWindow = new Rectangle();
            clippingPolygon = null;

            pictureBox1.Image = null;
            pictureBox2.Image = null;
        }
        private void DrawOriginalData()
        {
            Bitmap bmp1 = new Bitmap(pictureBox1.Width, pictureBox1.Height);
            Bitmap bmp2 = new Bitmap(pictureBox2.Width, pictureBox2.Height);

            using (Graphics g1 = Graphics.FromImage(bmp1))
            using (Graphics g2 = Graphics.FromImage(bmp2))
            {
                g1.Clear(Color.White);
                g2.Clear(Color.White);

                DrawCoordinateSystem(g1);
                DrawCoordinateSystem(g2);

                if (!clippingWindow.IsEmpty)
                {
                    Rectangle transformedWindow = TransformRectangle(clippingWindow, pictureBox1.Width, pictureBox1.Height);
                    g1.DrawRectangle(new Pen(windowColor, 2), transformedWindow);

                    foreach (var segment in segments)
                    {
                        System.Drawing.Point p1 = TransformPoint(segment.Start, pictureBox1.Width, pictureBox1.Height);
                        System.Drawing.Point p2 = TransformPoint(segment.End, pictureBox1.Width, pictureBox1.Height);
                        g1.DrawLine(new Pen(originalColor, 1), p1, p2);
                    }
                }

                if (clippingPolygon != null && clippingPolygon.Points.Count >= 3)
                {
                    DrawPolygon(g2, clippingPolygon, pictureBox2.Width, pictureBox2.Height, windowColor);

                    foreach (var segment in segments)
                    {
                        System.Drawing.Point p3 = TransformPoint(segment.Start, pictureBox2.Width, pictureBox2.Height);
                        System.Drawing.Point p4 = TransformPoint(segment.End, pictureBox2.Width, pictureBox2.Height);
                        g2.DrawLine(new Pen(originalColor, 1), p3, p4);
                    }
                }
            }

            pictureBox1.Image = bmp1;
            pictureBox2.Image = bmp2;
        }

        private void часть1ToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            ProcessPart1();
        }

        private void часть2ToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            ProcessPart2();
        }

        private void ProcessPart1()
        {
            if (segments.Count == 0) return;

            if (clippingWindow.IsEmpty)
            {
                MessageBox.Show("Для части 1 необходимо загрузить файл с отсекающим окном!", "Предупреждение",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }

            Bitmap bmp = new Bitmap(pictureBox1.Width, pictureBox1.Height);

            using (Graphics g = Graphics.FromImage(bmp))
            {
                g.Clear(Color.White);
                DrawCoordinateSystem(g);

                Rectangle transformedWindow = TransformRectangle(clippingWindow, pictureBox1.Width, pictureBox1.Height);
                g.DrawRectangle(new Pen(windowColor, 2), transformedWindow);

                foreach (var segment in segments)
                {
                    Line clipped = CohenSutherlandClip(segment);
                    if (clipped != null)
                    {
                        System.Drawing.Point p1 = TransformPoint(clipped.Start, pictureBox1.Width, pictureBox1.Height);
                        System.Drawing.Point p2 = TransformPoint(clipped.End, pictureBox1.Width, pictureBox1.Height);
                        g.DrawLine(new Pen(clippedColor, 2), p1, p2);
                    }
                }
            }

            pictureBox1.Image = bmp;
        }

        private void ProcessPart2()
        {
            if (segments.Count == 0) return;

            if (clippingPolygon == null || clippingPolygon.Points.Count < 3)
            {
                MessageBox.Show("Для части 2 необходимо загрузить файл с многоугольником!", "Предупреждение",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }

            Bitmap bmp = new Bitmap(pictureBox2.Width, pictureBox2.Height);

            using (Graphics g = Graphics.FromImage(bmp))
            {
                g.Clear(Color.White);

                DrawCoordinateSystem(g);

                Polygon clipPolygon = clippingPolygon;

                DrawPolygon(g, clipPolygon, pictureBox2.Width, pictureBox2.Height, windowColor);

                foreach (var segment in segments)
                {
                    List<Line> clippedLines = ClipLineByPolygon(segment, clipPolygon);

                    foreach (var clippedLine in clippedLines)
                    {
                        System.Drawing.Point p1 = TransformPoint(clippedLine.Start, pictureBox2.Width, pictureBox2.Height);
                        System.Drawing.Point p2 = TransformPoint(clippedLine.End, pictureBox2.Width, pictureBox2.Height);
                        g.DrawLine(new Pen(clippedColor, 2), p1, p2);
                    }
                }
            }

            pictureBox2.Image = bmp;
        }

        private Rectangle TransformRectangle(Rectangle rect, int width, int height)
        {
            int centerX = width / 2;
            int centerY = height / 2;

            int x = centerX + rect.X;
            int y = centerY - rect.Y - rect.Height;
            return new Rectangle(x, y, rect.Width, rect.Height);
        }

        private void DrawCoordinateSystem(Graphics g)
        {
            int centerX = pictureBox1.Width / 2;
            int centerY = pictureBox1.Height / 2;

            g.DrawLine(Pens.Black, 0, centerY, pictureBox1.Width, centerY);
            g.DrawLine(Pens.Black, centerX, 0, centerX, pictureBox1.Height);

            g.DrawLine(Pens.Black, pictureBox1.Width - 10, centerY - 5, pictureBox1.Width, centerY);
            g.DrawLine(Pens.Black, pictureBox1.Width - 10, centerY + 5, pictureBox1.Width, centerY);
            g.DrawLine(Pens.Black, centerX - 5, 10, centerX, 0);
            g.DrawLine(Pens.Black, centerX + 5, 10, centerX, 0);
        }

        private System.Drawing.Point TransformPoint(MyPoint point, int width, int height)
        {
            int centerX = width / 2;
            int centerY = height / 2;
            return new System.Drawing.Point(centerX + (int)point.X, centerY - (int)point.Y);
        }

        private Line CohenSutherlandClip(Line line)
        {
            const int INSIDE = 0;
            const int LEFT = 1;
            const int RIGHT = 2;
            const int BOTTOM = 4;
            const int TOP = 8;

            if (clippingWindow.IsEmpty) return null;

            double xMin = clippingWindow.Left;
            double xMax = clippingWindow.Right;
            double yMin = clippingWindow.Top;
            double yMax = clippingWindow.Bottom;

            int ComputeOutCode(double x, double y)
            {
                int code = INSIDE;
                if (x < xMin) code |= LEFT;
                else if (x > xMax) code |= RIGHT;
                if (y < yMin) code |= BOTTOM;
                else if (y > yMax) code |= TOP;
                return code;
            }

            double x0 = line.Start.X;
            double y0 = line.Start.Y;
            double x1 = line.End.X;
            double y1 = line.End.Y;

            int outCode0 = ComputeOutCode(x0, y0);
            int outCode1 = ComputeOutCode(x1, y1);
            bool accept = false;

            while (true)
            {
                if ((outCode0 | outCode1) == 0)
                {
                    accept = true;
                    break;
                }
                else if ((outCode0 & outCode1) != 0)
                {
                    break;
                }
                else
                {
                    double x = 0, y = 0;
                    int outCodeOut = outCode0 != 0 ? outCode0 : outCode1;

                    if ((outCodeOut & TOP) != 0)
                    {
                        x = x0 + (x1 - x0) * (yMax - y0) / (y1 - y0);
                        y = yMax;
                    }
                    else if ((outCodeOut & BOTTOM) != 0)
                    {
                        x = x0 + (x1 - x0) * (yMin - y0) / (y1 - y0);
                        y = yMin;
                    }
                    else if ((outCodeOut & RIGHT) != 0)
                    {
                        y = y0 + (y1 - y0) * (xMax - x0) / (x1 - x0);
                        x = xMax;
                    }
                    else if ((outCodeOut & LEFT) != 0)
                    {
                        y = y0 + (y1 - y0) * (xMin - x0) / (x1 - x0);
                        x = xMin;
                    }

                    if (outCodeOut == outCode0)
                    {
                        x0 = x; y0 = y;
                        outCode0 = ComputeOutCode(x0, y0);
                    }
                    else
                    {
                        x1 = x; y1 = y;
                        outCode1 = ComputeOutCode(x1, y1);
                    }
                }
            }

            return accept ? new Line(new MyPoint(x0, y0), new MyPoint(x1, y1)) : null;
        }

        private List<Line> ClipLineByPolygon(Line line, Polygon clipPolygon)
        {
            if (clipPolygon == null || clipPolygon.Points.Count < 3)
                return new List<Line>();

            List<MyPoint> inputList = new List<MyPoint> { line.Start, line.End };
            List<MyPoint> outputList = new List<MyPoint>();

            for (int i = 0; i < clipPolygon.Points.Count; i++)
            {
                MyPoint p1 = clipPolygon.Points[i];
                MyPoint p2 = clipPolygon.Points[(i + 1) % clipPolygon.Points.Count];

                outputList.Clear();

                if (inputList.Count == 0) break;

                MyPoint S = inputList[inputList.Count - 1];

                foreach (MyPoint E in inputList)
                {
                    if (IsInside(E, p1, p2))
                    {
                        if (!IsInside(S, p1, p2))
                        {
                            MyPoint intersection = ComputeIntersection(S, E, p1, p2);
                            if (intersection != null)
                                outputList.Add(intersection);
                        }
                        outputList.Add(E);
                    }
                    else if (IsInside(S, p1, p2))
                    {
                        MyPoint intersection = ComputeIntersection(S, E, p1, p2);
                        if (intersection != null)
                            outputList.Add(intersection);
                    }
                    S = E;
                }

                inputList = new List<MyPoint>(outputList);
            }
            List<Line> result = new List<Line>();
            for (int i = 0; i < outputList.Count - 1; i += 1)
            {
                result.Add(new Line(outputList[i], outputList[i + 1]));
            }

            return result;
        }

        private bool IsInside(MyPoint point, MyPoint edgeStart, MyPoint edgeEnd)
        {
            double crossProduct = (edgeEnd.X - edgeStart.X) * (point.Y - edgeStart.Y)
                                - (edgeEnd.Y - edgeStart.Y) * (point.X - edgeStart.X);
            return crossProduct <= 0;
        }

        private MyPoint ComputeIntersection(MyPoint lineStart, MyPoint lineEnd, MyPoint edgeStart, MyPoint edgeEnd)
        {
            double x1 = lineStart.X, y1 = lineStart.Y;
            double x2 = lineEnd.X, y2 = lineEnd.Y;
            double x3 = edgeStart.X, y3 = edgeStart.Y;
            double x4 = edgeEnd.X, y4 = edgeEnd.Y;

            double denominator = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

            if (Math.Abs(denominator) < 1e-10)
                return null;

            double t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / denominator;

            if (t < 0 || t > 1)
                return null;

            double x = x1 + t * (x2 - x1);
            double y = y1 + t * (y2 - y1);

            return new MyPoint(x, y);
        }

        private void DrawPolygon(Graphics g, Polygon polygon, int width, int height, Color color)
        {
            if (polygon == null || polygon.Points.Count < 3) return;
            List<System.Drawing.Point> points = new List<System.Drawing.Point>();
            foreach (var point in polygon.Points)
                points.Add(TransformPoint(point, width, height));
            points.Add(TransformPoint(polygon.Points[0], width, height));
            g.DrawPolygon(new Pen(color, 2), points.ToArray());
        }

        private void часть1ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog
            {
                Filter = "Text files (*.txt)|*.txt|All files (*.*)|*.*",
                Title = "Выберите файл с данными для части 1"
            };

            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                try
                {
                    LoadDataForPart1(openFileDialog.FileName);
                    DrawOriginalData();
                }
                catch (Exception ex)
                {
                    MessageBox.Show($"Ошибка загрузки файла: {ex.Message}", "Ошибка",
                        MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
        }

        private void часть2ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog
            {
                Filter = "Text files (*.txt)|*.txt|All files (*.*)|*.*",
                Title = "Выберите файл с данными для части 2"
            };

            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                try
                {
                    LoadDataForPart2(openFileDialog.FileName);
                    DrawOriginalData();
                }
                catch (Exception ex)
                {
                    MessageBox.Show($"Ошибка загрузки файла: {ex.Message}", "Ошибка",
                        MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
        }

        private void LoadDataForPart1(string filename)
        {
            segments.Clear();
            clippingPolygon = null;

            string[] lines = File.ReadAllLines(filename);
            int index = 0;

            int n = int.Parse(lines[index++].Trim());
            for (int i = 0; i < n; i++)
            {
                string[] coordinates = lines[index++].Split(new[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
                if (coordinates.Length >= 4)
                {
                    segments.Add(new Line(
                        new MyPoint(double.Parse(coordinates[0]), double.Parse(coordinates[1])),
                        new MyPoint(double.Parse(coordinates[2]), double.Parse(coordinates[3]))
                    ));
                }
            }

            if (index < lines.Length)
            {
                string[] windowCoordinates = lines[index++].Split(new[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
                if (windowCoordinates.Length >= 4)
                {
                    clippingWindow = new Rectangle(
                        (int)double.Parse(windowCoordinates[0]),
                        (int)double.Parse(windowCoordinates[1]),
                        (int)(double.Parse(windowCoordinates[2]) - double.Parse(windowCoordinates[0])),
                        (int)(double.Parse(windowCoordinates[3]) - double.Parse(windowCoordinates[1]))
                    );
                }
            }
        }

        private void LoadDataForPart2(string filename)
        {
            segments.Clear();
            clippingWindow = new Rectangle();

            string[] lines = File.ReadAllLines(filename);
            int index = 0;

            int n = int.Parse(lines[index++].Trim());
            for (int i = 0; i < n; i++)
            {
                string[] coordinates = lines[index++].Split(new[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
                if (coordinates.Length >= 4)
                {
                    segments.Add(new Line(
                        new MyPoint(double.Parse(coordinates[0]), double.Parse(coordinates[1])),
                        new MyPoint(double.Parse(coordinates[2]), double.Parse(coordinates[3]))
                    ));
                }
            }

            clippingPolygon = new Polygon();
            while (index < lines.Length)
            {
                string[] polyCoordinates = lines[index++].Split(new[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
                if (polyCoordinates.Length >= 2)
                {
                    clippingPolygon.Points.Add(new MyPoint(
                        double.Parse(polyCoordinates[0]),
                        double.Parse(polyCoordinates[1])
                    ));
                }
            }
        }

        public class MyPoint
        {
            public double X { get; set; }
            public double Y { get; set; }
            public MyPoint(double x, double y) { X = x; Y = y; }
        }

        public class Line
        {
            public MyPoint Start { get; set; }
            public MyPoint End { get; set; }
            public Line(MyPoint start, MyPoint end) { Start = start; End = end; }
        }

        public class Polygon
        {
            public List<MyPoint> Points { get; set; }
            public Polygon() { Points = new List<MyPoint>(); }
        }
    }
}