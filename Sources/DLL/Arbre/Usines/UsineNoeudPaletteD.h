///////////////////////////////////////////////////////////////////////////////
/// @file UsineNoeudPaletteD.h
/// @author Emilio Rivera
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Usine
///////////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_USINES_USINENOEUDPALETTED_H__
#define __ARBRE_USINES_USINENOEUDPALETTED_H__

#include "UsineNoeud.h"
#include "NoeudPaletteD.h"

///////////////////////////////////////////////////////////////////////////
/// @class UsineNoeudPaletteD
/// @brief Classe qui repr�sente une usine capable de cr�er des noeuds de
///        type Palette.
///
/// @author Emilio Rivera
/// @date 2015-01-24
/// @ingroup Usine
///////////////////////////////////////////////////////////////////////////
class UsineNoeudPaletteD : public UsineNoeud
{
public:
	/// Constructeur
	inline UsineNoeudPaletteD(const std::string& nom);
	/// Cr�ation d'un noeud
	inline virtual NoeudAbstrait* creerNoeud() const;
};

///////////////////////////////////////////////////////////////////////////
///
/// @fn inline UsineNoeudPaletteD::UsineNoeudPaletteD(const std::string& nom)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par d�faut aux variables membres.
///
/// @param[in] nom   : Le nom de l'usine qui correspond au type de noeuds cr��s.
///
/// @return Aucune (constructeur).
///
///////////////////////////////////////////////////////////////////////////
inline UsineNoeudPaletteD::UsineNoeudPaletteD(const std::string& nom)
	: UsineNoeud(nom, std::string("media/objets/PaletteD.obj"))
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* UsineNoeudPaletteD::creerNoeud() const
///
/// Cette fonction retourne un noeud nouvellement cr�� du type produit
/// par cette usine, soit une palette.
///
/// @return Le noeud nouvellement cr��.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* UsineNoeudPaletteD::creerNoeud() const
{
	auto noeud = new NoeudPaletteD{ obtenirNom() };
	noeud->assignerObjetRendu(&modele_, &liste_);
	return noeud;
}

#endif // __ARBRE_USINES_USINENOEUDPALETTED_H__