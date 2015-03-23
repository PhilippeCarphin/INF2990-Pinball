﻿//////////////////////////////////////////////////////////////////////////////
/// @file ModeJeu.cs
/// @author Ballers
/// @date 2015-03-10
/// @version 1.0 
///
/// @ingroup Fenetres
//////////////////////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.IO;
using System.Runtime.InteropServices;
using System.Text;
using System.Windows.Forms;

namespace InterfaceGraphique
{
    ///////////////////////////////////////////////////////////////////////////
    /// @class ModeJeu
    /// @brief Classe d'interface du mode jeu.
    ///
    /// @author Ballers
    /// @date 2015-03-10
    /// 
    /// @ingroup Fenetres
    ///////////////////////////////////////////////////////////////////////////
    public partial class ModeJeu : Form
    {
        private bool firstStart = true;
        public PartieTerminee gameOver; ///< Form de fin de partie
        private double currentZoom = -1; ///< Zoom courant
        private Touches touches; ///< Les touches pour le jeu
        private ZoneInfo zInfo;  ///< Form dinfo de prochaine zone
        private int currentZone = 0; ///< la zone a laquelle on est rendue
        private int nbZones;    ///< nombre de Zones dans la campagne/Partie rapide
        private int nombreBillesInit = 0;   /// Nombre de Billes initiales ( 3/5/7)
        private int nombreBillesMax;    ///< nombre maximal de billes en jeu
        List<string> myMaps;    ///< liste des zones a jouer
        StringBuilder map;      ///< la zone en jeu
        StringBuilder nextMap;  ///< prochaine zone
        bool peutAnimer;
        bool boolTemp = true;   ///< bool pour ne pas spam FinDePartie
        private bool activateAmbiantLight = false; ///< Etat de la lumiere ambiante
        private bool activateDirectLight = false; ///< Etat de la lumiere directe
        private bool activateSpotLight = false; ///< Etat de la lumiere spot
        private EtatJeuAbstrait etat; ///< Machine à états
        int[] proprietes = new int[5];  ///< les proprietes de la zone
        public int pointsPartie = 0;    ///< nombre de points
        public int pointsTotale = 0;    ///< no idea wtf is this

        private int nombreDeBillesGagnes = 0; ///< nombre de billes extras
        private int pointsGagnerBille = 0;  ///< Nombre de Points pour gagner une nouvelle bille
        private int pointsGagnerPartie = 0; ///< Nombre de Points pour gagner une zone
        private int billesDisponibles = 0;  ///< Billes dont le(s) joueur(s) disposent
        public int billesEnJeu = 0;         ///< Billes qui sont sur la zone
        private int nombreDeBillesUtilise = 0; ///< Nombre de Billes deja utilises
        private int billesPerdus = 0;       ///< Nomrede billes tombees dans le trou

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

        ///////////////////////////////////////////////////////////////////////////
        /// @class EtatJeuAbstrait
        /// @brief Classe interne (ModeJeu) d'etat abstrait
        ///
        /// @author Ballers
        /// @date 2015-3-10
        ///
        /// @ingroup Fenetres
        ///////////////////////////////////////////////////////////////////////////
        public partial class EtatJeuAbstrait
        {
            public EtatJeuAbstrait() {}
            public EtatJeuAbstrait(ModeJeu parent)
            {
                //Console.WriteLine("Etat :" + '\t' + "Abstrait");
                this.parent_ = parent;
            }
        };

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public Configuration()
        /// @brief Constructeur par parametre de la fenetre de mode jeu.
        /// @param[in] maps : Liste de zones a jouer.
        /// @param[in] playerType : Type de joueur (Solo, 2P, AI)
        /// @return Aucune (constructeur).
        ///
        ////////////////////////////////////////////////////////////////////////
        public ModeJeu(List<string> maps, int playerType)
        {
            this.MouseWheel += new MouseEventHandler(panel_GL_MouseWheel);

            if (FonctionsNatives.obtenirModeDoubleBille() != 0)
            {
                nombreBillesMax = 2;
            }
            else
            {
                nombreBillesMax = 1;
            }

            // Permet d'etablir le type de joueur
            EtablirTouchesEtAI(playerType);

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
            Console.WriteLine(nbZones);
            map = new StringBuilder(myMaps[0]);
            FonctionsNatives.ouvrirXML(map, map.Capacity);
            resetConfig();
            nombreBillesInit = FonctionsNatives.obtenirNombreDeBilles();
            FonctionsNatives.construireListesPalettes();
            FonctionsNatives.translater(-10, 0);

            currentZone++;
            Program.tempBool = true;
            panel_GL.Focus();
            string nomMap = Path.GetFileNameWithoutExtension(map.ToString());
            label_Nom.Text = "Nom: " + nomMap;
            if (nbZones == 1)
                this.Text = "Partie Rapide: " + nomMap;
            if (nbZones > 1)
                this.Text = "Campagne: " + nomMap;
            etat = new EtatJeuDebutDePartie(this);
            // Il faut changer le mode car le traitement de début est fini
            etat = new EtatJeuJouer(this);
            FonctionsNatives.animerJeu(true);
           // CreerBille();       
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn protected void resetConfig()
        /// @brief Reset des points et aux configurations de partie.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        protected void resetConfig()
        {
            billesEnJeu = 0;
            FonctionsNatives.resetNombreBillesCourantes();
            nombreDeBillesGagnes = 0;
            nombreDeBillesUtilise = 0;
            pointsPartie = 0;
            pointsTotale = 0;
            pointsGagnerPartie = FonctionsNatives.obtenirPointsGagnerPartie();
            pointsGagnerBille = FonctionsNatives.obtenirPointsGagnerBille();
            nombreBillesInit = FonctionsNatives.obtenirNombreDeBilles();
            billesDisponibles = nombreBillesInit;
            label_nbGagnes.Text = nombreDeBillesGagnes.ToString();
            setProprietes();
            if(!firstStart)
                Program.myCustomConsole.Update();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void setProprietes()
        /// @brief Affichage des proprietes dans les labels correspondants.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void setProprietes()
        {
            IntPtr config = FonctionsNatives.obtenirProprietes(map,map.Capacity);
            Marshal.Copy(config, proprietes, 0, 5);
            label_nbPointsButC.Text = proprietes[0].ToString();
            label_nbPointsButT.Text = proprietes[1].ToString();
            label_nbPointsCible.Text = proprietes[2].ToString();
            label_nbWin.Text = proprietes[3].ToString();
            label_nbPointsBille.Text = proprietes[4].ToString();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn static public void InitialiserAnimation()
        /// @brief Initialise openGL et l'animation.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public void InitialiserAnimation()
        {
            this.DoubleBuffered = false;
            this.StartPosition = FormStartPosition.WindowsDefaultBounds;
            FonctionsNatives.initialiserOpenGL(panel_GL.Handle);
            FonctionsNatives.dessinerOpenGL();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void MettreAJour(double tempsInterAffichage)
        /// @brief Mise a jour du panneau OpenGL.
        /// @param[in] tempsInterAffichage : Objet duquel provient un evenement.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public void MettreAJour(double tempsInterAffichage)
        {
            try
            {
                this.Invoke((MethodInvoker)delegate
                {
                    if (peutAnimer)
                    {
                        FonctionsNatives.animer(tempsInterAffichage);
                        if (Program.compteurFrames == 0)
                            pointsPartie = FonctionsNatives.obtenirNombreDePointsDePartie();
                    }
                    if (Program.compteurFrames == 0)
                    {
                        FonctionsNatives.dessinerOpenGL();
                    }
                    billesEnJeu = FonctionsNatives.obtenirNombreBillesCourante();
                    billesPerdus = FonctionsNatives.obtenirNombreBillesPerdus();
                    billesDisponibles = nombreBillesInit + nombreDeBillesGagnes - billesPerdus - billesEnJeu;
                    if (billesEnJeu < nombreBillesMax && (billesDisponibles > 0))
                    {
                        // Wait a certain time
                        CreerBille();
                    }
                    if (billesDisponibles == 0 && boolTemp && billesEnJeu == 0)
                    {
                        FinCampagne(false);
                    }
                    if (pointsPartie >= nombreDeBillesGagnes * pointsGagnerBille + pointsGagnerBille)
                    {
                        nombreDeBillesGagnes++;
                        label_nbGagnes.Text = nombreDeBillesGagnes.ToString();

                    }

                    label_nbPoints.Text = pointsPartie.ToString();
                    if (billesDisponibles >= 0)
                    {
                        label_nbBilles.Text = billesDisponibles.ToString();
                    }
                    if (pointsPartie >= pointsGagnerPartie && boolTemp && (nbZones > 1))
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

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void PartieRapide_FormClosing(object sender, EventArgs e)
        /// @brief Evenement lorsqu'on ferme la form PartieRapide.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void PartieRapide_FormClosing(object sender, FormClosingEventArgs e)
        {
            lock (Program.unLock)
            {
                FonctionsNatives.libererOpenGL();
                Program.peutAfficher = false;
                Program.tempBool = false;
            }
            //Console.WriteLine("closing");
            Program.myCustomConsole.Hide();
          //  Console.WriteLine("closing");
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void RecommencerPartie()
        /// @brief Recommence la partie.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public void RecommencerPartie()
        {
            resetConfig();
            FonctionsNatives.purgeAll();
            FonctionsNatives.ouvrirXML(map, map.Capacity);
            FonctionsNatives.resetNombreBillesCourantes();
            FonctionsNatives.construireListesPalettes();
            FonctionsNatives.mettreAJourListeBillesEtNoeuds();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void AfficherInformations()
        /// @brief Afficher les informations de la partie.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public void AfficherInformations()
        {
            InfoPanel.Visible = !InfoPanel.Visible;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void ProchainePartie()
        /// @brief Chargement de la prochaine partie.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void ProchainePartie()
        {
            boolTemp = false;
            peutAnimer = false;
            map = new StringBuilder(myMaps[currentZone]);
            nextMap = new StringBuilder(map.ToString());
            nextMap.Remove(nextMap.Length - 4, 4);
            System.Threading.Thread.Sleep(500);
            zInfo = new ZoneInfo(Path.GetFileName(nextMap.ToString()), FonctionsNatives.obtenirDifficulte(map, map.Capacity).ToString(), true);
            Program.myCustomConsole.Hide();
            this.Hide();
            zInfo.ShowDialog();
            this.Show();
            Program.myCustomConsole.Show();
            if (Program.mMenu.modeJeuMain != null)
            {
                Program.myCustomConsole.Show();
                Program.mMenu.modeJeuMain.Focus();
            }
            FonctionsNatives.ouvrirXML(map, map.Capacity);
            FonctionsNatives.construireListesPalettes();
            FonctionsNatives.resetNombreDePointsDePartie();
            FonctionsNatives.resetNombreBillesCourantes();
            FonctionsNatives.mettreAJourListeBillesEtNoeuds();
            currentZone++;
            peutAnimer = true;
            boolTemp = true;
            /// La création de l'état s'occupe d'appeler resetConfig
            etat = new EtatJeuDebutDePartie(this);
            // Il faut changer le mode car le traitement de début est fini
            etat = new EtatJeuJouer(this);
            label_Nom.Text = "Nom: " + Path.GetFileNameWithoutExtension(map.ToString());
            if (nbZones == 1)
                this.Text = "Partie Rapide: " + Path.GetFileNameWithoutExtension(map.ToString());
            if (nbZones > 1)
                this.Text = "Campagne: " + Path.GetFileNameWithoutExtension(map.ToString());
        
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void CreerBille()
        /// @brief Creation d'une nouvelle bille.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void CreerBille()
        {
            StringBuilder bille = new StringBuilder("bille");
            FonctionsNatives.creerObjet(bille, bille.Capacity);
            nombreDeBillesUtilise++;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void FinCampagne(bool active)
        /// @brief Desactivation d'options en fin de campagne.
        /// @param[in] active : valeur d'activation.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void FinCampagne(bool active)
        {
            Program.myCustomConsole.Hide();
            peutAnimer = false;
            boolTemp = false;
            gameOver = new PartieTerminee(active);
            Program.myCustomConsole.Hide();
            gameOver.ShowDialog(this);
            if (Program.mMenu.modeJeuMain != null)
            {
                Program.myCustomConsole.Show();
                Program.mMenu.modeJeuMain.Focus();
            }
        }

        private void PartieRapide_Load(object sender, EventArgs e)
        {

        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void EtablirTouchesEtAI(int playerType)
        /// @brief Etablit les touches de jeu et active ou non l'AI selon le mode choisi.
        /// @param[in] playerType : Type de joueur (Solo, 2P, AI).
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void EtablirTouchesEtAI(int playerType)
        {
            if (playerType == 1)
            {
                touches = new Touches(FonctionsNatives.obtenirTouchePGJ1(),
                                 FonctionsNatives.obtenirTouchePGJ1(),
                                 FonctionsNatives.obtenirTouchePDJ1(),
                                 FonctionsNatives.obtenirTouchePDJ1(),
                                 FonctionsNatives.obtenirToucheRessort());
                FonctionsNatives.activerAI(false);
            }
            else if (playerType == 2)
            {
                touches = new Touches(FonctionsNatives.obtenirTouchePGJ1(),
                                FonctionsNatives.obtenirTouchePGJ2(),
                                FonctionsNatives.obtenirTouchePDJ1(),
                                FonctionsNatives.obtenirTouchePDJ2(),
                                FonctionsNatives.obtenirToucheRessort());

                FonctionsNatives.activerAI(false);
            }
            else if (playerType == 3)
            {
                // Le 1337 est la pour rendre l'acces aux touches de joueur 2 invalide
                touches = new Touches(FonctionsNatives.obtenirTouchePGJ1(),
                                1337,
                                FonctionsNatives.obtenirTouchePDJ1(),
                                1337,
                                FonctionsNatives.obtenirToucheRessort());

                FonctionsNatives.activerAI(true);
            }

        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void PartieRapide_KeyDown(object sender, EventArgs e)
        /// @brief Evenement lorsqu'on appuie sur une touche en partie rapide.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void PartieRapide_KeyDown(object sender, KeyEventArgs e)
        {
            etat.traiterKeyDown(sender, e);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void PartieRapide_KeyUp(object sender, EventArgs e)
        /// @brief Evenement lorsqu'on relache une touche en partie rapide.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void PartieRapide_KeyUp(object sender, KeyEventArgs e)
        {
            etat.traiterKeyUp(sender, e);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void PartieRapide_redimensionner(object sender, EventArgs e)
        /// @brief Evenement lorsqu'on redimensionne la fenetre de partie rapide.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void PartieRapide_redimensionner(object sender, EventArgs e)
        {
            FonctionsNatives.redimensionnerFenetre(panel_GL.Width == 0 ? 1 : panel_GL.Width, panel_GL.Height == 0 ? 1 : panel_GL.Height);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void PartieRapide_KeyDown(object sender, EventArgs e)
        /// @brief Evenement lorsqu'on appuie et relache une touche en partie rapide.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void PartieRapide_KeyPress(object sender, KeyPressEventArgs e)
        {
            etat.traiterKeyPress(sender, e);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void panel_GL_MouseWheel(object sender, EventArgs e)
        /// @brief Evenement lorsqu'on utilise la roulette de la souris sur le panel GL.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void panel_GL_MouseWheel(object sender, MouseEventArgs e)
        {
            etat.traiterRoulette(sender, e);
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void RecommencerTout()
        /// @brief Reinitialise la campagne ou la partie rapide lorsqu'on termine.
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
            Program.myCustomConsole.Hide();
            this.Hide();
            zInfo = new ZoneInfo(Path.GetFileName(nextMap.ToString()), FonctionsNatives.obtenirDifficulte(map, map.Capacity).ToString(),false);
            zInfo.ShowDialog();
            this.Show();
            if (Program.mMenu.modeJeuMain != null)
            {
                Program.myCustomConsole.Show();
                Program.mMenu.modeJeuMain.Focus();
            }
            FonctionsNatives.ouvrirXML(map, map.Capacity);
            FonctionsNatives.resetNombreDePointsDePartie();
            FonctionsNatives.resetNombreBillesCourantes();
            FonctionsNatives.construireListesPalettes();
            currentZone = 1;
            peutAnimer = true;
            boolTemp = true;
            /// La création de l'état s'occupe d'appeler resetConfig
            etat = new EtatJeuDebutDePartie(this);
            // Il faut changer le mode car le traitement de début est fini
            etat = new EtatJeuJouer(this);
           
           // gameOver.Close();
            gameOver.Dispose();
            label_Nom.Text = "Nom: " + Path.GetFileNameWithoutExtension(map.ToString());


           
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Quitter()
        /// @brief Quitte le mode Jeu.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public void Quitter()
        {
           // resetConfig();
            Program.myCustomConsole.Hide();
            this.Close();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void mPrincipal_menu_Click(object sender, EventArgs e)
        /// @brief Retour au menu principal lorsqu'on clique sur l'option dans le menu.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void mPrincipal_menu_Click(object sender, EventArgs e)
        {
            Program.myCustomConsole.Hide();
            this.Close();
        }

        private void panel_GL_MouseClick(object sender, MouseEventArgs e)
        {
          //  panel_GL.Focus();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void ModeJeu_Shown(object sender, EventArgs e)
        /// @brief Affichage/Ajustement de la console custom si utilisee
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void ModeJeu_Shown(object sender, EventArgs e)
        {
            var scrren = Screen.PrimaryScreen.Bounds.Height;
            this.Height = (scrren*3)/4;
           
            Program.myCustomConsole.reStart();
            Program.myCustomConsole.Update();
            if (Program.mMenu.modeJeuMain != null)
                Program.mMenu.modeJeuMain.Focus();
            firstStart = false;
        }

        private void ModeJeu_Deactivate(object sender, EventArgs e)
        {
            FonctionsNatives.desactiverPalettesDJ1();
            FonctionsNatives.desactiverPalettesDJ2();
            FonctionsNatives.desactiverPalettesGJ1();
            FonctionsNatives.desactiverPalettesGJ2();
        }
    }
}
