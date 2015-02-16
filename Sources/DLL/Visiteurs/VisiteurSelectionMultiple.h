///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurSelectionMultiple.h
/// @author The Ballers
/// @date 2015-02-01
/// @version 1.0
///
/// @ingroup Visiteur
///////////////////////////////////////////////////////////////////////////////
#ifndef __VISITEURS_VISITEURSELECTIONMULTIPLE_H__
#define __VISITEURS_VISITEURSELECTIONMULTIPLE_H__

#include "NoeudAbstrait.h"
#include "VisiteurAbstrait.h"
#include "glm\glm.hpp"

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurSelectionMultiple
/// @brief Classe pour selectionner les objets de l'arbre de rendu
///
///        Instancier cette classe avec en param�tre le point cliqu�
///		   Ensuite, appeler la m�thode accepterVisiteur() de l'arbre de 
///		   rendu et lui fournir CE visiteur en param�tre
///
/// @author Philippe Carphin
/// @date 2015-02-02
/// @ingroup Visiteur
///////////////////////////////////////////////////////////////////////////
class VisiteurSelectionMultiple : public VisiteurAbstrait
{
public:

	/// Constructeur par param�tre
	VisiteurSelectionMultiple(glm::dvec3 selectionBasGauche, glm::dvec3 selectionHautDroit);

	/// Destructeur
	~VisiteurSelectionMultiple();

	/// Traiter une op�ration sur l'arbre de rendu et ses enfants
	virtual bool traiter(ArbreRenduINF2990* arbre);
	virtual bool traiter(NoeudAbstrait* noeud);
	virtual bool traiter(NoeudTable* table);

	//////////////////////////////////////////////////////////////////////////
	///
	/// @fn int obtenirNbObjetsSelectionne()
	///
	/// M�thode get pour l'attribut nbObjetsSelectionne_.
	///
	/// @return Nombre d'objets s�lectionn�s (attribut).
	///
	//////////////////////////////////////////////////////////////////////////
	int obtenirNbObjetsSelectionne() const { return nbObjetsSelectionne_; }

private:

	/// Constructeur par d�faut
	VisiteurSelectionMultiple();

	glm::dvec3 selectionBasGauche_; ///< Point cliqu� (bas gauche)
	glm::dvec3 selectionHautDroit_; ///< Point cliqu� (haut droit)

	int nbObjetsSelectionne_;		///< Nombre d'objets s�lectionn�s
};

#endif //__VISITEURS_VISITEURSELECTIONMULTIPLE_H__