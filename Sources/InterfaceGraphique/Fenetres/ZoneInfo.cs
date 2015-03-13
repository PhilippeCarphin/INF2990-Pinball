﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace InterfaceGraphique
{
    public partial class ZoneInfo : Form
    {
        int time;
        int[] proprietes = new int[5];
        public ZoneInfo(string nomZone, string difficulte,bool win)
        {
            InitializeComponent();
            this.Icon = Properties.Resources.Pinball;
            this.WindowState = FormWindowState.Normal;
            this.FormBorderStyle = FormBorderStyle.None;
            StringBuilder zoneProps = new StringBuilder(Application.StartupPath + @"\zones\" + nomZone + ".xml");
            IntPtr config = FonctionsNatives.obtenirProprietes(zoneProps, zoneProps.Capacity);
            Marshal.Copy(config, proprietes, 0, 5);
            if (win)
            {
                labelWin.Text = "Vous avez gagné!";
            }
            else
            {
                labelWin.Text = "Début de la partie";
            }
            time = 5;
            timer1.Enabled = true;
           
            timer1.Interval = 25;
            timer1.Tick += new EventHandler(DecrementProgressBar);
            timer1.Tick += new System.EventHandler(this.timer1_Tick);
            label_Zone.Text = nomZone;
            label_Difficulte.Text = difficulte;
            label_Points.Text = proprietes[3].ToString();
            label_Bille.Text = proprietes[4].ToString();
            screenShot.SizeMode = PictureBoxSizeMode.StretchImage;
            screenShot.Image = Image.FromFile(Application.StartupPath + @"\zones\" + nomZone+ ".jpg");
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
         //   time--;
         //   labelTimeLeft.Text = time.ToString();
          //  if (time == 0)
         //       this.Close();
        }

        private void ZoneInfo_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar == ' ')
            {
                this.Close();
            }
        }

        private void DecrementProgressBar(object sender, EventArgs e)
        {
            tempRestant.Value--;
            if (tempRestant.Value % 40 == 0)
            {
                time--;
               
                labelTimeLeft.Text = time.ToString();
            }
            if (tempRestant.Value == tempRestant.Minimum)
            {
                timer1.Stop();
                this.Close();
            }
        }
    }
}