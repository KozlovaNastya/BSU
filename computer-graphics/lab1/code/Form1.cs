using System;
using System.Drawing;
using System.Reflection.Emit;
using System.Windows.Forms;

namespace lab1
{
    public partial class Form1 : Form
    {
        private bool updating = false;
        private Color currentColor = Color.Red;

        public Form1()
        {
            InitializeComponent();
            SubscribeToEvents();
            UpdateAllDisplays();
        }

        private void SubscribeToEvents()
        {
            // RGB события
            numericUpDown1.ValueChanged += RgbValueChanged;
            numericUpDown2.ValueChanged += RgbValueChanged;
            numericUpDown3.ValueChanged += RgbValueChanged;

            trackBar1.Scroll += RgbTrackBarChanged;
            trackBar2.Scroll += RgbTrackBarChanged;
            trackBar3.Scroll += RgbTrackBarChanged;

            // HSV события
            numericUpDown4.ValueChanged += HsvValueChanged;
            numericUpDown5.ValueChanged += HsvValueChanged;
            numericUpDown6.ValueChanged += HsvValueChanged;

            trackBar4.Scroll += HsvTrackBarChanged;
            trackBar5.Scroll += HsvTrackBarChanged;
            trackBar6.Scroll += HsvTrackBarChanged;

            // LAB события  
            numericUpDown7.ValueChanged += LabValueChanged;
            numericUpDown8.ValueChanged += LabValueChanged;
            numericUpDown9.ValueChanged += LabValueChanged;

            trackBar7.Scroll += LabTrackBarChanged;
            trackBar8.Scroll += LabTrackBarChanged;
            trackBar9.Scroll += LabTrackBarChanged;
        }

        private void UpdateAllDisplays()
        {
            UpdateFromRgb();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            ColorDialog colorDialog = new ColorDialog();
            colorDialog.Color = currentColor;

            if (colorDialog.ShowDialog() == DialogResult.OK)
            {
                currentColor = colorDialog.Color;
                UpdateAllDisplays();
                label1.Visible = false;
            }
        }

        private void RgbValueChanged(object sender, EventArgs e)
        {
            if (updating) return;
            currentColor = Color.FromArgb((int)numericUpDown1.Value,
                                         (int)numericUpDown2.Value,
                                         (int)numericUpDown3.Value);
            UpdateFromRgb();
        }
        private void RgbTrackBarChanged(object sender, EventArgs e)
        {
            if (updating) return;

            updating = true;
            numericUpDown1.Value = trackBar1.Value;
            numericUpDown2.Value = trackBar2.Value;
            numericUpDown3.Value = trackBar3.Value;
            updating = false;

            RgbValueChanged(sender, e);
        }

        private void HsvValueChanged(object sender, EventArgs e)
        {
            if (updating) return;
            UpdateFromHsv();
        }

        private void HsvTrackBarChanged(object sender, EventArgs e)
        {
            if (updating) return;

            updating = true;
            numericUpDown4.Value = trackBar4.Value;
            numericUpDown5.Value = trackBar5.Value;
            numericUpDown6.Value = trackBar6.Value;
            updating = false;

            HsvValueChanged(sender, e);
        }

        private void LabValueChanged(object sender, EventArgs e)
        {
            if (updating) return;
            UpdateFromLab();
        }

        private void LabTrackBarChanged(object sender, EventArgs e)
        {
            if (updating) return;

            updating = true;
            numericUpDown7.Value = trackBar7.Value;
            numericUpDown8.Value = trackBar8.Value - 128;
            numericUpDown9.Value = trackBar9.Value - 128;
            updating = false;

            LabValueChanged(sender, e);
        }
        private void SafeSetTrackBar(TrackBar trackBar, int value)
        {
            if (value < trackBar.Minimum)
                value = trackBar.Minimum;
            if (value > trackBar.Maximum)
                value = trackBar.Maximum;
            trackBar.Value = value;
        }

        private void SafeSetTrackBar(TrackBar trackBar, double value)
        {
            int intValue = (int)Math.Round(value);
            SafeSetTrackBar(trackBar, intValue);
        }

        private void SafeSetNumericUpDown(NumericUpDown numericUpDown, decimal value)
        {
            try
            {
                if (value < numericUpDown.Minimum)
                    value = numericUpDown.Minimum;
                if (value > numericUpDown.Maximum)
                    value = numericUpDown.Maximum;

                if (numericUpDown.Value != value)
                {
                    numericUpDown.Value = value;
                }
            }
            catch (Exception ex)
            {
                System.Diagnostics.Debug.WriteLine($"SafeSetNumericUpDown error: {ex.Message}");
            }
        }
        private void DebugLog(string message)
        {
            System.Diagnostics.Debug.WriteLine($"[DEBUG] {DateTime.Now:HH:mm:ss.fff}: {message}");
        }

        private void UpdateFromRgb()
        {
            if (updating) return;

            updating = true;
            try
            {
                ColorConverter.RgbToHsv(currentColor.R, currentColor.G, currentColor.B,
                    out double h, out double s, out double v);

                SafeSetNumericUpDown(numericUpDown4, (decimal)h);
                SafeSetNumericUpDown(numericUpDown5, (decimal)(s * 100));
                SafeSetNumericUpDown(numericUpDown6, (decimal)(v * 100));

                SafeSetTrackBar(trackBar4, h);
                SafeSetTrackBar(trackBar5, s * 100);
                SafeSetTrackBar(trackBar6, v * 100);

                ColorConverter.RgbToLab(currentColor.R, currentColor.G, currentColor.B,
                    out double l, out double a, out double b);

                SafeSetNumericUpDown(numericUpDown7, (decimal)l);
                SafeSetNumericUpDown(numericUpDown8, (decimal)a);
                SafeSetNumericUpDown(numericUpDown9, (decimal)b);

                SafeSetTrackBar(trackBar7, l);
                SafeSetTrackBar(trackBar8, a + 128);
                SafeSetTrackBar(trackBar9, b + 128);

                panel1.BackColor = currentColor;
            }
            finally
            {
                updating = false;
            }
        }

        private void UpdateFromHsv()
        {
            if (updating) return;

            updating = true;
            try
            {
                double h = (double)numericUpDown4.Value;
                double s = (double)numericUpDown5.Value / 100.0;
                double v = (double)numericUpDown6.Value / 100.0;

                ColorConverter.HsvToRgb(h, s, v, out int r, out int g, out int b);
                currentColor = Color.FromArgb(r, g, b);


                SafeSetNumericUpDown(numericUpDown1, r);
                SafeSetNumericUpDown(numericUpDown2, g);
                SafeSetNumericUpDown(numericUpDown3, b);

                SafeSetTrackBar(trackBar1, r);
                SafeSetTrackBar(trackBar2, g);
                SafeSetTrackBar(trackBar3, b);

                ColorConverter.RgbToLab(r, g, b, out double l, out double a, out double b_val);

                SafeSetNumericUpDown(numericUpDown7, (decimal)l);
                SafeSetNumericUpDown(numericUpDown8, (decimal)a);
                SafeSetNumericUpDown(numericUpDown9, (decimal)b_val);

                SafeSetTrackBar(trackBar7, l);
                SafeSetTrackBar(trackBar8, a + 128);
                SafeSetTrackBar(trackBar9, b_val + 128);

                panel1.BackColor = currentColor;
            }
            finally
            {
                updating = false;
            }
        }

        private void UpdateFromLab()
        {
            if (updating) return;

            updating = true;
            try
            {
                double l = (double)numericUpDown7.Value;
                double a = (double)numericUpDown8.Value;
                double b_val = (double)numericUpDown9.Value;

                ColorConverter.LabToRgb(l, a, b_val, out int r, out int g, out int b);
                currentColor = Color.FromArgb(r, g, b);

                SafeSetNumericUpDown(numericUpDown1, r);
                SafeSetNumericUpDown(numericUpDown2, g);
                SafeSetNumericUpDown(numericUpDown3, b);

                SafeSetTrackBar(trackBar1, r);
                SafeSetTrackBar(trackBar2, g);
                SafeSetTrackBar(trackBar3, b);

                ColorConverter.RgbToHsv(r, g, b, out double h, out double s, out double v);

                SafeSetNumericUpDown(numericUpDown4, (decimal)h);
                SafeSetNumericUpDown(numericUpDown5, (decimal)(s * 100));
                SafeSetNumericUpDown(numericUpDown6, (decimal)(v * 100));

                SafeSetTrackBar(trackBar4, h);
                SafeSetTrackBar(trackBar5, s * 100);
                SafeSetTrackBar(trackBar6, v * 100);

                panel1.BackColor = currentColor;
            }
            finally
            {
                updating = false;
            }
        }
    }
}