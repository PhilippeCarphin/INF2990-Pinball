﻿using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Windows.Forms;

namespace InterfaceGraphique
{
    public partial class ModeJeu : Form
    {
        public PartieTerminee gameOver;
        private Timer timer;
        private Timer timerBille2;
        private double currentZoom = -1; ///< Zoom courant
        private Touches touches; ///< Les touches pour le jeu
        private ZoneInfo zInfo;
        private int currentZone = 0;
        private int nbZones;
        private int nombreBillesInit = 0;
        List<string> myMaps;
        StringBuilder map;
        StringBuilder nextMap;
        bool peutAnimer;
        bool boolTemp = true;
        bool startGame = false;
        private bool activateAmbiantLight = false; ///< Etat de la lumiere ambiante
        private bool activateDirectLight = false; ///< Etat de la lumiere directe
        private bool activateSpotLight = false; ///< Etat de la lumiere spot
        private EtatJeuAbstrait etat; ///< Machine à états

        public int pointsPartie = 0;
        public int pointsTotale = 0;
        public int billeDisponible = 0;
        private int nombreDeBillesGagnes = 0;
        private int pointsGagnerBille = 0;
        private int pointsGagnerPartie = 0;
        private int billesDisponibles = 0;
        public int billesEnJeu = 0;
        private int nombreDeBillesUtilise = 0;
        
        // Modificateurs
        public void setVisibilityMenuStrip(bool vis) { menuStrip.Visible = vis; }
        public void setCurrentZoom(double val)       { currentZoom = val; }
        public void setPeutAnimer(bool activation)   { peutAnimer = activation; }
        
        // Accesseurs
        public double getCurrentZoom()    { return currentZoom; }
        public Touches getTouches()       { return touches; }
        public bool getAmbiantLight()     { return activateAmbiantLight;}
        public bool getDirectLight()      { return activateDirectLight; }
        public bool getSpotLight()        { return activateSpotLight; }
        
        // Toggle des lumières
        public void toggleAmbiantLight() { activateAmbiantLight = !activateAmbiantLight; }
        public void toggleDirectLight()  { activateDirectLight  = !activateDirectLight; }
        public void toggleSpotLight()    { activateSpotLight    = !activateSpotLight; }

        // Méthodes de changement d'état
        public void pauseGame() { etat = new EtatJeuPause(this); }
        public void resumeGame() { etat = new EtatJeuJouer(this); }
        
        public partial class EtatJeuAbstrait
        {
            public EtatJeuAbstrait() {}
            public EtatJeuAbstrait(ModeJeu parent)
            {
                //Console.WriteLine("Etat :" + '\t' + "Abstrait");
                this.parent_ = parent;
            }
        };

        public ModeJeu(List<string> maps, int playerType)
        {
            {/*
                this.WindowState = FormWindowState.Normal;
                this.FormBorderStyle = FormBorderStyle.None;
                this.WindowState = FormWindowState.Maximized;*/
            }
            timer = new Timer();
           // timerBille2 = new Timer();
           // timerBille2.Interval = 1000;
           // timerBille2.Tick += new System.EventHandler(this.timerBille2_Tick);
            timer.Enabled = true;

            timer.Interval = 3000;
            timer.Tick += new System.EventHandler(this.timer_Tick);
            EtablirTouches(playerType);
            this.KeyDown += new KeyEventHandler(PartieRapide_KeyDown);
            this.KeyUp += new KeyEventHandler(PartieRapide_KeyUp);
            InitializeComponent();
            peutAnimer = true;
            Program.peutAfficher = true;              
            InitialiserAnimation();
            FonctionsNatives.resetZoom();
            currentZoom = -1;
            myMaps = new List<string>(maps);
            nbZones = maps.Count;
            if( nbZones == 1)
                this.Text = "Partie Rapide";
            if (nbZones > 1)
                this.Text = "Campagne";
            map = new StringBuilder(myMaps[0]);
            //Console.WriteLine(nbZones);
            FonctionsNatives.ouvrirXML(map, map.Capacity);
            //Console.WriteLine(pointsGagnerPartie);
            //Console.WriteLine(pointsPartie);
            resetConfig();
            nombreBillesInit = FonctionsNatives.obtenirNombreDeBilles();
            FonctionsNatives.construireListesPalettes();
            currentZone++;
            Program.tempBool = true;
            panel_GL.Focus();
            
            etat = new EtatJeuDebutDePartie(this);
            // Il faut changer le mode car le traitement de début est fini
            etat = new EtatJeuJouer(this);
            timer.Start();
          
        }


        protected void resetConfig()
        {
            billeDisponible = 0;
            billesEnJeu = 0;
            nombreDeBillesGagnes = 0;
            nombreDeBillesUtilise = 0;
            pointsPartie = 0;
            pointsTotale = 0;
            pointsGagnerPartie = FonctionsNatives.obtenirPointsGagnerPartie();
            pointsGagnerBille = FonctionsNatives.obtenirPointsGagnerBille();
            nombreBillesInit = FonctionsNatives.obtenirNombreDeBilles();
            this.PointPartie.Text = pointsPartie.ToString();
            this.nbBilles.Text = "0";
        }
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn static public void InitialiserAnimation()
        /// @brief Initialise openGL et l'animation.
        /// 
        /// @return Aucune (constructeur).
        ///
        ////////////////////////////////////////////////////////////////////////
        
        public void InitialiserAnimation()
        {
            this.DoubleBuffered = false;
            this.StartPosition = FormStartPosition.WindowsDefaultBounds;
            FonctionsNatives.initialiserOpenGL(panel_GL.Handle);
            FonctionsNatives.dessinerOpenGL();

        }

        // To DO: remove this
        private void timer_Tick(object sender, EventArgs e)
        {
          StringBuilder bille = new StringBuilder("bille");
          FonctionsNatives.creerObjet(bille, bille.Capacity);
          //Console.WriteLine("timer");
         // timerBille2.Start();
          timer.Stop();
          startGame = true;
        }
        // And this
        private void timerBille2_Tick(object sender, EventArgs e)
        {
            StringBuilder bille = new StringBuilder("bille");
            FonctionsNatives.creerObjet(bille, bille.Capacity);
            //Console.WriteLine("BILLE 2");
            timerBille2.Stop();
        }

        public void MettreAJour(double tempsInterAffichage)
        {
            try
            {
                this.Invoke((MethodInvoker)delegate
                {
                    if (peutAnimer)
                    {
                        FonctionsNatives.animer(tempsInterAffichage);
                        //int bfPts = pointsPartie;
                        pointsPartie = FonctionsNatives.obtenirNombreDePointsDePartie();
                        //if (bfPts != pointsPartie)
                        //    Console.WriteLine(pointsPartie);
                    }
                   FonctionsNatives.dessinerOpenGL();

                   billesEnJeu = FonctionsNatives.obtenirNombreBillesCourante();
                   if (startGame && billesEnJeu == 0 && (nombreBillesInit + nombreDeBillesGagnes - nombreDeBillesUtilise > 0))
                //   if (billesEnJeu == 0 && nombreBillesInit > 0)
                  
                    {
                        // wait a certain time
                       StringBuilder bille = new StringBuilder("bille");
                       FonctionsNatives.creerObjet(bille, bille.Capacity);
                       nombreDeBillesUtilise++;
                       Console.WriteLine(nombreBillesInit);
                       Console.WriteLine(nombreDeBillesUtilise);
                   }
                   if (nombreDeBillesUtilise >= (nombreBillesInit + nombreDeBillesGagnes) && boolTemp)
                   {
                       FinCampagne(false);
                   }
                   if (pointsPartie >= nombreDeBillesGagnes * pointsGagnerBille + pointsGagnerBille)
                   {
                       nombreDeBillesGagnes++;
                       billesDisponibles++;
                   }

                   this.PointPartie.Text = pointsPartie.ToString();
                  // this.nbBilles.Text = (nombreDeBillesGagnes - nombreDeBillesUtilise).ToString();
                  // this.nbBilles.Text = (nombreBillesInit + nombreDeBillesGagnes).ToString();
                   this.nbBilles.Text = billesEnJeu.ToString();
                    if (pointsPartie >= pointsGagnerPartie && boolTemp)
                    {
                        if (currentZone >= nbZones)
                        {
                            FinCampagne(true);
                        
                        }
                        else
                        {
                            ProchainePartie();  
                        }
                    }
                   

                    if (currentZoom <= 0)
                    {
                        FonctionsNatives.resetZoom();
                        currentZoom = FonctionsNatives.obtenirZoomCourant();

                    }
                });
            }
            catch (Exception)
            {
            }
            
        }
        
        private void PartieRapide_FormClosing(object sender, FormClosingEventArgs e)
        {
            lock (Program.unLock)
            {
                FonctionsNatives.libererOpenGL();
                Program.peutAfficher = false;
                Program.tempBool = false;
            }
        }

        public void RecommencerPartie()
        {
            resetConfig();

            FonctionsNatives.ouvrirXML(map, map.Capacity);

            FonctionsNatives.construireListesPalettes();
            FonctionsNatives.mettreAJourListeBillesEtNoeuds();


            timer.Start();
        }

        private void ProchainePartie()
        {
            boolTemp = false;
            peutAnimer = false;
            map = new StringBuilder(myMaps[currentZone]);
            nextMap = new StringBuilder(map.ToString());
            nextMap.Remove(nextMap.Length - 4, 4);
            //Console.WriteLine(Path.GetFileName(nextMap.ToString()));

            System.Threading.Thread.Sleep(500);
            zInfo = new ZoneInfo(Path.GetFileName(nextMap.ToString()), FonctionsNatives.obtenirDifficulte(map, map.Capacity).ToString(), true);
            this.Hide();
            zInfo.ShowDialog();
            this.Show();

            FonctionsNatives.ouvrirXML(map, map.Capacity);
            FonctionsNatives.construireListesPalettes();
            FonctionsNatives.resetNombreDePointsDePartie();
            FonctionsNatives.resetNombreBillesCourantes();
            currentZone++;
            peutAnimer = true;
            boolTemp = true;
            /// La création de l'état s'occupe d'appeler resetConfig
            etat = new EtatJeuDebutDePartie(this);
            // Il faut changer le mode car le traitement de début est fini
            etat = new EtatJeuJouer(this);
            timer.Enabled = true;
            timer.Interval = 3000;
            timer.Stop();
            timer.Start();

        }

        private void FinCampagne(bool active)
        {
                            peutAnimer = false;
                            boolTemp = false;
                            gameOver = new PartieTerminee(active);
            
                            gameOver.ShowDialog(this);
        }
        private void PartieRapide_Load(object sender, EventArgs e)
        {

        }

        private void EtablirTouches(int playerType)
        {
            if (playerType == 1)
            {
                touches = new Touches(FonctionsNatives.obtenirTouchePGJ1(),
                                 FonctionsNatives.obtenirTouchePGJ1(),
                                 FonctionsNatives.obtenirTouchePDJ1(),
                                 FonctionsNatives.obtenirTouchePDJ1(),
                                 FonctionsNatives.obtenirToucheRessort());
            }
            else if (playerType == 2)
            {
                touches = new Touches(FonctionsNatives.obtenirTouchePGJ1(),
                                FonctionsNatives.obtenirTouchePGJ2(),
                                FonctionsNatives.obtenirTouchePDJ1(),
                                FonctionsNatives.obtenirTouchePDJ2(),
                                FonctionsNatives.obtenirToucheRessort());
            }
            else if (playerType == 3)
            {
                // Le 1337 est la pour rendre l'acces aux touches de joueur 2 invalide
                touches = new Touches(FonctionsNatives.obtenirTouchePGJ1(),
                                1337,
                                FonctionsNatives.obtenirTouchePDJ1(),
                                1337,
                                FonctionsNatives.obtenirToucheRessort());
            }



        }

        private void PartieRapide_KeyDown(object sender, KeyEventArgs e)
        {
            etat.traiterKeyDown(sender, e);
        }


        private void PartieRapide_KeyUp(object sender, KeyEventArgs e)
        {
            etat.traiterKeyUp(sender, e);
        }

        

        private void PartieRapide_redimensionner(object sender, EventArgs e)
        {
            FonctionsNatives.redimensionnerFenetre(panel_GL.Width == 0 ? 1 : panel_GL.Width, panel_GL.Height == 0 ? 1 : panel_GL.Height);
        }

        private void PartieRapide_KeyPress(object sender, KeyPressEventArgs e)
        {
            etat.traiterKeyPress(sender, e);
        }

        private void panel_GL_MouseWheel(object sender, MouseEventArgs e)
        {
            etat.traiterRoulette(sender, e);
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void RecommencerTout()
        /// @brief Reinitialise la campagne ou la partie rapide lorsqu'on termine
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public void RecommencerTout()
        {
           if (gameOver.Enabled)
            {
                gameOver.Hide();
            }
           
            pointsPartie = 0;
            currentZone = 0;
            map = new StringBuilder(myMaps[0]);
            nextMap = new StringBuilder(map.ToString());
            nextMap.Remove(nextMap.Length - 4, 4);
            //Console.WriteLine(map);
            this.Hide();
            zInfo = new ZoneInfo(Path.GetFileName(nextMap.ToString()), FonctionsNatives.obtenirDifficulte(map, map.Capacity).ToString(),false);
            zInfo.ShowDialog();
            this.Show();
            FonctionsNatives.ouvrirXML(map, map.Capacity);
            FonctionsNatives.resetNombreDePointsDePartie();
            FonctionsNatives.resetNombreBillesCourantes();
            currentZone = 1;
            FonctionsNatives.construireListesPalettes();
            startGame = false;
            peutAnimer = true;
            boolTemp = true;
            /// La création de l'état s'occupe d'appeler resetConfig
            etat = new EtatJeuDebutDePartie(this);
            // Il faut changer le mode car le traitement de début est fini
            etat = new EtatJeuJouer(this);
            timer.Start();
           
           // gameOver.Close();
            gameOver.Dispose();
            timer.Stop();
            timer.Start();

           
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Quitter()
        /// @brief Quitte le mode Jeu
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public void Quitter()
        {
            timer.Stop();
            this.Close();
        }
        
        private void mPrincipal_menu_Click(object sender, EventArgs e)
        {
            timer.Stop();
            this.Close();
        }

        private void panel_GL_MouseClick(object sender, MouseEventArgs e)
        {
          //  panel_GL.Focus();
        }

    }

    public partial class FonctionsNatives
    {
       
    }
}