//////////////////////////////////////////////////////////////////////////////
/// @file ConfigScene.h
/// @author Jean-Fran�ois P�russe
/// @date 2007-01-10
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __CONFIGURATION_CONFIGSCENE_H__
#define __CONFIGURATION_CONFIGSCENE_H__

#include "tinyxml2.h"

///////////////////////////////////////////////////////////////////////////
/// @class ConfigScene
/// @brief Les variables de configuration de la classe CScene.
///        C'est une classe singleton.
///
/// @author Jean-Fran�ois P�russe
/// @date 2007-01-10
///////////////////////////////////////////////////////////////////////////
class ConfigScene
{

public:

	ConfigScene();
	~ConfigScene();

	void sauvegarderConfiguration();

	bool lireConfiguration();

	void modifierConfiguration(int* touche, bool doubleBille, bool rebond, bool* debogage);

private:

	int* touches_;
	bool doubleBille_, rebond_;
	bool* debogage_;

	std::string fichierDefaut_, derniereSauvegarde_;
	tinyxml2::XMLDocument document_;

	void lireXML();

};


#endif // __CONFIGURATION_CONFIGSCENE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
