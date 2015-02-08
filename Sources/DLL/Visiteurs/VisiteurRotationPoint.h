///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurRotation.h
/// @author The Ballers
/// @date 2015-02-01
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#ifndef __VISITEURS_VISITEURROTATIONPOINT_H__
#define __VISITEURS_VISITEURROTATIONPOINT_H__

#include "VisiteurAbstrait.h"
#include "glm\glm.hpp"


///////////////////////////////////////////////////////////////////////////
/// @class VisiteurRotation
/// @brief Classe pour effectuer une rotation sur des objets seletionn�s de
///		   l'arbre de rendu.
///
///        Instancier cette classe avec en param�tre les angles de rotation.
///		   Ensuite, appelez la m�thode accepterVisiteur() de l'arbre de rendu 
///		   et lui fournir CE visiteur en param�tre.
///
/// @author Yonni Chen
/// @date 2015-02-02
///////////////////////////////////////////////////////////////////////////
class VisiteurRotationPoint : public VisiteurAbstrait
{
public:

	// Constructeur par param�tre : sp�cifiez l'angle, l'axe et le sens
	VisiteurRotationPoint(glm::dvec3 angles ,glm::dvec3 centreRotation);

	// Destructeur
	~VisiteurRotationPoint();

	// M�thode d'acc�s
	glm::dvec3 getRotation() { return angles_; };

	// M�thode de modifications
	void setRotation(glm::dvec3 dep) { angles_ = dep; };

	// Traiter une op�ration sur l'arbre de rendu et ses enfants
	virtual bool traiter(ArbreRenduINF2990* arbre);
	virtual bool traiter(NoeudAbstrait* noeud);
	virtual bool traiter(NoeudTable* noeud);

private:

	// Ne touchez pas au constructeur par d�faut
	VisiteurRotationPoint();

	// Angles de rotation en x, y et z
	glm::dvec3 angles_;

	glm::dvec3 centreRotation_;

};


#endif //__VISITEURS_VISITEURROTATIONPOINT_H__