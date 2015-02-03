///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurSelection.h
/// @author The Ballers
/// @date 2015-02-01
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#ifndef __VISITEURS_VISITEURSELECTION_H__
#define __VISITEURS_VISITEURSELECTION_H__

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
class VisiteurSelection : public VisiteurAbstrait
{
public:

	// Constructeur par d�faut : aucun d�placement
	VisiteurSelection(glm::dvec3 pointDansLeMonde);

	// Destructeur
	~VisiteurSelection();

	// Traiter une op�ration sur l'arbre de rendu et ses enfants
	virtual bool traiter(ArbreRenduINF2990* arbre);
	virtual bool traiter(NoeudAbstrait* noeud);
	virtual bool VisiteurSelection::traiter(NoeudTable* table);

private:
	
	// Ne touchez pas au constructeur par d�faut
	VisiteurSelection();
	
	// Point cliqu�
	glm::dvec3 pointDansLeMonde_;
};


#endif //__VISITEURS_VISITEURSELECTION_H__