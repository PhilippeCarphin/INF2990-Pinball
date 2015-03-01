///////////////////////////////////////////////////////////////////////////
/// @file NoeudPaletteG.h
/// @author The Ballers
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////

#ifndef  __ARBRE_NOEUDS_NOEUDPALETTEG_H__
#define  __ARBRE_NOEUDS_NOEUDPALETTEG_H__

#include "NoeudComposite.h"
#include "Gl/gl.h"

///////////////////////////////////////////////////////////////////////////
/// @class NoeudPaletteG
/// @brief Classe qui represente une palette gauche.
///
/// @author The Ballers
/// @date 2015-01-24
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////
class NoeudPaletteG : public NoeudComposite
{
public:
	/// Constructeur
	NoeudPaletteG(const std::string& typeNoeud);

	/// Destructeur 
	~NoeudPaletteG();

	/// Surchage de la methode qui affiche l'objet.
	virtual void afficherConcret() const;

	/// Surchage de la methode qui anime l'objet.
	virtual void animer(float temps);

	/// Accepte un visiteur.
	virtual bool accepterVisiteur(VisiteurAbstrait* vis);

	void activer(){};
	void desactiver(){};

private:
	/// Angle Original pour le mouvement des palettes selon les touches du clavier
	double angleZOriginal;
	
	/// Angle selon l'axe des X.
	float angleX_{ 0.f };

	/// Angle selon l'axe des Y.
	float angleY_{ 0.f };

	/// Angle de rotation.
	float angleRotation_{ 0.f };
};

#endif // __ARBRE_NOEUDS_NOEUDPALETTEG_H__