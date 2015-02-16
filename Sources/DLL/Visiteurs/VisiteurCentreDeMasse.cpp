////////////////////////////////////////////////
/// @file   VisiteurCentreDeMasse.cpp
/// @author The Ballers
/// @date   2015-02-01
///
/// @ingroup Visiteur
////////////////////////////////////////////////

#include "VisiteurCentreDeMasse.h"
#include "../Arbre/ArbreRenduINF2990.h"
#include "../Arbre/Noeuds/NoeudTable.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurCentreDeMasse::VisiteurCentreDeMasse()
///
/// Constructeur.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurCentreDeMasse::VisiteurCentreDeMasse()
:centreDeMasse_{ 0, 0, 0 },
nbNoeuds_{ 0 }
{

}


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurCentreDeMasse::~VisiteurCentreDeMasse()
///
/// Destructeur vide.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurCentreDeMasse::~VisiteurCentreDeMasse()
{

}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurCentreDeMasse::traiter(ArbreRenduINF2990* arbre)
///
/// Cette fonction traite l'arbre de rendu pour calculer le centre de masse
/// des objets selectionn�s. Cette fonction retourne true pour dire que 
/// l'op�ration s'est faite correctement.
///
/// @param[in] arbre : L'arbre de rendu � traiter.
///
/// @return Retourne toujours true.
///
////////////////////////////////////////////////////////////////////////
bool VisiteurCentreDeMasse::traiter(ArbreRenduINF2990* arbre)
{
	for (unsigned int i = 0; i < arbre->obtenirNombreEnfants(); i++)
	{
		arbre->getEnfant(i)->accepterVisiteur(this);
	}

	return true;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurCentreDeMasse::traiter(NoeudTable* table)
///
/// Cette fonction traite la table de l'arbre de rendu et ses enfants pour
/// le calcul du centre de masse. Cette fonction retourne true pour dire 
///	que l'op�ration s'est faite correctement.
///
/// @param[in] table : La table � traiter.
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool VisiteurCentreDeMasse::traiter(NoeudTable* table)
{
	for (unsigned int i = 0; i < table->obtenirNombreEnfants(); i++)
	{
		table->getEnfant(i)->accepterVisiteur(this);
	}
	return true;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurCentreDeMasse::traiter(NoeudAbstrait* noeud)
/// 
///	Calcule le centre de masse (tous les noeuds ont une masse de 1).
/// Cette fonction retourne true pour dire que l'op�ration s'est
/// faite correctement.
///
/// @param[in] noeud : noeud � traiter.
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool VisiteurCentreDeMasse::traiter(NoeudAbstrait* noeud)
{
	if (noeud->estSelectionne())
	{
		centreDeMasse_ += noeud->obtenirPositionRelative();
		nbNoeuds_++;
	}

	return true;
}


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
glm::dvec3 VisiteurCentreDeMasse::obtenirCentreDeMasse() const
{
	return glm::dvec3{ centreDeMasse_.x / nbNoeuds_,
		centreDeMasse_.y / nbNoeuds_,
		centreDeMasse_.z / nbNoeuds_ };
}