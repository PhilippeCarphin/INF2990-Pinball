///////////////////////////////////////////////////////////////////////////////
/// @file UsineNoeudCouvercle.h
/// @author Emilio Rivera
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Usine
///////////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_USINES_USINENOEUDCOUVERCLE_H__
#define __ARBRE_USINES_USINENOEUDCOUVERCLE_H__

#include "UsineNoeud.h"
#include "NoeudCouvercle.h"

///////////////////////////////////////////////////////////////////////////
/// @class UsineNoeudCouvercle
/// @brief Classe qui repr�sente une usine capable de cr�er des noeuds de
///        type Couvercle.
///
/// @author Emilio Rivera
/// @date 2015-01-24
/// @ingroup Usine
///////////////////////////////////////////////////////////////////////////
class UsineNoeudCouvercle : public UsineNoeud
{
public:
	/// Constructeur
	inline UsineNoeudCouvercle(const std::string& nom);
	/// Cr�ation d'un noeud
	inline virtual NoeudAbstrait* creerNoeud() const;
};

///////////////////////////////////////////////////////////////////////////
///
/// @fn inline UsineNoeudCouvercle::UsineNoeudCouvercle(const std::string& nom)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par d�faut aux variables membres.
///
/// @param[in] nom   : Le nom de l'usine qui correspond au type de noeuds cr��s.
///
/// @return Aucune (constructeur).
///
///////////////////////////////////////////////////////////////////////////
inline UsineNoeudCouvercle::UsineNoeudCouvercle(const std::string& nom)
	: UsineNoeud(nom, std::string("media/objets/Couvercle.obj"))
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* UsineNoeudCouvercle::creerNoeud() const
///
/// Cette fonction retourne un noeud nouvellement cr�� du type produit
/// par cette usine, soit un couvercle.
///
/// @return Le noeud nouvellement cr��.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* UsineNoeudCouvercle::creerNoeud() const
{
	auto noeud = new NoeudCouvercle{ obtenirNom() };
	noeud->assignerObjetRendu(&modele_, &liste_);
	return noeud;
}

#endif // __ARBRE_USINES_USINENOEUDCOUVERCLE_H__