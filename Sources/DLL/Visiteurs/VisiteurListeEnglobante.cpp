////////////////////////////////////////////////
/// @file   VisiteurSelection.cpp
/// @author The Ballers
/// @date   2015-02-01
///
/// @ingroup Visiteur
////////////////////////////////////////////////
#include "VisiteurListeEnglobante.h"
#include "../Arbre/ArbreRenduINF2990.h"
#include "../Arbre/Noeuds/NoeudTable.h"
#include <iostream>

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSelection::VisiteurSelection()
///
/// Constructeur par d�faut (vide).
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurListeEnglobante::VisiteurListeEnglobante()
{

}


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSelection::~VisiteurSelection()
///
/// Destructeur vide 
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurListeEnglobante::~VisiteurListeEnglobante()
{

}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurSelection::traiter(ArbreRenduINF2990* arbre)
/// @brief Cette fonction traite l'arbre de rendu pour visiter ses enfants.
///
/// Cette fonction retourne true pour dire que l'op�ration s'est
/// fait correctement.
///
/// @param[in] arbre : L'arbre de rendu � traiter.
///
/// @return Retourne toujours true.
///
////////////////////////////////////////////////////////////////////////
bool VisiteurListeEnglobante::traiter(ArbreRenduINF2990* arbre)
{
	for (unsigned int i = 0; i < arbre->obtenirNombreEnfants(); i++)
	{
		arbre->getEnfant(i)->accepterVisiteur(this);
	}
	return true;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurSelection::traiter(NoeudTable* table)
/// @brief Cette fonction traite la table de l'arbre de rendu.
///
/// Cette fonction retourne true pour dire que l'op�ration s'est
/// fait correctement.
///
/// @param[in] table : Le noeud de type Table � traiter.
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool VisiteurListeEnglobante::traiter(NoeudTable* table)
{
	for (unsigned int i = 0; i < table->obtenirNombreEnfants(); i++)
	{
		table->getEnfant(i)->accepterVisiteur(this);
	}
	return true;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurSelection::traiter(NoeudAbstrait* noeud)
/// @brief Cette fonction traite les enfants de l'arbre de rendu. 
///
/// Cette fonction retourne true pour dire que l'op�ration s'est
/// faite correctement.
///
/// @param[in] noeud : Noeud de l'arbre � traiter.
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool VisiteurListeEnglobante::traiter(NoeudAbstrait* noeud)
{
	if (noeud->estSelectionne())
	{
		glm::dvec3 coinsEnglobant[4];
		noeud->obtenirVecteursBoite(coinsEnglobant[0], coinsEnglobant[1], coinsEnglobant[2], coinsEnglobant[3]);
		conteneur_boite_englobante boite;
		
		for (int i = 0; i < 4; i++)
		{
			boite.first.push_back(coinsEnglobant[i]);
		}
		boite.second = noeud;

		boitesEnglobantes_.push_back(boite);
	}
	return true;
}

