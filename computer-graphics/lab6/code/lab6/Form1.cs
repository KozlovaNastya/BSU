using System;
using System.Drawing;
using System.Windows.Forms;

namespace lab6
{
    public partial class Form1 : Form
    {
        private Point3D[] vertices;
        private int[,] edges;
        private float scale = 50.0f;
        private float offsetX, offsetY;
        private float rotationX, rotationY, rotationZ;
        private float translateX, translateY, translateZ;
        private float[,] transformationMatrix;

        // Панели для отдельных проекций
        private Panel projectionXY;
        private Panel projectionXZ;
        private Panel projectionYZ;

        // Элементы управления для проекций
        private TrackBar projXY_Zoom;
        private TrackBar projXY_X;
        private TrackBar projXY_Y;
        private TrackBar projXZ_Zoom;
        private TrackBar projXZ_X;
        private TrackBar projXZ_Y;
        private TrackBar projYZ_Zoom;
        private TrackBar projYZ_X;
        private TrackBar projYZ_Y;

        // Остальные элементы
        private Panel mainCanvas;
        private TrackBar trackBarScale;
        private TrackBar trackBarRotateX;
        private TrackBar trackBarRotateY;
        private TrackBar trackBarRotateZ;
        private TrackBar trackBarTranslateX;
        private TrackBar trackBarTranslateY;
        private TrackBar trackBarTranslateZ;
        private TextBox txtMatrix;
        private Button btnResetScale;
        private Button btnResetRotation;
        private Button btnResetTranslation;
        private Label lblScale;
        private Label lblRotateX;
        private Label lblRotateY;
        private Label lblRotateZ;
        private Label lblTranslateX;
        private Label lblTranslateY;
        private Label lblTranslateZ;

        // Параметры для проекций
        private float projXY_Scale = 8.0f;
        private float projXY_OffsetX = 0.0f;
        private float projXY_OffsetY = 0.0f;
        private float projXZ_Scale = 8.0f;
        private float projXZ_OffsetX = 0.0f;
        private float projXZ_OffsetY = 0.0f;
        private float projYZ_Scale = 8.0f;
        private float projYZ_OffsetX = 0.0f;
        private float projYZ_OffsetY = 0.0f;

        public Form1()
        {
            InitializeComponent();
            InitializeLetterK();
            InitializeTransformationMatrix();
            SetupEventHandlers();
        }

        private void InitializeComponent()
        {
            this.Text = "Лабораторная работа 6 - 3D Буква K";
            this.Size = new Size(1200, 850); // Увеличил высоту
            this.StartPosition = FormStartPosition.CenterScreen;

            mainCanvas = new Panel();
            mainCanvas.Location = new Point(10, 10);
            mainCanvas.Size = new Size(500, 400);
            mainCanvas.BorderStyle = BorderStyle.FixedSingle;
            mainCanvas.BackColor = Color.White;

            // Создаем панели для проекций
            projectionXY = new Panel();
            projectionXY.Location = new Point(520, 10);
            projectionXY.Size = new Size(200, 180);
            projectionXY.BorderStyle = BorderStyle.FixedSingle;
            projectionXY.BackColor = Color.White;

            projectionXZ = new Panel();
            projectionXZ.Location = new Point(730, 10);
            projectionXZ.Size = new Size(200, 180);
            projectionXZ.BorderStyle = BorderStyle.FixedSingle;
            projectionXZ.BackColor = Color.White;

            projectionYZ = new Panel();
            projectionYZ.Location = new Point(940, 10);
            projectionYZ.Size = new Size(200, 180);
            projectionYZ.BorderStyle = BorderStyle.FixedSingle;
            projectionYZ.BackColor = Color.White;

            // Панель с матрицей сдвинута вниз
            txtMatrix = new TextBox();
            txtMatrix.Location = new Point(520, 400); // Было 220, стало 400
            txtMatrix.Size = new Size(620, 150);
            txtMatrix.Multiline = true;
            txtMatrix.ScrollBars = ScrollBars.Vertical;
            txtMatrix.Font = new Font("Consolas", 9);
            txtMatrix.ReadOnly = true;

            // Создаем элементы управления для проекций (снижена начальная позиция)
            CreateProjectionControls(projectionXY.Location.X, projectionXY.Location.Y + 190,
                                   "XY", out projXY_Zoom, out projXY_X, out projXY_Y);

            CreateProjectionControls(projectionXZ.Location.X, projectionXZ.Location.Y + 190,
                                   "XZ", out projXZ_Zoom, out projXZ_X, out projXZ_Y);

            CreateProjectionControls(projectionYZ.Location.X, projectionYZ.Location.Y + 190,
                                   "YZ", out projYZ_Zoom, out projYZ_X, out projYZ_Y);

            // Основные элементы управления (сдвинуты вниз из-за панели с матрицей)
            lblScale = new Label() { Text = "Масштаб:", Location = new Point(10, 460), Size = new Size(90, 20) };
            trackBarScale = new TrackBar();
            trackBarScale.Location = new Point(100, 460);
            trackBarScale.Size = new Size(200, 45);
            trackBarScale.Minimum = 10;
            trackBarScale.Maximum = 200;
            trackBarScale.Value = 50;
            trackBarScale.TickFrequency = 10;

            btnResetScale = new Button();
            btnResetScale.Text = "Сброс";
            btnResetScale.Location = new Point(310, 460);
            btnResetScale.Size = new Size(60, 25);

            lblRotateX = new Label() { Text = "Вращение X:", Location = new Point(10, 510), Size = new Size(80, 20) };
            trackBarRotateX = new TrackBar();
            trackBarRotateX.Location = new Point(100, 510);
            trackBarRotateX.Size = new Size(200, 45);
            trackBarRotateX.Minimum = -180;
            trackBarRotateX.Maximum = 180;
            trackBarRotateX.TickFrequency = 30;

            lblRotateY = new Label() { Text = "Вращение Y:", Location = new Point(10, 560), Size = new Size(80, 20) };
            trackBarRotateY = new TrackBar();
            trackBarRotateY.Location = new Point(100, 560);
            trackBarRotateY.Size = new Size(200, 45);
            trackBarRotateY.Minimum = -180;
            trackBarRotateY.Maximum = 180;
            trackBarRotateY.TickFrequency = 30;

            lblRotateZ = new Label() { Text = "Вращение Z:", Location = new Point(10, 610), Size = new Size(80, 20) };
            trackBarRotateZ = new TrackBar();
            trackBarRotateZ.Location = new Point(100, 610);
            trackBarRotateZ.Size = new Size(200, 45);
            trackBarRotateZ.Minimum = -180;
            trackBarRotateZ.Maximum = 180;
            trackBarRotateZ.TickFrequency = 30;

            btnResetRotation = new Button();
            btnResetRotation.Text = "Сброс вращения";
            btnResetRotation.Location = new Point(310, 560);
            btnResetRotation.Size = new Size(100, 25);

            lblTranslateX = new Label() { Text = "Перенос X:", Location = new Point(10, 660), Size = new Size(80, 20) };
            trackBarTranslateX = new TrackBar();
            trackBarTranslateX.Location = new Point(100, 660);
            trackBarTranslateX.Size = new Size(200, 45);
            trackBarTranslateX.Minimum = -100;
            trackBarTranslateX.Maximum = 100;
            trackBarTranslateX.TickFrequency = 20;

            lblTranslateY = new Label() { Text = "Перенос Y:", Location = new Point(10, 710), Size = new Size(80, 20) };
            trackBarTranslateY = new TrackBar();
            trackBarTranslateY.Location = new Point(100, 710);
            trackBarTranslateY.Size = new Size(200, 45);
            trackBarTranslateY.Minimum = -100;
            trackBarTranslateY.Maximum = 100;
            trackBarTranslateY.TickFrequency = 20;

            lblTranslateZ = new Label() { Text = "Перенос Z:", Location = new Point(10, 760), Size = new Size(80, 20) };
            trackBarTranslateZ = new TrackBar();
            trackBarTranslateZ.Location = new Point(100, 760);
            trackBarTranslateZ.Size = new Size(200, 45);
            trackBarTranslateZ.Minimum = -100;
            trackBarTranslateZ.Maximum = 100;
            trackBarTranslateZ.TickFrequency = 20;

            btnResetTranslation = new Button();
            btnResetTranslation.Text = "Сброс переноса";
            btnResetTranslation.Location = new Point(310, 710);
            btnResetTranslation.Size = new Size(100, 25);

            this.Controls.AddRange(new Control[] {
                mainCanvas, projectionXY, projectionXZ, projectionYZ, txtMatrix,
                lblScale, trackBarScale, btnResetScale,
                lblRotateX, trackBarRotateX,
                lblRotateY, trackBarRotateY,
                lblRotateZ, trackBarRotateZ,
                btnResetRotation,
                lblTranslateX, trackBarTranslateX,
                lblTranslateY, trackBarTranslateY,
                lblTranslateZ, trackBarTranslateZ,
                btnResetTranslation
            });
        }

        private void CreateProjectionControls(int x, int y, string title,
                                    out TrackBar zoomTrack, out TrackBar xTrack, out TrackBar yTrack)
        {
            Label lblTitle = new Label()
            {
                Text = title,
                Location = new Point(x, y),
                Size = new Size(30, 20),
                Font = new Font("Arial", 9, FontStyle.Bold)
            };

            Label lblZoom = new Label()
            {
                Text = "Масштаб:",
                Location = new Point(x, y + 25),
                Size = new Size(60, 20)
            };

            zoomTrack = new TrackBar();
            zoomTrack.Location = new Point(x + 65, y + 25);
            zoomTrack.Size = new Size(120, 45);
            zoomTrack.Minimum = 1;
            zoomTrack.Maximum = 30;
            zoomTrack.Value = 8;
            zoomTrack.TickFrequency = 5;
            zoomTrack.Tag = title;

            Label lblX = new Label()
            {
                Text = "Смещ. X:",
                Location = new Point(x, y + 75),
                Size = new Size(60, 20)
            };

            xTrack = new TrackBar();
            xTrack.Location = new Point(x + 65, y + 75);
            xTrack.Size = new Size(120, 45);
            xTrack.Minimum = -100;
            xTrack.Maximum = 100;
            xTrack.Value = 0;
            xTrack.TickFrequency = 20;
            xTrack.Tag = title;

            Label lblY = new Label()
            {
                Text = "Смещ. Y:",
                Location = new Point(x, y + 125),
                Size = new Size(60, 20)
            };

            yTrack = new TrackBar();
            yTrack.Location = new Point(x + 65, y + 125);
            yTrack.Size = new Size(120, 45);
            yTrack.Minimum = -100;
            yTrack.Maximum = 100;
            yTrack.Value = 0;
            yTrack.TickFrequency = 20;
            yTrack.Tag = title;

            this.Controls.AddRange(new Control[] {
                lblTitle, lblZoom, zoomTrack, lblX, xTrack, lblY, yTrack
            });
        }

        private void InitializeLetterK()
        {
            vertices = new Point3D[]
            {
        new Point3D(-1, -2, -0.5f),
        new Point3D(-1, 2, -0.5f),
        new Point3D(-0.5f, -2, -0.5f),
        new Point3D(-0.5f, 2, -0.5f),

        new Point3D(-1, -2, 0.5f),
        new Point3D(-1, 2, 0.5f),
        new Point3D(-0.5f, -2, 0.5f),
        new Point3D(-0.5f, 2, 0.5f),

        new Point3D(1, 2, -0.5f),
        new Point3D(1, 1, -0.5f),
        new Point3D(1, -1, -0.5f),
        new Point3D(1, -2, -0.5f),

        new Point3D(1, 2, 0.5f),
        new Point3D(1, 1, 0.5f),
        new Point3D(1, -1, 0.5f),
        new Point3D(1, -2, 0.5f),

        new Point3D(-0.5f, 0.5f, -0.5f),
        new Point3D(-0.5f, 0.5f, 0.5f),
        new Point3D(-0.5f, -0.5f, -0.5f),
        new Point3D(-0.5f, -0.5f, 0.5f)
            };

            edges = new int[,]
            {
        {0, 1}, {2, 3}, {0, 2}, {1, 3},
        {4, 5}, {6, 7}, {4, 6}, {5, 7},
        {0, 4}, {1, 5}, {2, 6}, {3, 7},

        {3, 16}, {7, 17},
        {2, 18}, {6, 19},

        {16, 8}, {16, 9},
        {17, 12}, {17, 13},

        {18, 10}, {18, 11},
        {19, 14}, {19, 15},

        {8, 12}, {9, 13}, {10, 14}, {11, 15},

        {16, 17}, {18, 19},
        {8, 9}, {12, 13},
        {10, 11}, {14, 15}
            };

            offsetX = mainCanvas.Width / 2;
            offsetY = mainCanvas.Height / 2;
        }

        private void InitializeTransformationMatrix()
        {
            transformationMatrix = new float[4, 4];
            for (int i = 0; i < 4; i++)
                transformationMatrix[i, i] = 1.0f;
        }

        private void SetupEventHandlers()
        {
            trackBarScale.Scroll += (s, e) => { scale = trackBarScale.Value; UpdateTransformation(); };
            trackBarRotateX.Scroll += (s, e) => { rotationX = trackBarRotateX.Value; UpdateTransformation(); };
            trackBarRotateY.Scroll += (s, e) => { rotationY = trackBarRotateY.Value; UpdateTransformation(); };
            trackBarRotateZ.Scroll += (s, e) => { rotationZ = trackBarRotateZ.Value; UpdateTransformation(); };
            trackBarTranslateX.Scroll += (s, e) => { translateX = trackBarTranslateX.Value; UpdateTransformation(); };
            trackBarTranslateY.Scroll += (s, e) => { translateY = trackBarTranslateY.Value; UpdateTransformation(); };
            trackBarTranslateZ.Scroll += (s, e) => { translateZ = trackBarTranslateZ.Value; UpdateTransformation(); };

            projXY_Zoom.Scroll += (s, e) => { projXY_Scale = projXY_Zoom.Value; UpdateProjections(); };
            projXY_X.Scroll += (s, e) => { projXY_OffsetX = projXY_X.Value; UpdateProjections(); };
            projXY_Y.Scroll += (s, e) => { projXY_OffsetY = projXY_Y.Value; UpdateProjections(); };

            projXZ_Zoom.Scroll += (s, e) => { projXZ_Scale = projXZ_Zoom.Value; UpdateProjections(); };
            projXZ_X.Scroll += (s, e) => { projXZ_OffsetX = projXZ_X.Value; UpdateProjections(); };
            projXZ_Y.Scroll += (s, e) => { projXZ_OffsetY = projXZ_Y.Value; UpdateProjections(); };

            projYZ_Zoom.Scroll += (s, e) => { projYZ_Scale = projYZ_Zoom.Value; UpdateProjections(); };
            projYZ_X.Scroll += (s, e) => { projYZ_OffsetX = projYZ_X.Value; UpdateProjections(); };
            projYZ_Y.Scroll += (s, e) => { projYZ_OffsetY = projYZ_Y.Value; UpdateProjections(); };

            btnResetScale.Click += (s, e) => { trackBarScale.Value = 50; scale = 50; UpdateTransformation(); };
            btnResetRotation.Click += (s, e) =>
            {
                trackBarRotateX.Value = trackBarRotateY.Value = trackBarRotateZ.Value = 0;
                rotationX = rotationY = rotationZ = 0;
                UpdateTransformation();
            };
            btnResetTranslation.Click += (s, e) =>
            {
                trackBarTranslateX.Value = trackBarTranslateY.Value = trackBarTranslateZ.Value = 0;
                translateX = translateY = translateZ = 0;
                UpdateTransformation();
            };

            mainCanvas.Paint += MainCanvas_Paint;
            projectionXY.Paint += ProjectionXY_Paint;
            projectionXZ.Paint += ProjectionXZ_Paint;
            projectionYZ.Paint += ProjectionYZ_Paint;
        }

        private void UpdateTransformation()
        {
            InitializeTransformationMatrix();

            float scaleFactor = scale / 5.0f;
            float[,] scaleMatrix = {
                {scaleFactor, 0, 0, 0},
                {0, scaleFactor, 0, 0},
                {0, 0, scaleFactor, 0},
                {0, 0, 0, 1}
            };
            transformationMatrix = MultiplyMatrices(scaleMatrix, transformationMatrix);

            if (rotationX != 0)
            {
                float rx = rotationX * (float)Math.PI / 180.0f;
                float[,] rotX = {
                    {1, 0, 0, 0},
                    {0, (float)Math.Cos(rx), -(float)Math.Sin(rx), 0},
                    {0, (float)Math.Sin(rx), (float)Math.Cos(rx), 0},
                    {0, 0, 0, 1}
                };
                transformationMatrix = MultiplyMatrices(rotX, transformationMatrix);
            }

            if (rotationY != 0)
            {
                float ry = rotationY * (float)Math.PI / 180.0f;
                float[,] rotY = {
                    {(float)Math.Cos(ry), 0, (float)Math.Sin(ry), 0},
                    {0, 1, 0, 0},
                    {-(float)Math.Sin(ry), 0, (float)Math.Cos(ry), 0},
                    {0, 0, 0, 1}
                };
                transformationMatrix = MultiplyMatrices(rotY, transformationMatrix);
            }

            if (rotationZ != 0)
            {
                float rz = rotationZ * (float)Math.PI / 180.0f;
                float[,] rotZ = {
                    {(float)Math.Cos(rz), -(float)Math.Sin(rz), 0, 0},
                    {(float)Math.Sin(rz), (float)Math.Cos(rz), 0, 0},
                    {0, 0, 1, 0},
                    {0, 0, 0, 1}
                };
                transformationMatrix = MultiplyMatrices(rotZ, transformationMatrix);
            }

            if (translateX != 0 || translateY != 0 || translateZ != 0)
            {
                float[,] translateMatrix = {
                    {1, 0, 0, translateX * 0.1f},
                    {0, 1, 0, translateY * 0.1f},
                    {0, 0, 1, translateZ * 0.1f},
                    {0, 0, 0, 1}
                };
                transformationMatrix = MultiplyMatrices(translateMatrix, transformationMatrix);
            }

            UpdateMatrixDisplay();
            mainCanvas.Invalidate();
            UpdateProjections();
        }

        private void UpdateProjections()
        {
            projectionXY.Invalidate();
            projectionXZ.Invalidate();
            projectionYZ.Invalidate();
        }

        private float[,] MultiplyMatrices(float[,] a, float[,] b)
        {
            int rows = a.GetLength(0);
            int cols = b.GetLength(1);
            int common = a.GetLength(1);
            float[,] result = new float[rows, cols];

            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    float sum = 0;
                    for (int k = 0; k < common; k++)
                    {
                        sum += a[i, k] * b[k, j];
                    }
                    result[i, j] = sum;
                }
            }
            return result;
        }

        private void UpdateMatrixDisplay()
        {
            string matrixText = "Матрица преобразования:\r\n";
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    matrixText += $"{transformationMatrix[i, j]:F2}\t";
                }
                matrixText += "\r\n";
            }
            txtMatrix.Text = matrixText;
        }

        private void MainCanvas_Paint(object sender, PaintEventArgs e)
        {
            Graphics g = e.Graphics;
            g.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
            g.Clear(Color.White);

            DrawCoordinateSystem(g, mainCanvas.Width, mainCanvas.Height);

            Point3D[] transformedVertices = new Point3D[vertices.Length];
            for (int i = 0; i < vertices.Length; i++)
            {
                transformedVertices[i] = TransformPoint(vertices[i]);
            }

            using (Pen edgePen = new Pen(Color.Blue, 2))
            {
                for (int i = 0; i < edges.GetLength(0); i++)
                {
                    Point3D p1 = transformedVertices[edges[i, 0]];
                    Point3D p2 = transformedVertices[edges[i, 1]];

                    g.DrawLine(edgePen,
                        offsetX + p1.X, offsetY - p1.Y,
                        offsetX + p2.X, offsetY - p2.Y);
                }
            }

            using (Brush vertexBrush = new SolidBrush(Color.Red))
            {
                for (int i = 0; i < transformedVertices.Length; i++)
                {
                    float x = offsetX + transformedVertices[i].X;
                    float y = offsetY - transformedVertices[i].Y;
                    g.FillEllipse(vertexBrush, x - 2, y - 2, 4, 4);
                }
            }
        }

        private void ProjectionXY_Paint(object sender, PaintEventArgs e)
        {
            DrawProjection(e.Graphics, projectionXY,
                p => new PointF(
                    projectionXY.Width / 2 + p.X * projXY_Scale + projXY_OffsetX,
                    projectionXY.Height / 2 - p.Y * projXY_Scale + projXY_OffsetY),
                "XY (X-Y)");
        }

        private void ProjectionXZ_Paint(object sender, PaintEventArgs e)
        {
            DrawProjection(e.Graphics, projectionXZ,
                p => new PointF(
                    projectionXZ.Width / 2 + p.X * projXZ_Scale + projXZ_OffsetX,
                    projectionXZ.Height / 2 - p.Z * projXZ_Scale + projXZ_OffsetY),
                "XZ (X-Z)");
        }

        private void ProjectionYZ_Paint(object sender, PaintEventArgs e)
        {
            DrawProjection(e.Graphics, projectionYZ,
                p => new PointF(
                    projectionYZ.Width / 2 + p.Y * projYZ_Scale + projYZ_OffsetX,
                    projectionYZ.Height / 2 - p.Z * projYZ_Scale + projYZ_OffsetY),
                "YZ (Y-Z)");
        }

        private void DrawProjection(Graphics g, Panel panel, Func<Point3D, PointF> projection, string title)
        {
            g.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
            g.Clear(Color.White);

            // Рисуем заголовок
            using (var font = new Font("Arial", 10, FontStyle.Bold))
            using (var brush = new SolidBrush(Color.Black))
            {
                g.DrawString(title, font, brush, 5, 5);
            }

            Point3D[] transformedVertices = new Point3D[vertices.Length];
            for (int i = 0; i < vertices.Length; i++)
            {
                transformedVertices[i] = TransformPoint(vertices[i]);
            }

            // Рисуем оси координат для проекции
            DrawProjectionAxes(g, panel.Width, panel.Height, title);

            // Рисуем ребра
            using (Pen edgePen = new Pen(Color.DarkGreen, 1))
            {
                for (int i = 0; i < edges.GetLength(0); i++)
                {
                    PointF p1 = projection(transformedVertices[edges[i, 0]]);
                    PointF p2 = projection(transformedVertices[edges[i, 1]]);

                    g.DrawLine(edgePen, p1, p2);
                }
            }
        }

        private void DrawProjectionAxes(Graphics g, int width, int height, string projectionType)
        {
            int centerX = width / 2;
            int centerY = height / 2;
            int axisLength = 40;

            using (var axisFont = new Font("Arial", 8, FontStyle.Bold))
            {
                if (projectionType.Contains("XY"))
                {
                    // Ось X
                    g.DrawLine(Pens.Red, centerX, centerY, centerX + axisLength, centerY);
                    g.DrawString("X", axisFont, Brushes.Red, centerX + axisLength + 3, centerY - 6);

                    // Ось Y
                    g.DrawLine(Pens.Green, centerX, centerY, centerX, centerY - axisLength);
                    g.DrawString("Y", axisFont, Brushes.Green, centerX + 2, centerY - axisLength - 10);
                }
                else if (projectionType.Contains("XZ"))
                {
                    // Ось X
                    g.DrawLine(Pens.Red, centerX, centerY, centerX + axisLength, centerY);
                    g.DrawString("X", axisFont, Brushes.Red, centerX + axisLength + 3, centerY - 6);

                    // Ось Z
                    g.DrawLine(Pens.Blue, centerX, centerY, centerX, centerY - axisLength);
                    g.DrawString("Z", axisFont, Brushes.Blue, centerX + 2, centerY - axisLength - 10);
                }
                else if (projectionType.Contains("YZ"))
                {
                    // Ось Y
                    g.DrawLine(Pens.Green, centerX, centerY, centerX + axisLength, centerY);
                    g.DrawString("Y", axisFont, Brushes.Green, centerX + axisLength + 3, centerY - 6);

                    // Ось Z
                    g.DrawLine(Pens.Blue, centerX, centerY, centerX, centerY - axisLength);
                    g.DrawString("Z", axisFont, Brushes.Blue, centerX + 2, centerY - axisLength - 10);
                }
            }
        }

        private void DrawCoordinateSystem(Graphics g, int width, int height)
        {
            int centerX = width / 2;
            int centerY = height / 2;
            int axisLength = 80;

            using (var axisFont = new Font("Arial", 10, FontStyle.Bold))
            {
                g.DrawLine(Pens.Red, centerX, centerY, centerX + axisLength, centerY);
                g.DrawString("X", axisFont, Brushes.Red, centerX + axisLength + 5, centerY - 8);

                g.DrawLine(Pens.Green, centerX, centerY, centerX, centerY - axisLength);
                g.DrawString("Y", axisFont, Brushes.Green, centerX + 3, centerY - axisLength - 15);

                g.DrawLine(Pens.Blue, centerX, centerY, centerX - axisLength / 2, centerY + axisLength / 2);
                g.DrawString("Z", axisFont, Brushes.Blue, centerX - axisLength / 2 - 15, centerY + axisLength / 2);
            }
        }

        private Point3D TransformPoint(Point3D point)
        {
            float x = point.X * transformationMatrix[0, 0] + point.Y * transformationMatrix[0, 1] +
                     point.Z * transformationMatrix[0, 2] + transformationMatrix[0, 3];
            float y = point.X * transformationMatrix[1, 0] + point.Y * transformationMatrix[1, 1] +
                     point.Z * transformationMatrix[1, 2] + transformationMatrix[1, 3];
            float z = point.X * transformationMatrix[2, 0] + point.Y * transformationMatrix[2, 1] +
                     point.Z * transformationMatrix[2, 2] + transformationMatrix[2, 3];

            return new Point3D(x, y, z);
        }
    }

    public class Point3D
    {
        public float X { get; set; }
        public float Y { get; set; }
        public float Z { get; set; }

        public Point3D(float x, float y, float z)
        {
            X = x;
            Y = y;
            Z = z;
        }
    }
}