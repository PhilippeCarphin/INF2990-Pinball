///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurSelection.h
/// @author The Ballers
/// @date 2015-02-01
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#ifndef __VISITEURS_VISITEURSELECTIONMULTIPLE_H__
#define __VISITEURS_VISITEURSELECTIONMULTIPLE_H__

#include "NoeudAbstrait.h"
#include "NoeudComposite.h"
#include "VisiteurAbstrait.h"
#include "glm\glm.hpp"

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurSelection
/// @brief Classe pour selectionner les objets de l'arbre de rendu
///
///        Instancier cette classe avec en param�tre le point cliqu�
///		   Ensuite, appelez la m�thode accepterVisiteur() de l'arbre de 
///		   rendu et lui fournir CE visiteur en param�tre
///
/// @author Yonni Chen
/// @date 2015-02-02
///////////////////////////////////////////////////////////////////////////
class VisiteurSelectionMultiple : public VisiteurAbstrait
{
public:

	// Constructeur par d�faut : aucun d�placement
	VisiteurSelectionMultiple(glm::dvec3 selectionBasGauche, glm::dvec3 selectionHautDroit);

	// Destructeur
	~VisiteurSelectionMultiple();

	// Traiter une op�ration sur l'arbre de rendu et ses enfants
	virtual bool traiter(ArbreRenduINF2990* arbre);
	virtual bool traiter(NoeudAbstrait* noeud);
	virtual bool traiter(NoeudTable* table);

	int obtenirNbObjetsSelectionne(){ return nbObjetsSelectionne_; }

private:

	// Ne touchez pas au constructeur par d�faut
	VisiteurSelectionMultiple();

	// Point cliqu�
	glm::dvec3 selectionBasGauche_, selectionHautDroit_;

	int nbObjetsSelectionne_;
};


#endif //__VISITEURS_VISITEURSELECTIONMULTIPLE_H__