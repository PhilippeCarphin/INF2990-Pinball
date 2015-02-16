///////////////////////////////////////////////////////////////////////////////
/// @file UsineNoeudButoirCirculaire.h
/// @author The Ballers
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Usine
///////////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_USINES_USINENOEUDBUTOIRCIRCULAIRE_H__
#define __ARBRE_USINES_USINENOEUDBUTOIRCIRCULAIRE_H__

#include "UsineNoeud.h"
#include "NoeudButoirCirculaire.h"

///////////////////////////////////////////////////////////////////////////
/// @class UsineNoeudButoirCirculaire
/// @brief Classe qui represente une usine capable de creer des noeuds de
///        type NoeudButoirCirculaire.
///
/// @author The Ballers
/// @date 2015-01-24
/// @ingroup Usine
///////////////////////////////////////////////////////////////////////////
class UsineNoeudButoirCirculaire : public UsineNoeud
{
public:
	/// Constructeur
	inline UsineNoeudButoirCirculaire(const std::string& nom);

	/// Creation d'un noeud
	inline virtual NoeudAbstrait* creerNoeud() const;
};

//////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @fn inline UsineNoeudButoirCirculaire::UsineNoeudButoirCirculaire(const std::string& nom)
///
/// Ce constructeur ne fait qu'appeler la version de la classe de base
/// et donner des valeurs par defaut aux variables membres.
///
/// @param[in] nom   : Le nom de l'usine qui correspond au type de noeuds crees.
///
/// @return Aucune (constructeur).
///
//////////////////////////////////////////////////////////////////////////////////////////////////
inline UsineNoeudButoirCirculaire::UsineNoeudButoirCirculaire(const std::string& nom)
	: UsineNoeud(nom, std::string("media/objets/ButoirCirculaire.obj"))
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* UsineNoeudButoirCirculaire::creerNoeud() const
///
/// Cette fonction retourne un noeud nouvellement cree du type produit
/// par cette usine, soit un NoeudButoirCirculaire.
///
/// @return Le noeud nouvellement cree.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* UsineNoeudButoirCirculaire::creerNoeud() const
{
	auto noeud = new NoeudButoirCirculaire{ obtenirNom() };
	noeud->assignerObjetRendu(&modele_, &liste_);
	return noeud;
}

#endif // __ARBRE_USINES_USINENOEUDBUTOIRCIRCULAIRE_H__