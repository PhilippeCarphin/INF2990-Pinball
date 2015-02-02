#ifndef __VISITEURS_VISITEURDEPLACEMENT_H__
#define __VISITEURS_VISITEURDEPLACEMENT_H__

#include "VisiteurAbstrait.h"
#include "glm\glm.hpp"

class VisiteurDeplacement : public VisiteurAbstrait
{
public:

	// Constructeur par d�faut : aucun d�placement
	VisiteurDeplacement();

	// Constructeur par param�tre : sp�cifiez un vecteur de d�placement
	VisiteurDeplacement(glm::dvec3 dep);

	// Destructeur
	~VisiteurDeplacement();

	// M�thode d'acces
	double getDeplacementX() { return deplacement_[0]; };
	double getDeplacementY() { return deplacement_[1]; };
	double getDeplacementZ() { return deplacement_[2]; };
	glm::dvec3 getDeplacement() { return deplacement_; };

	// M�thode de modifications
	void setDeplacementX(float x) { deplacement_[0] = x; };
	void setDeplacementY(float y) { deplacement_[1] = y; };
	void setDeplacementZ(float z) { deplacement_[2] = z; };
	void setDeplacement(glm::dvec3 dep) { deplacement_ = dep; };

	// Traiter une op�ration selon le type sp�cifique de l'objet en param�tre
	virtual bool traiter(ArbreRenduINF2990* arbre);
	virtual bool traiter(NoeudAbstrait* noeud);
	virtual bool traiter(NoeudButoir* butoir);
	virtual bool traiter(NoeudCible* cible);
	virtual bool traiter(NoeudGenerateurBille* generateur);
	virtual bool traiter(NoeudMur* mur);
	virtual bool traiter(NoeudPalette* palette);
	virtual bool traiter(NoeudPortail* portail);
	virtual bool traiter(NoeudRessort* ressort);
	virtual bool traiter(NoeudTrou* trou);
	virtual bool traiter(NoeudTable* table);

private:

	glm::dvec3 deplacement_;

};


#endif //__VISITEURS_VISITEURDEPLACEMENT_H__