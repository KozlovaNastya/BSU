using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.IO;
using System.Linq;
using System.Windows.Forms;

namespace lab2
{
    public partial class Form1 : Form
    {
        private ImageProcessor processor;

        public Form1()
        {
            InitializeComponent();
            processor = new ImageProcessor();

            backgroundWorker1.DoWork += backgroundWorker1_DoWork;
            backgroundWorker1.ProgressChanged += backgroundWorker1_ProgressChanged;
            backgroundWorker1.RunWorkerCompleted += backgroundWorker1_RunWorkerCompleted;
            dataGridView1.ReadOnly = true;
        }

        private void button1_Click_1(object sender, EventArgs e)
        {
            using (FolderBrowserDialog folderDialog = new FolderBrowserDialog())
            {
                if (folderDialog.ShowDialog() == DialogResult.OK)
                {
                    textBox1.Text = folderDialog.SelectedPath;
                }
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrEmpty(textBox1.Text) || !Directory.Exists(textBox1.Text))
            {
                MessageBox.Show("Выберите корректную папку!");
                return;
            }

            dataGridView1.Rows.Clear();
            progressBar1.Value = 0;
            button2.Enabled = false;

            backgroundWorker1.RunWorkerAsync(textBox1.Text);
        }

        private void backgroundWorker1_DoWork(object sender, DoWorkEventArgs e)
        {
            string folderPath = e.Argument as string;
            var supportedExtensions = new[] { ".jpg", ".jpeg", ".png", ".bmp", ".gif", ".tif", ".tiff", ".pcx" };

            var imageFiles = Directory.GetFiles(folderPath, "*.*", SearchOption.AllDirectories)
                .Where(f => supportedExtensions.Contains(Path.GetExtension(f).ToLower()))
                .ToArray();

            int totalFiles = imageFiles.Length;

            for (int i = 0; i < totalFiles; i++)
            {
                if (backgroundWorker1.CancellationPending)
                {
                    e.Cancel = true;
                    return;
                }

                var imageInfo = processor.GetImageInfo(imageFiles[i]);

                backgroundWorker1.ReportProgress((i * 100) / totalFiles, imageInfo);
            }
        }

        private void backgroundWorker1_ProgressChanged(object sender, ProgressChangedEventArgs e)
        {
            progressBar1.Value = e.ProgressPercentage;

            if (e.UserState is ImageInfo imageInfo)
            {
                    dataGridView1.Rows.Add(
                    imageInfo.FileName,
                    imageInfo.Dimensions,
                    imageInfo.Resolution,
                    imageInfo.ColorDepth,
                    imageInfo.Compression,
                    imageInfo.Format
                );
                label1.Text = $"Обработано: {dataGridView1.Rows.Count} файлов";
            }
        }

        private void backgroundWorker1_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            button2.Enabled = true;
            progressBar1.Value = 100;
            label1.Text = $"Обработка завершена. Всего файлов: {dataGridView1.Rows.Count}";

            if (e.Error != null)
            {
                MessageBox.Show($"Ошибка: {e.Error.Message}");
            }
        }

    }
}