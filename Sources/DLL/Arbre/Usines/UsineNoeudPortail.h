///////////////////////////////////////////////////////////////////////////////
/// @file UsineNoeudPortail.h
/// @author Emilio Rivera
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Usine
///////////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_USINES_USINENOEUDPORTAIL_H__
#define __ARBRE_USINES_USINENOEUDPORTAIL_H__

#include "UsineNoeud.h"
#include "NoeudPortail.h"

///////////////////////////////////////////////////////////////////////////
/// @class UsineNoeudPortail
/// @brief Classe qui repr�sente une usine capable de cr�er des noeuds de
///        type Portail.
///
/// @author Emilio Rivera
/// @date 2015-01-24
/// @ingroup Usine
///////////////////////////////////////////////////////////////////////////
class UsineNoeudPortail : public UsineNoeud
{
public:
	/// Constructeur
	inline UsineNoeudPortail(const std::string& nom);
	/// Cr�ation d'un noeud
	inline virtual NoeudAbstrait* creerNoeud() const;
};

///////////////////////////////////////////////////////////////////////////
///
/// @fn inline UsineNoeudPortail::UsineNoeudPortail(const std::string& nom)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par d�faut aux variables membres.
///
/// @param[in] nom   : Le nom de l'usine qui correspond au type de noeuds cr��s.
///
/// @return Aucune (constructeur).
///
///////////////////////////////////////////////////////////////////////////
inline UsineNoeudPortail::UsineNoeudPortail(const std::string& nom)
	: UsineNoeud(nom, std::string("media/objets/Portail.obj"))
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* UsineNoeudPortail::creerNoeud() const
///
/// Cette fonction retourne un noeud nouvellement cr�� du type produit
/// par cette usine, soit un butoir circulaire.
///
/// @return Le noeud nouvellement cr��.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* UsineNoeudPortail::creerNoeud() const
{
	auto noeud = new NoeudPortail{ obtenirNom() };
	noeud->assignerObjetRendu(&modele_, &liste_);
	return noeud;
}

#endif // __ARBRE_USINES_USINENOEUDPORTAIL_H__