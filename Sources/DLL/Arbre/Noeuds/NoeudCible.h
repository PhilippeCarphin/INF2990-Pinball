///////////////////////////////////////////////////////////////////////////
/// @file NoeudCible.h
/// @author The Ballers
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////

#ifndef __ARBRES_NOEUDS_NOEUDCIBLE_H__
#define __ARBRES_NOEUDS_NOEUDCIBLE_H__

#include "NoeudComposite.h"
#include "Gl/gl.h"

///////////////////////////////////////////////////////////////////////////
/// @class NoeudCible
/// @brief Classe qui repr�sente une cible.
///
/// @author The Ballers
/// @date 2015-01-24
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////
class NoeudCible : public NoeudComposite
{
public:
	/// Constructeur
	NoeudCible(const std::string& typeNoeud);

	/// Destructeur 
	~NoeudCible();

	/// Surchage de la m�thode qui affiche l'objet.
	virtual void afficherConcret() const;

	/// Surchage de la m�thode qui anime l'objet.
	virtual void animer(float temps);

	/// Accepte un visiteur.
	virtual bool accepterVisiteur(VisiteurAbstrait* vis);

private:

	/// Angle selon l'axe des X.
	float angleX_{ 0.f };

	/// Angle selon l'axe des Y.
	float angleY_{ 0.f };

	/// Angle de rotation.
	float angleRotation_{ 0.f };
};

#endif // __ARBRE_NOEUDS_NOEUDCIBLE_H__