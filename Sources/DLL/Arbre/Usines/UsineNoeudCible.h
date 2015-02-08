///////////////////////////////////////////////////////////////////////////////
/// @file UsineNoeudCible.h
/// @author Emilio Rivera
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Usine
///////////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_USINES_USINENOEUDCIBLE_H__
#define __ARBRE_USINES_USINENOEUDCIBLE_H__

#include "UsineNoeud.h"
#include "NoeudCible.h"

///////////////////////////////////////////////////////////////////////////
/// @class UsineNoeudCible
/// @brief Classe qui repr�sente une usine capable de cr�er des noeuds de
///        type Cible.
///
/// @author Emilio Rivera
/// @date 2015-01-24
/// @ingroup Usine
///////////////////////////////////////////////////////////////////////////
class UsineNoeudCible : public UsineNoeud
{
public:
	/// Constructeur
	inline UsineNoeudCible(const std::string& nom);
	/// Cr�ation d'un noeud
	inline virtual NoeudAbstrait* creerNoeud() const;
};

///////////////////////////////////////////////////////////////////////////
///
/// @fn inline UsineNoeudCible::UsineNoeudCible(const std::string& nom)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par d�faut aux variables membres.
///
/// @param[in] nom   : Le nom de l'usine qui correspond au type de noeuds cr��s.
///
/// @return Aucune (constructeur).
///
///////////////////////////////////////////////////////////////////////////
inline UsineNoeudCible::UsineNoeudCible(const std::string& nom)
	: UsineNoeud(nom, std::string("media/objets/Cible.obj"))
{}

NoeudAbstrait* UsineNoeudCible::creerNoeud() const
{
	auto noeud = new NoeudCible{ obtenirNom() };
	noeud->assignerObjetRendu(&modele_, &liste_);
	return noeud;
}



#endif // __ARBRE_USINES_USINENOEUDCIBLE_H__