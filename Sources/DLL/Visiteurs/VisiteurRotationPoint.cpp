////////////////////////////////////////////////
/// @file   VisiteurRotationPoint.cpp
/// @author Yonni Chen
/// @date   2015-02-01
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////

#include "VisiteurRotationPoint.h"
#include "../Arbre/ArbreRenduINF2990.h"
#include <iostream>


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurRotationPoint::VisiteurRotationPoint()
///
/// VIDE
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurRotationPoint::VisiteurRotationPoint()
{

}


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurRotationPoint::VisiteurRotationPoint(glm::dvec3 dep)
///
/// Ne fait qu'initialiser les variables membres de la classe.
///
/// @param[in] dev : Le vecteur de rotation
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurRotationPoint::VisiteurRotationPoint(glm::dvec3 angles, glm::dvec3 centreRotation)
:centreRotation_{ centreRotation }
{
	angles_ = angles;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurRotationPoint::~VisiteurRotationPoint()
///
/// Destructeur vide 
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurRotationPoint::~VisiteurRotationPoint()
{

}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurRotationPoint::traiter(ArbreRenduINF2990* noeud)
///
/// Cette fonction traite l'arbre de rendu pour effectuer une rotation sur ses enfants
/// selectionn�s
///
/// Cette fonction retourne true pour dire que l'op�ration s'est
/// fait correctement
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool VisiteurRotationPoint::traiter(ArbreRenduINF2990* noeud)
{
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++)
	{
		traiter(noeud->getEnfant(i));
	}

	return true;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurRotationPoint::traiter(NoeudAbstrait* noeud)
///
/// Cette fonction traite les enfants de l'arbre de rendu. Si ses enfants ont des enfants
/// ils seront aussi trait�s.
///
/// Cette fonction retourne true pour dire que l'op�ration s'est
/// fait correctement
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool VisiteurRotationPoint::traiter(NoeudAbstrait* noeud)
{
	// Connaitre le type du noeud
	std::string nom = noeud->obtenirType();

	// Si l'�l�ment est une table, visiter ses enfants
	if (nom == "table")
	{
		// Traiter les enfants selectionn�s de la table
		for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++)
		{
			if (noeud->chercher(i)->estSelectionne())
				traiter(noeud->chercher(i));
		}
	}

	else
	{
		if (noeud->estSelectionne())
		{
			// LOGIQUE DE ROTATION AUTOUR D'UN POINT
			// Changer la position du noeud
			glm::dvec3 positionInitiale = noeud->obtenirPositionRelative();
			glm::dvec3 vecteurInitial = positionInitiale - centreRotation_;
			// std::cout << "VecteurInitial: " << vecteurInitial.x << ", " << vecteurInitial.y << std::endl;
			double angleEnRadian = -angles_[2] * 2 * 3.14156 / 360;
			glm::dmat3 transform = glm::dmat3{ glm::dvec3{ cos(angleEnRadian), -sin(angleEnRadian), 0.0 },
												glm::dvec3{ sin(angleEnRadian), cos(angleEnRadian), 0.0f },
												glm::dvec3{       0.0      ,       0.0        , 1.0 } };

			glm::dvec3 vecteurFinal = transform * vecteurInitial;
			// std::cout << "VecteurFinal: " << vecteurFinal.x << ", " << vecteurFinal.y << std::endl;
			glm::dvec3 positionFinale = centreRotation_ + vecteurFinal;

			noeud->assignerPositionRelative(positionFinale);

			// Changer l'orientation du noeud
			noeud->assignerRotation(angles_);
		}
	}

	return true;
}