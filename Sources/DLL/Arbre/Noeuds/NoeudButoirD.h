///////////////////////////////////////////////////////////////////////////
/// @file NoeudButoirD.h
/// @author Yonni Chen
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////

#ifndef __ARBRE_NOEUDS_NOEUDBUTOIRD_H__
#define __ARBRE_NOEUDS_NOEUDBUTOIRD_H__


#include "NoeudComposite.h"

///////////////////////////////////////////////////////////////////////////
/// @class NoeudButoirD
/// @brief Classe qui repr�sente un butoir.
///
/// @author Julien Gascon-Samson
/// @date 2011-05-19
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////
class NoeudButoirD : public NoeudComposite
{
public:

	/// Constructeur � partir du type du noeud.
	NoeudButoirD(const std::string& typeNoeud);

	/// Destructeur.
	~NoeudButoirD();

	/// Affiche le butoir.
	virtual void afficherConcret() const;

	/// Effectue l'animation du butoir.
	virtual void animer(float temps);

	/// Accepte un visiteur.
	virtual bool accepterVisiteur(VisiteurAbstrait* vis);

private:

	/// Angle dans le sinus de l'oscillation
	float angle_{ 0 };

};

#endif // __ARBRE_NOEUDS_NOEUDBUTOIRD_H__