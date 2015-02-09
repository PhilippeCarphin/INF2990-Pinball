///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurAgrandissement.h
/// @author The Ballers
/// @date 2015-02-01
/// @version 1.0
///
/// @ingroup Visiteur
///////////////////////////////////////////////////////////////////////////////
#ifndef __VISITEURS_VISITEURAGRANDISSEMENT_H__
#define __VISITEURS_VISITEURAGRANDISSEMENT_H__

#include "VisiteurAbstrait.h"
#include "glm\glm.hpp"

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurAgrandissement
/// @brief Classe pour agrandir ou r�tr�cir des objets seletionn�s de
///		   l'arbre de rendu.
///
///        Instancier cette classe avec en param�tre le facteur d'agrandissement
///		   en x, y et z. Ensuite, appeler la m�thode accepterVisiteur()
///		   de l'arbre de rendu et lui fournir CE visiteur en param�tre
///
/// @author Yonni Chen
/// @date 2015-02-02
/// @ingroup Visiteur
///////////////////////////////////////////////////////////////////////////
class VisiteurAgrandissement : public VisiteurAbstrait
{
public:
	
	/// Constructeur par param�tre
	VisiteurAgrandissement(glm::dvec3 homothetie);

	/// Destructeur
	~VisiteurAgrandissement();

	/// M�thode d'acc�s
	glm::dvec3 getAgrandissement() { return homothetie_; };

	/// M�thode de modifications
	void setAgrandissement(glm::dvec3 homothetie) { homothetie_ = homothetie; };

	/// Traiter une op�ration sur l'arbre de rendu et ses enfants
	virtual bool traiter(ArbreRenduINF2990* arbre);
	/// Traiter une op�ration sur l'arbre de rendu et ses enfants
	virtual bool traiter(NoeudTable* noeud);
	/// Traiter une op�ration sur l'arbre de rendu et ses enfants
	virtual bool traiter(NoeudAbstrait* noeud);

private:

	/// Constructeur par d�faut
	VisiteurAgrandissement();

	glm::dvec3 homothetie_; ///< Facteur d'agrandissement en x, y et z

};

#endif //__VISITEURS_VISITEURAGRANDISSEMENT_H__