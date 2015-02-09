///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurCentreDeMasse.h
/// @author The Ballers
/// @date 2015-02-01
/// @version 1.0
///
/// @ingroup Visiteur
///////////////////////////////////////////////////////////////////////////////
#ifndef __VISITEURS_VISITEURCENTREDEMASSE_H__
#define __VISITEURS_VISITEURCENTREDEMASSE_H__

#include "VisiteurAbstrait.h"
#include "../Arbre/ArbreRenduINF2990.h"
#include "../Arbre/Noeuds/NoeudTable.h"
#include "glm\glm.hpp"


///////////////////////////////////////////////////////////////////////////
/// @class VisiteurCentreDeMasse
/// @brief Utilis� pour calculer le centre de masse des noeuds s�lectionn�s
///
/// @author Philippe Carphin
/// @date 2015-02-02
/// @ingroup Visiteur
///////////////////////////////////////////////////////////////////////////
class VisiteurCentreDeMasse : public VisiteurAbstrait
{
public:

	/// Constructeur
	VisiteurCentreDeMasse();

	/// Destructeur
	~VisiteurCentreDeMasse();
	
	/// Traiter une op�ration sur l'arbre de rendu et ses enfants
	virtual bool traiter(ArbreRenduINF2990* arbre);
	virtual bool traiter(NoeudTable* table);
	virtual bool traiter(NoeudAbstrait* noeud);

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn glm::dvec3 obtenirCentreDeMasse()
	///
	/// Cette fonction retourne les coordonn�es du centre de masse 
	/// du noeud visit�.
	///
	/// @param[in] Aucun
	///
	/// @return Coordonn�es de centre de masse d'un noeud (dvec3)
	///
	////////////////////////////////////////////////////////////////////////
	glm::dvec3 obtenirCentreDeMasse()
	{
		return glm::dvec3{ centreDeMasse_.x / nbNoeuds_,
							centreDeMasse_.y / nbNoeuds_,
							centreDeMasse_.z / nbNoeuds_};
	}

private:
	
	glm::dvec3 centreDeMasse_; ///< Centre de masse d'un noeud
	int nbNoeuds_; ///< Nombre de noeuds
	
};


#endif //__VISITEURS_VISITEURCENTREDEMASSE_H__