using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace youtube
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            this.DoubleBuffered = true;

            this.Paint += new PaintEventHandler(Form1_Paint);
        }

        private void Form1_Paint(object sender, System.Windows.Forms.PaintEventArgs e)
        {
            e.Graphics.DrawRectangle(Pens.Black, new Rectangle(0,0, 50, 75));
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            this.Refresh();
        }

    }
}
