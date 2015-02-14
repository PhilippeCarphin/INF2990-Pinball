///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurSelectionInverse.h
/// @author The Ballers
/// @date 2015-02-01
/// @version 1.0
///
/// @ingroup Visiteur
///////////////////////////////////////////////////////////////////////////////
#ifndef __VISITEURS_VISITEURSELECTIONINVERSE_H__
#define __VISITEURS_VISITEURSELECTIONINVERSE_H__

#include "NoeudAbstrait.h"
#include "NoeudComposite.h"
#include "VisiteurAbstrait.h"
#include "glm\glm.hpp"

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurSelectionInverse
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
class VisiteurSelectionInverse : public VisiteurAbstrait
{
public:

	/// Constructeur par d�faut : aucun d�placement
	VisiteurSelectionInverse(glm::dvec3 pointDansLeMonde, int valeurStencil);

	/// Destructeur
	~VisiteurSelectionInverse();

	/// Traiter une op�ration sur l'arbre de rendu et ses enfants
	virtual bool traiter(ArbreRenduINF2990* arbre);
	/// Traiter une op�ration sur l'arbre de rendu et ses enfants
	virtual bool traiter(NoeudAbstrait* noeud);
	/// Traiter une op�ration sur l'arbre de rendu et ses enfants
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
	int obtenirNbObjetsSelectionne() 
	{ return nbObjetsSelectionne_; }

private:

	/// Constructeur par d�faut
	VisiteurSelectionInverse();

	glm::dvec3 pointDansLeMonde_; ///< Point cliqu�

	int valeurStencil_; ///< Valeur du stencil
	int nbObjetsSelectionne_; ///< Nombre d'objets s�lectionn�s
};


#endif //__VISITEURS_VISITEURSELECTIONINVERSE_H__