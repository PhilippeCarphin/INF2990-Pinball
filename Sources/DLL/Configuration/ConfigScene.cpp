////////////////////////////////////////////////////////////////////////////////////
/// @file ConfigScene.cpp
/// @author The Ballers
/// @date 2015-02-25
/// @version 1.0
///
/// @ingroup Configuration
///
////////////////////////////////////////////////////////////////////////////////////

#include "ConfigScene.h"
#include <fstream>

////////////////////////////////////////////////////////////////////////
///
/// @fn ConfigScene::ConfigScene()
///
/// Assigne les valeurs par d�faut des attributs de classe
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
ConfigScene::ConfigScene()
{
	derniereSauvegarde_ = "lastSave.bin";
	config_ = new int[12];
}


////////////////////////////////////////////////////////////////////////
///
/// @fn ConfigScene::~ConfigScene()
///
/// Detruit les informations internes relatives � la configuration
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
ConfigScene::~ConfigScene()
{
	delete[] config_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ConfigScene::sauvegarderConfiguration()
///
/// Cette fonction �crit les valeurs de la configuration dans un fichier binaire.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ConfigScene::sauvegarderConfiguration()
{
	std::fstream fichier;
	fichier.open(derniereSauvegarde_, std::ios::out | std::ios::binary);

	for (int i = 0; i < 12; i++)
		fichier.write((char*)&config_[i], sizeof(int));

	fichier.close();

}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool ConfigScene::lireConfiguration()
///
/// Cette fonction lit les valeurs de la configuration � de la derni�re
/// configuration de jeu.
///
/// @return True pour indiquer que la lecture s'est bien faite. False autrement
///
////////////////////////////////////////////////////////////////////////
bool ConfigScene::lireConfiguration()
{
	bool lectureOK = false;

	lireFichierBinaire();
	lectureOK = true;
	
	return lectureOK;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ConfigScene::lireFichierBinaire()
///
/// Cette fonction lit les valeurs de la configuration � partir d'un fichier binaire.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ConfigScene::lireFichierBinaire()
{
	std::fstream fichier;
	fichier.open(derniereSauvegarde_, std::ios::in | std::ios::binary);

	if (!fichier.fail())
	{
		for (int i = 0; i < 12; i++)
			fichier.read((char*)&config_[i], sizeof(int));

		fichier.close();
	}

}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ConfigScene::modifierConfiguration(int config[12])
///
/// Cette fonction assigne les nouvelles configurations de zone de jeu.
///
/// @param[in] config[12] : Un tableau contenant les informations de configuration
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ConfigScene::modifierConfiguration(int config[12])
{
	config_[0] = config[0];		// Palette gauche joueur 1
	config_[1] = config[1];		// Palette droite joueur 1
	config_[2] = config[2];		// Palette gauche joueur 2
	config_[3] = config[3];		// Palette droite joueur 2
	config_[4] = config[4];		// Ressort
	config_[5] = config[5];		// Nombre de billes par partie
	config_[6] = config[6];		// Mode double bille
	config_[7] = config[7];		// Mode force de rebond
	config_[8] = config[8];		// G�n�ration d'une bille
	config_[9] = config[9];		// Vitesse apr�s collision
	config_[10] = config[10];	// Activation de l'�clairage
	config_[11] = config[11];	// Champ d'attraction de portail
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////