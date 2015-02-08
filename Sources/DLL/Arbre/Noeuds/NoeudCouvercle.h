///////////////////////////////////////////////////////////////////////////
/// @file NoeudCouvercle.h
/// @author Yonni Chen
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////

#ifndef  __ARBRE_NOEUDS_NOEUDCOUVERCLE_H__
#define  __ARBRE_NOEUDS_NOEUDCOUVERCLE_H__

#include "NoeudComposite.h"
#include "Gl/gl.h"

///////////////////////////////////////////////////////////////////////////
/// @class NoeudCouvercle
/// @brief Classe qui repr�sente un couvercle.
///
/// @author Yonni Chen
/// @date 2015-01-24
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////
class NoeudCouvercle : public NoeudComposite
{
public:
	/// Constructeur
	NoeudCouvercle(const std::string& typeNoeud);

	/// Destructeur 
	~NoeudCouvercle();

	/// Surchage de la m�thode qui affiche l'objet
	virtual void afficherConcret() const;

	/// Surchage de la m�thode qui anime l'objet
	virtual void animer(float temps);

	/// Accepte un visiteur.
	virtual bool accepterVisiteur(VisiteurAbstrait* vis);

	/// Retourne l'enfant du noeud courant.
	virtual NoeudAbstrait* getEnfant(int i) { return NoeudComposite::getEnfant(i); };
	 
private:
	// TODO(Emilio): Ins�rer les attributs propres � chaque type d'objet
	/// Angle selon l'axe des X.
	float angleX_{ 0.f };
	/// Angle selon l'axe des Y.
	float angleY_{ 0.f };
	/// Angle de rotation.
	float angleRotation_{ 0.f };
};

#endif // __ARBRE_NOEUDS_NOEUDCOUVERCLE_H__