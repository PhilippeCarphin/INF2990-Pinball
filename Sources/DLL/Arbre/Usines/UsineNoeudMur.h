///////////////////////////////////////////////////////////////////////////////
/// @file UsineNoeudMur.h
/// @author Emilio Rivera
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Usine
///////////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_USINES_USINENOEUDMUR_H__
#define __ARBRE_USINES_USINENOEUDMUR_H__

#include "UsineNoeud.h"
#include "NoeudMur.h"

///////////////////////////////////////////////////////////////////////////
/// @class UsineNoeudMur
/// @brief Classe qui repr�sente une usine capable de cr�er des noeuds de
///        type NoeudMur.
///
/// @author Emilio Rivera
/// @date 2015-01-24
/// @ingroup Usine
///////////////////////////////////////////////////////////////////////////
class UsineNoeudMur : public UsineNoeud
{
public:
	/// Constructeur
	inline UsineNoeudMur(const std::string& nom);

	/// Cr�ation d'un noeud
	inline virtual NoeudAbstrait* creerNoeud() const;
};


///////////////////////////////////////////////////////////////////////////////////////
///
/// @fn inline UsineNoeudMur::UsineNoeudMur(const std::string& nom)
///
/// Ce constructeur ne fait qu'appeler la version de la classe de base
/// et donner des valeurs par d�faut aux variables membres.
///
/// @param[in] nom   : Le nom de l'usine qui correspond au type de noeuds cr��s.
///
/// @return Aucune (constructeur).
///
///////////////////////////////////////////////////////////////////////////////////////
inline UsineNoeudMur::UsineNoeudMur(const std::string& nom)
	: UsineNoeud(nom, std::string("media/objets/Mur.obj"))
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* UsineNoeudMur::creerNoeud() const
///
/// Cette fonction retourne un noeud nouvellement cr�� du type produit
/// par cette usine, soit un NoeudMur.
///
/// @return Le noeud nouvellement cr��.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* UsineNoeudMur::creerNoeud() const
{
	auto noeud = new NoeudMur{ obtenirNom() };
	noeud->assignerObjetRendu(&modele_, &liste_);
	return noeud;
}

#endif // __ARBRE_USINES_USINENOEUDMUR_H__