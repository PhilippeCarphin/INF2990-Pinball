///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurDuplication.h
/// @author The Ballers
/// @date 2015-02-01
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#ifndef __VISITEURS_VISITEURDUPLICATION_H__
#define __VISITEURS_VISITEURDUPLICATION_H__

#include "NoeudAbstrait.h"
#include "VisiteurAbstrait.h"
#include <vector>

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurDuplication
/// @brief Classe pour selectionner les objets de l'arbre de rendu
///
///        Instancier cette classe avec en param�tre le point cliqu�
///		   Ensuite, appelez la m�thode accepterVisiteur() de l'arbre de 
///		   rendu et lui fournir CE visiteur en param�tre
///
/// @author The Ballers
/// @date 2015-02-02
///////////////////////////////////////////////////////////////////////////
class VisiteurDuplication : public VisiteurAbstrait
{
public:

	// Constructeur par param�tre
	VisiteurDuplication(glm::dvec3 pointDansLeMonde);

	// Destructeur
	~VisiteurDuplication();

	// Traiter une op�ration sur l'arbre de rendu et ses enfants
	virtual bool traiter(ArbreRenduINF2990* arbre);
	virtual bool traiter(NoeudAbstrait* noeud);
	virtual bool traiter(NoeudTable* table);

private:

	// Ne touchez pas au constructeur par d�faut
	VisiteurDuplication();

	// Point o� il y a eu le clic de la souris
	glm::dvec3 pointDansLeMonde_;

	// Contient les copies des objets selectionn�s
	std::vector<NoeudAbstrait*> copies_;

	// Pour le cas ou il y a eu selection multiple
	int minX, maxX, minY, maxY;

};


#endif //__VISITEURS_VISITEURDUPLICATION_H__