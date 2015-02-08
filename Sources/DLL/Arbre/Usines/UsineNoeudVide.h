///////////////////////////////////////////////////////////////////////////////
/// @file UsineNoeudVide.h
/// @author Emilio Rivera
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Usine
///////////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_USINES_USINENOEUDVIDE_H__
#define __ARBRE_USINES_USINENOEUDVIDE_H__

#include "UsineNoeud.h"
#include "NoeudVide.h"

///////////////////////////////////////////////////////////////////////////
/// @class UsineNoeudVide
/// @brief Classe qui repr�sente une usine capable de cr�er des noeuds de
///        type Vide.
///
/// @author Emilio Rivera
/// @date 2015-01-24
/// @ingroup Usine
///////////////////////////////////////////////////////////////////////////
class UsineNoeudVide : public UsineNoeud
{
public:
	/// Constructeur
	inline UsineNoeudVide(const std::string& nom);
	/// Cr�ation d'un noeud
	inline virtual NoeudAbstrait* creerNoeud() const;
};

///////////////////////////////////////////////////////////////////////////
///
/// @fn inline UsineNoeudVide::UsineNoeudVide(const std::string& nom)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par d�faut aux variables membres.
///
/// @param[in] nom   : Le nom de l'usine qui correspond au type de noeuds cr��s.
///
/// @return Aucune (constructeur).
///
///////////////////////////////////////////////////////////////////////////
inline UsineNoeudVide::UsineNoeudVide(const std::string& nom)
	: UsineNoeud(nom, std::string("media/objets/Vide.obj"))
{

}

#endif // __ARBRE_USINES_USINENOEUDVIDE_H__