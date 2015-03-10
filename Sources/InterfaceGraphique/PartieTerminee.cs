﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace InterfaceGraphique
{
    public partial class PartieTerminee : Form
    {
        System.Media.SoundPlayer playerBtn = new System.Media.SoundPlayer(Properties.Resources.button_29);

        public PartieTerminee()
        {
            InitializeComponent();
            StartPosition = FormStartPosition.CenterScreen;
        }

        private void PartieTerminee_Shown(object sender, EventArgs e)
        {
            playerBtn.Play();
        }

        private void boutonMenuP_Click(object sender, EventArgs e)
        {
            this.Close();
            ((ModeJeu)this.Owner).Close();
        }

        private void boutonRecommencer_Click(object sender, EventArgs e)
        {
            this.Close();
            ((ModeJeu)this.Owner).RecommencerTout();
        }
    }
}
