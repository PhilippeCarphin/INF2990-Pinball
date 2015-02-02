#ifndef __ARBRES_NOEUDS_NOEUDBUTOIRCIRCULAIRE_H__
#define __ARBRES_NOEUDS_NOEUDBUTOIRCIRCULAIRE_H__

#include "NoeudComposite.h"
#include "Gl/gl.h"

class NoeudButoirCirculaire : public NoeudComposite
{
public:
	// Constructeur
	NoeudButoirCirculaire(const std::string& typeNoeud);
	// Destructeur 
	~NoeudButoirCirculaire();

	// Surchage de la m�thode qui affiche l'objet
	virtual void afficherConcret() const;
	// Surchage de la m�thode qui anime l'objet
	virtual void animer(float temps);

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

#endif // __ARBRES_NOEUDS_NOEUDBUTOIRCIRCULAIRE_H__