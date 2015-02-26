//////////////////////////////////////////////////////////////////////////////
/// @file ConfigScene.h
/// @author The Ballers
/// @date 2015-02-25
/// @version 1.0
///
/// @ingroup Configuration
///
//////////////////////////////////////////////////////////////////////////////
#ifndef __CONFIGURATION_CONFIGSCENE_H__
#define __CONFIGURATION_CONFIGSCENE_H__

#include <string>

///////////////////////////////////////////////////////////////////////////
/// @class ConfigScene
/// @brief Les variables de configuration de la classe CScene.
///
/// @author The Ballers
/// @date 2015-02-25
///////////////////////////////////////////////////////////////////////////
class ConfigScene
{

public:

	// Constructeur
	ConfigScene();

	// Destructeur
	~ConfigScene();

	// Sauvegarder en fichier binaire
	void sauvegarderConfiguration();

	// Lire le fichier de la derni�re configuration
	bool lireConfiguration();

	// Modifier les variables de configuration
	void modifierConfiguration(int config[12]);

	// Retourne les configurations de l'objets
	int* obtenirConfiguration() const { return config_; };

private:

	// Lis un fichier binaire
	void lireFichierBinaire();

	// Contient toutes les informations relative � la configuration du jeu
	int* config_;

	// Nom de la derni�re sauvegarde
	std::string derniereSauvegarde_;

};


#endif // __CONFIGURATION_CONFIGSCENE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////