#ifndef __VISITEURS_VISITEURXML_H__
#define __VISITEURS_VISITEURXML_H__

#include "VisiteurAbstrait.h"
#include "tinyxml2.h"
#include <iostream>

class VisiteurXML : public VisiteurAbstrait
{
public:

	// Constructeur par d�faut : aucun d�placement
	VisiteurXML(std::string nomFichier);

	// Destructeur
	~VisiteurXML();

	// Traiter une op�ration selon le type sp�cifique de l'objet en param�tre
	virtual bool traiter(ArbreRenduINF2990* arbre);
	virtual bool traiter(NoeudAbstrait* noeud, tinyxml2::XMLElement* parent);
	virtual bool traiter(NoeudButoir* butoir, tinyxml2::XMLElement* parent);
	virtual bool traiter(NoeudCible* cible, tinyxml2::XMLElement* parent);
	virtual bool traiter(NoeudGenerateurBille* generateur, tinyxml2::XMLElement* parent);
	virtual bool traiter(NoeudMur* mur, tinyxml2::XMLElement* parent);
	virtual bool traiter(NoeudPalette* palette, tinyxml2::XMLElement* parent);
	virtual bool traiter(NoeudPortail* portail, tinyxml2::XMLElement* parent);
	virtual bool traiter(NoeudRessort* ressort, tinyxml2::XMLElement* parent);
	virtual bool traiter(NoeudTrou* trou, tinyxml2::XMLElement* parent);
	virtual bool traiter(NoeudTable* table, tinyxml2::XMLElement* parent);

private:

	tinyxml2::XMLDocument document;
	std::string nomFichier;
	
};


#endif //__VISITEURS_VISITEURSELECTION_H__