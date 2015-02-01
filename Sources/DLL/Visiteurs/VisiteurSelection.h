#ifndef __VISITEURS_VISITEURSELECTION_H__
#define __VISITEURS_VISITEURSELECTION_H__

#include "VisiteurAbstrait.h"
#include "glm\glm.hpp"

class VisiteurSelection : public VisiteurAbstrait
{
public:

	// Constructeur par d�faut : aucun d�placement
	VisiteurSelection();

	// Destructeur
	~VisiteurSelection();

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
	
	// Param�tre sp�cifiques?

};


#endif //__VISITEURS_VISITEURSELECTION_H__