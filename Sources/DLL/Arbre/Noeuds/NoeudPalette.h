///////////////////////////////////////////////////////////////////////////
/// @file NoeudPalette.h
/// @author Yonni Chen
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////

#ifndef  __ARBRE_NOEUDS_NOEUDPALETTE_H__
#define  __ARBRE_NOEUDS_NOEUDPALETTE_H__

#include "NoeudComposite.h"
#include "Gl/gl.h"

///////////////////////////////////////////////////////////////////////////
/// @class NoeudPalette
/// @brief Classe qui repr�sente une palette.
///
/// @author Yonni Chen
/// @date 2015-01-24
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////
class NoeudPalette : public NoeudComposite
{
public:
	/// Constructeur
	NoeudPalette(const std::string& typeNoeud);
	/// Destructeur 
	~NoeudPalette();

	/// Surchage de la m�thode qui affiche l'objet.
	virtual void afficherConcret() const;

	/// Surchage de la m�thode qui anime l'objet.
	virtual void animer(float temps);

	/// Accepte un visiteur.
	virtual bool accepterVisiteur(VisiteurAbstrait* vis);

private:
	// TODO(Emilio): Ins�rer les attributs propres � chaque type d'objet
	/// Angle selon l'axe des X.
	float angleX_{ 0.f };
	/// Angle selon l'axe des Y.
	float angleY_{ 0.f };
	/// Angle de rotation.
	float angleRotation_{ 0.f };
};

#endif // __ARBRE_NOEUDS_NOEUDPALETTE_H__