////////////////////////////////////////////////
/// @file   VisiteurDeselectionnerTout.cpp
/// @author The Ballers
/// @date   2015-02-01
///
/// @ingroup Visiteur
////////////////////////////////////////////////
#include "VisiteurDeselectionnerTout.h"
#include "../Arbre/ArbreRenduINF2990.h"
#include "../Arbre/Noeuds/NoeudTable.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDeselectionnerTout::VisiteurDeselectionnerTout()
///
/// Constructeur par d�faut (vide).
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurDeselectionnerTout::VisiteurDeselectionnerTout()
{

}


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDeselectionnerTout::~VisiteurDeselectionnerTout()
///
/// Destructeur vide.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurDeselectionnerTout::~VisiteurDeselectionnerTout()
{

}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurDeselectionnerTout::traiter(ArbreRenduINF2990* arbre)
/// @brief Cette fonction traite l'arbre de rendu pour visiter ses enfants.
///
/// Cette fonction retourne true pour dire que l'op�ration s'est
/// faite correctement.
///
/// @param[in] arbre : L'arbre de rendu � traiter.
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool VisiteurDeselectionnerTout::traiter(ArbreRenduINF2990* arbre)
{
	for (unsigned int i = 0; i < arbre->obtenirNombreEnfants(); i++)
	{
		arbre->getEnfant(i)->accepterVisiteur(this);
	}

	return true;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurDeselectionnerTout::traiter(NoeudTable* table)
/// @brief Cette fonction traite la table de l'arbre de rendu.
///
/// Cette fonction retourne true pour dire que l'op�ration s'est
/// faite correctement.
///
/// @param[in] table : Le noeud de type Table � traiter.
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool VisiteurDeselectionnerTout::traiter(NoeudTable* table)
{
	for (unsigned int i = 0; i < table->obtenirNombreEnfants(); i++)
	{
		table->getEnfant(i)->accepterVisiteur(this);
	}
	return true;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurDeselectionnerTout::traiter(NoeudAbstrait* noeud)
///
/// Ce visiteur d�s�lectionne un noeud.
///
/// @param[in] noeud : Noeud de l'arbre � traiter.
///
/// @return Retourne toujours true.
///
////////////////////////////////////////////////////////////////////////
bool VisiteurDeselectionnerTout::traiter(NoeudAbstrait* noeud)
{
	noeud->assignerSelection(false);
	return true;
}