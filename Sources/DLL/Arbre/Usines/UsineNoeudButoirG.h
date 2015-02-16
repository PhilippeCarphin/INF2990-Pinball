///////////////////////////////////////////////////////////////////////////////
/// @file UsineNoeudButoirG.h
/// @author Emilio Rivera
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Usine
///////////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_USINES_USINENOEUDBUTOIRG_H__
#define __ARBRE_USINES_USINENOEUDBUTOIRG_H__

#include "UsineNoeud.h"
#include "NoeudButoirG.h"

///////////////////////////////////////////////////////////////////////////
/// @class UsineNoeudButoirG
/// @brief Classe qui repr�sente une usine capable de cr�er des noeuds de
///        type NoeudButoirG.
///
/// @author Emilio Rivera
/// @date 2015-01-24
/// @ingroup Usine
///////////////////////////////////////////////////////////////////////////
class UsineNoeudButoirG : public UsineNoeud
{
public:
	/// Constructeur
	inline UsineNoeudButoirG(const std::string& nom);

	/// Cr�ation d'un noeud
	inline virtual NoeudAbstrait* creerNoeud() const;
};

///////////////////////////////////////////////////////////////////////////
///
/// @fn inline UsineNoeudButoirG::UsineNoeudButoirG(const std::string& nom)
///
/// Ce constructeur ne fait qu'appeler la version de la classe de base
/// et donner des valeurs par d�faut aux variables membres.
///
/// @param[in] nom   : Le nom de l'usine qui correspond au type de noeuds cr��s.
///
/// @return Aucune (constructeur).
///
///////////////////////////////////////////////////////////////////////////
inline UsineNoeudButoirG::UsineNoeudButoirG(const std::string& nom)
	: UsineNoeud(nom, std::string("media/objets/ButoirG.obj"))
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* UsineNoeudButoirG::creerNoeud() const
///
/// Cette fonction retourne un noeud nouvellement cr�� du type produit
/// par cette usine, soit un NoeudButoirG.
///
/// @return Le noeud nouvellement cr��.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* UsineNoeudButoirG::creerNoeud() const
{
	auto noeud = new NoeudButoirG{ obtenirNom() };
	noeud->assignerObjetRendu(&modele_, &liste_);
	return noeud;
}

#endif // __ARBRE_USINES_USINENOEUDBUTOIRG_H__