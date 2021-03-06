﻿//////////////////////////////////////////////////////////////////////////////
/// @file Proprietes.cs
/// @author Ballers
/// @date 2015-01-27
/// @version 1.0 
///
/// @ingroup Fenetres
//////////////////////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace InterfaceGraphique
{
    ///////////////////////////////////////////////////////////////////////////
    /// @class Proprietes
    /// @brief Fenetre des proprietes de la partie.
    ///
    /// @author The Ballers
    /// @date 2015-01-27
    /// 
    /// @ingroup Fenetres
    ///////////////////////////////////////////////////////////////////////////
    public partial class Proprietes : Form
    {
        public List<int> mesProp; ///< Liste des proprietes
        string errorMessage = "";

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public Proprietes(List<int> a)
        /// @brief Constructeur par parameetre de la fenetre.
        /// 
        /// param[in] a : Liste des proprietes a instancier.
        /// 
        /// @return Aucune (constructeur).
        ///
        ////////////////////////////////////////////////////////////////////////
        public Proprietes(List<int> a)
        {
            InitializeComponent();
            mesProp = a;
            ptsButCirc_Box.Text = mesProp[0].ToString();
            ptsButTri_Box.Text = mesProp[1].ToString();
            ptsCible_Box.Text = mesProp[2].ToString();
            ptsVictoire_Box.Text = mesProp[3].ToString();
            ptsFreeBall_Box.Text = mesProp[4].ToString();
            difficulte_ComboBox.Text = mesProp[5].ToString();
            
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private bool checkValue()
        /// @brief Verifie que les valeurs entrees par l'utilisateur sont valides.
        /// 
        /// @return True si les valeurs entrees sont valides, false sinon.
        ///
        ////////////////////////////////////////////////////////////////////////
        private bool checkValue()
        {
            int n;
            bool isValid = true;
          
            if( !(int.TryParse(ptsButCirc_Box.Text, out n))){
                isValid = false;
                errorMessage += "\nLa valeur des points pour un butoir circulaire est invalide";
            }
            else
            {
                if( (n <= 0) || (n > 10000))
                {
                    isValid = false;
                    errorMessage += "\nLa valeur des points pour un butoir circulaire est hors de la limite( 0 a 10000) ";
                }
                    
            }
            if (!(int.TryParse(ptsButTri_Box.Text, out n)))
            {
                isValid = false;
                errorMessage += "\nLa valeur des points pour un butoir triangulaire est invalide";
            }
            else
            {
                if ((n <= 0) || (n > 10000))
                {
                    isValid = false;
                    errorMessage += "\nLa valeur des points pour un butoir triangulaire est hors la limite( 0 a 10000) ";
                }

            }
            if (!(int.TryParse(ptsCible_Box.Text, out n)))
            {
                isValid = false;
                errorMessage += "\nLa valeur des points pour une cible est invalide";
            }
            else
            {
                if ((n <= 0) || (n > 10000))
                {
                    isValid = false;
                    errorMessage += "\nLa valeur des points pour une cible est hors la limite( 0 a 10000) ";
                }

            }
            if (!(int.TryParse(ptsVictoire_Box.Text, out n)))
            {
                isValid = false;
                errorMessage += "\nLa valeur des points pour une victoire est invalide";
            }
            else
            {
                if ((n <= 0) || (n > 10000))
                {
                    isValid = false;
                    errorMessage += "\nLa valeur des points pour une victoire est hors la limite( 0 a 10000) ";
                }

            }
            if (!(int.TryParse(ptsFreeBall_Box.Text, out n)))
            {
                isValid = false;
                errorMessage += "\nLa valeur des points pour une balle gratuite est invalide";
            }
            else
            {
                if ((n <= 0) || (n > 10000))
                {
                    isValid = false;
                    errorMessage += "\nLa valeur des points pour une balle gratuite est hors la limite( 0 a 10000) ";
                }

            }
            if (!(int.TryParse(difficulte_ComboBox.Text, out n)))
            {
                isValid = false;
                errorMessage += "\nLa valeur de la difficulte est invalide";
            }
            else
            {
                if ((n < 1) || (n > 10))
                {
                    isValid = false;
                    errorMessage += "\nLa valeur de difficulte est hors la limite(1 a 10) ";
                }

            }

            return isValid;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void propAnnuler_Bouton_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le bouton Annuler.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void propAnnuler_Bouton_Click(object sender, EventArgs e)
        {
            this.Close();        

        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public List<int> getProps()
        /// @brief Accesseur de l'attribut des proprietes.
        /// 
        /// @return La liste des proprietes de jeu.
        ///
        ////////////////////////////////////////////////////////////////////////
        public List<int> getProps()
        {
            return mesProp;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void propConfirm_Bouton_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le bouton Confirmer.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void propConfirm_Bouton_Click(object sender, EventArgs e)
        {

            if (checkValue())
            {
                mesProp[0] = Convert.ToInt32(ptsButCirc_Box.Text);
                mesProp[1] = Convert.ToInt32(ptsButTri_Box.Text);
                mesProp[2] = (Convert.ToInt32(ptsCible_Box.Text));
                mesProp[3] =(Convert.ToInt32(ptsVictoire_Box.Text));
                mesProp[4] = (Convert.ToInt32(ptsFreeBall_Box.Text));
                mesProp[5] = (Convert.ToInt32(difficulte_ComboBox.Text));
                this.Hide();
            }
            else
            {
                MessageBox.Show(errorMessage, "Valeurs incorrectes",
                MessageBoxButtons.OK, MessageBoxIcon.Error);
                errorMessage = "";
            }
           
          // this.Close();
        }

        
    }
}
