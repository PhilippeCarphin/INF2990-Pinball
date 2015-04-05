///////////////////////////////////////////////////////////////////////////////
/// @file ControleurLumieres.h
/// @author The ballers
/// @date 2015-03-20
/// @version 1.0
///
/// @ingroup Eclairage
///////////////////////////////////////////////////////////////////////////////

#ifndef __ECLAIRAGE_CONTROLEUR_LUMIERES_H__
#define __ECLAIRAGE_CONTROLEUR_LUMIERES_H__

#include "Lumiere.h"


////////////////////////////////////////////////////////////////////////////////
///
/// @class ControleurLumieres
/// @brief Cette classe controle les lumieres.  Elle s'occuppe de definir leurs
/// couleurs, position etc. et de les envoyer au serveur OpenGL.
/// 
/// @author The ballers
/// @date 2015-04-02
////////////////////////////////////////////////////////////////////////////////
class ControleurLumieres
{

public:
	
	/// Constructeur
	ControleurLumieres();

	/// Destructeur
	~ControleurLumieres();

	/// Donne les valeurs choisies par le controleur aux lumieres
	void initialiserLumieres();

	/// Passe les donnees des lumieres au serveur OpenGL
	void definirLumieres();

	/// Activer la lumiere Ambiante
	void activerAmbiante();
	/// Desactiver la lumiere ambiante
	void desactiverAmbiante();

	/// Activer la lumiere directionnnelle
	void activerDirectionnelle();

	/// Desactiver la lumiere directionnelle
	void desactiverDirectionnelle();

	/// Activer la lumiere spot
	void activerSpot();
	/// Desactiver la lumiere spot
	void desactiverSpot();


	// Touche utilisees pour l'experimentation
	void touche1();
	void touche2();
	void touche3();

private:

	/// Objet pour la lumiere ambiante
	Lumiere* lumAmbiante_;

	/// Objet pour la lumiere directionnelle
	Lumiere* lumDirectionnelle_;

	/// Objet pour la lumiere spot
	Lumiere* lumSpot_;

};

#endif // __ECLAIRAGE_CONTROLEUR_LUMIERES_H__