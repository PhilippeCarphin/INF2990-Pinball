///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurSuppression.h
/// @author The Ballers
/// @date 2015-02-01
/// @version 1.0
///
/// @ingroup Visiteur
///////////////////////////////////////////////////////////////////////////////
#ifndef __VISITEURS_VISITEURXML_H__
#define __VISITEURS_VISITEURXML_H__

#include "VisiteurAbstrait.h"
#include <string>

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurSuppression
/// @brief Classe pour enregistrer l'information de l'arbre de rendu
///		   dans un fichier XML.
///
///        Instancier cette classe avec en param�tre le nom du fichier avec
///		   l'extension .xml . Ensuite, appelee la m�thode accepterVisiteur()
///		   de l'arbre de rendu et lui fournir CE visiteur en param�tre
///
/// @author Yonni Chen
/// @date 2015-02-02
/// @ingroup Visiteur
///////////////////////////////////////////////////////////////////////////
class VisiteurSuppression : public VisiteurAbstrait
{
public:

	/// Constructeur par param�tre : fournir le nom du fichier de sauvegarde et les propri�t�s du jeu
	VisiteurSuppression(std::string nomFichier, int proprietes[]);

	/// Destructeur
	~VisiteurSuppression();

	/// Traiter un arbre de rendu et ses enfants
	virtual bool traiter(ArbreRenduINF2990* arbre);

	/// Traiter la table de l'arbre de rendu
	virtual bool traiter(NoeudTable* table);

	/// Traiter une feuille
	virtual bool traiter(NoeudAbstrait* noeud);

private:

	/// Constructeur par d�faut
	VisiteurSuppression();

	std::string nomFichier; ///< Nom du fichier � lire ou � �crire.
	int* proprietes_ = new int[6]; ///< Propri�t�s de la partie � lire ou �crire

};

#endif //__VISITEURS_VISITEURXML_H__