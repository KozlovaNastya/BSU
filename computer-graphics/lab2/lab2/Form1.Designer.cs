namespace lab2
{
    partial class Form1
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.progressBar1 = new System.Windows.Forms.ProgressBar();
            this.label1 = new System.Windows.Forms.Label();
            this.dataGridView1 = new System.Windows.Forms.DataGridView();
            this.colFileName = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.colDimensions = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.colResolution = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.colColorDepth = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.colCompression = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.colFormat = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.backgroundWorker1 = new System.ComponentModel.BackgroundWorker();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).BeginInit();
            this.SuspendLayout();
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(12, 5);
            this.textBox1.Name = "textBox1";
            this.textBox1.ReadOnly = true;
            this.textBox1.Size = new System.Drawing.Size(485, 22);
            this.textBox1.TabIndex = 1;
            this.textBox1.Text = "Выберите папку с изображениями...";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(508, 4);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(107, 23);
            this.button1.TabIndex = 2;
            this.button1.Text = "Обзор...";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click_1);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(634, 5);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(154, 23);
            this.button2.TabIndex = 3;
            this.button2.Text = "Начать обработку";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // progressBar1
            // 
            this.progressBar1.Location = new System.Drawing.Point(12, 31);
            this.progressBar1.Name = "progressBar1";
            this.progressBar1.Size = new System.Drawing.Size(485, 23);
            this.progressBar1.Step = 1;
            this.progressBar1.TabIndex = 4;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(505, 38);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(105, 16);
            this.label1.TabIndex = 5;
            this.label1.Text = "Готов к работе";
            // 
            // dataGridView1
            // 
            this.dataGridView1.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.dataGridView1.BackgroundColor = System.Drawing.SystemColors.ControlLight;
            this.dataGridView1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView1.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.colFileName,
            this.colDimensions,
            this.colResolution,
            this.colColorDepth,
            this.colCompression,
            this.colFormat});
            this.dataGridView1.GridColor = System.Drawing.SystemColors.Control;
            this.dataGridView1.Location = new System.Drawing.Point(12, 60);
            this.dataGridView1.Name = "dataGridView1";
            this.dataGridView1.ReadOnly = true;
            this.dataGridView1.RowHeadersWidth = 51;
            this.dataGridView1.RowTemplate.Height = 24;
            this.dataGridView1.Size = new System.Drawing.Size(776, 378);
            this.dataGridView1.TabIndex = 6;
            // 
            // colFileName
            // 
            this.colFileName.HeaderText = "Имя файла";
            this.colFileName.MinimumWidth = 6;
            this.colFileName.Name = "colFileName";
            this.colFileName.ReadOnly = true;
            // 
            // colDimensions
            // 
            this.colDimensions.HeaderText = "Размеры";
            this.colDimensions.MinimumWidth = 6;
            this.colDimensions.Name = "colDimensions";
            this.colDimensions.ReadOnly = true;
            // 
            // colResolution
            // 
            this.colResolution.HeaderText = "Разрешение";
            this.colResolution.MinimumWidth = 6;
            this.colResolution.Name = "colResolution";
            this.colResolution.ReadOnly = true;
            // 
            // colColorDepth
            // 
            this.colColorDepth.HeaderText = "Глубина цвета";
            this.colColorDepth.MinimumWidth = 6;
            this.colColorDepth.Name = "colColorDepth";
            this.colColorDepth.ReadOnly = true;
            // 
            // colCompression
            // 
            this.colCompression.HeaderText = "Сжатие";
            this.colCompression.MinimumWidth = 6;
            this.colCompression.Name = "colCompression";
            this.colCompression.ReadOnly = true;
            // 
            // colFormat
            // 
            this.colFormat.HeaderText = "Формат";
            this.colFormat.MinimumWidth = 6;
            this.colFormat.Name = "colFormat";
            this.colFormat.ReadOnly = true;
            // 
            // backgroundWorker1
            // 
            this.backgroundWorker1.WorkerReportsProgress = true;
            this.backgroundWorker1.WorkerSupportsCancellation = true;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.dataGridView1);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.progressBar1);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.textBox1);
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.ProgressBar progressBar1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.DataGridView dataGridView1;
        private System.Windows.Forms.DataGridViewTextBoxColumn colFileName;
        private System.Windows.Forms.DataGridViewTextBoxColumn colDimensions;
        private System.Windows.Forms.DataGridViewTextBoxColumn colResolution;
        private System.Windows.Forms.DataGridViewTextBoxColumn colColorDepth;
        private System.Windows.Forms.DataGridViewTextBoxColumn colCompression;
        private System.Windows.Forms.DataGridViewTextBoxColumn colFormat;
        private System.ComponentModel.BackgroundWorker backgroundWorker1;
    }
}

