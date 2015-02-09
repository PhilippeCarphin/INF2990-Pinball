///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurDeplacement.h
/// @author The Ballers
/// @date 2015-02-01
/// @version 1.0
///
/// @ingroup Visiteur
///////////////////////////////////////////////////////////////////////////////
#ifndef __VISITEURS_VISITEURDEPLACEMENT_H__
#define __VISITEURS_VISITEURDEPLACEMENT_H__

#include "VisiteurAbstrait.h"
#include "glm\glm.hpp"

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurDeplacement
/// @brief Classe pour deplacer les objets selectionn�s de l'arbre de rendu
///
///        Instancier cette classe avec en param�tre le vecteur de 
///		   d�placement. Ensuite, appeler la m�thode accepterVisiteur()
///		   de l'arbre de rendu et lui fournir CE visiteur en param�tre
///
/// @author Yonni Chen
/// @date 2015-02-02
/// @ingroup Visiteur
///////////////////////////////////////////////////////////////////////////
class VisiteurDeplacement : public VisiteurAbstrait
{
public:

	/// Constructeur par param�tre : sp�cifiez un vecteur de d�placement
	VisiteurDeplacement(glm::dvec3 dep);

	/// Destructeur
	~VisiteurDeplacement();

	/// M�thode d'acces
	glm::dvec3 getDeplacement() { return deplacement_; };

	/// M�thode de modifications
	void setDeplacement(glm::dvec3 dep) { deplacement_ = dep; };

	/// Traiter une op�ration sur l'arbre de rendu et ses enfants
	virtual bool traiter(ArbreRenduINF2990* arbre);
	/// Traiter une op�ration sur l'arbre de rendu et ses enfants
	virtual bool traiter(NoeudAbstrait* noeud);

private:

	/// Constructeur par d�faut
	VisiteurDeplacement();

	glm::dvec3 deplacement_; ///< Vecteur de d�placement

};


#endif //__VISITEURS_VISITEURDEPLACEMENT_H__