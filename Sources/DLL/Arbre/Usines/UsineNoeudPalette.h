///////////////////////////////////////////////////////////////////////////////
/// @file UsineNoeudPalette.h
/// @author Emilio Rivera
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Usine
///////////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_USINES_USINENOEUDPALETTE_H__
#define __ARBRE_USINES_USINENOEUDPALETTE_H__

#include "UsineNoeud.h"
#include "NoeudPalette.h"

///////////////////////////////////////////////////////////////////////////
/// @class UsineNoeudPalette
/// @brief Classe qui repr�sente une usine capable de cr�er des noeuds de
///        type Palette.
///
/// @author Emilio Rivera
/// @date 2015-01-24
/// @ingroup Usine
///////////////////////////////////////////////////////////////////////////
class UsineNoeudPalette : public UsineNoeud
{
public:
	/// Constructeur
	inline UsineNoeudPalette(const std::string& nom);
	/// Cr�ation d'un noeud
	inline virtual NoeudAbstrait* creerNoeud() const;
};

///////////////////////////////////////////////////////////////////////////
///
/// @fn inline UsineNoeudPalette::UsineNoeudPalette(const std::string& nom)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par d�faut aux variables membres.
///
/// @param[in] nom   : Le nom de l'usine qui correspond au type de noeuds cr��s.
///
/// @return Aucune (constructeur).
///
///////////////////////////////////////////////////////////////////////////
inline UsineNoeudPalette::UsineNoeudPalette(const std::string& nom)
	: UsineNoeud(nom, std::string("media/objets/Palette.obj"))
{}

NoeudAbstrait* UsineNoeudPalette::creerNoeud() const
{
	auto noeud = new NoeudPalette{ obtenirNom() };
	noeud->assignerObjetRendu(&modele_, &liste_);
	return noeud;
}


#endif // __ARBRE_USINES_USINENOEUDPALETTE_H__