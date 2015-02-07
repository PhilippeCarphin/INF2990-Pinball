////////////////////////////////////////////////
/// @file   VisiteurDuplication.cpp
/// @author The Ballers
/// @date   2015-02-01
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////
#include "VisiteurDuplication.h"
#include "../Arbre/ArbreRenduINF2990.h"
#include "../Arbre/Noeuds/NoeudTable.h"
#include <iostream>

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDuplication::VisiteurDuplication()
///
/// VIDE
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurDuplication::VisiteurDuplication()
{

}


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDuplication::VisiteurDuplication(glm::dvec3 pointDansLeMonde)
///
/// Ne fait qu'initialiser les variables membres de la classe.
///
/// @param[in] pointDansLeMonde : Le point ou il y a eu le clic
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurDuplication::VisiteurDuplication(glm::dvec3 pointDansLeMonde)
{
	pointDansLeMonde_ = pointDansLeMonde;
	maxX = maxY = 0;
	minX = minY = std::numeric_limits<int>::max();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDuplication::~VisiteurDuplication()
///
/// Destructeur vide 
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurDuplication::~VisiteurDuplication()
{
	for (unsigned int i = 0; i < copies_.size(); i++)
		delete copies_[i];

	copies_.clear();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurDuplication::traiter(ArbreRenduINF2990* noeud)
///
/// Cette fonction traite l'arbre de rendu pour dupliquer ses enfants selectionn�s
///
/// Cette fonction retourne true pour dire que l'op�ration s'est
/// fait correctement
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool VisiteurDuplication::traiter(ArbreRenduINF2990* arbre)
{
	// Visiter les enfants de l'arbre
	for (unsigned int i = 0; i < arbre->obtenirNombreEnfants(); i++)
	{
		// Traiter les enfants de l'arbre de rendu
		arbre->getEnfant(i)->accepterVisiteur(this);
	}

	return true;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurDuplication::traiter(NoeudTable* table)
///
/// Cette fonction traite la table de l'arbre de rendu.
///
/// Cette fonction retourne true pour dire que l'op�ration s'est
/// fait correctement
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool VisiteurDuplication::traiter(NoeudTable* table)
{
	// Traiter les enfants selectionn�s de la table
	for (unsigned int i = 0; i < table->obtenirNombreEnfants(); i++)
	{
		// Effectuer une copie des enfants selectionn�s et les ajouter � la structure de donn�e
		table->getEnfant(i)->accepterVisiteur(this);
	}

	// Si la structure ne contient qu'un seul objet
	if (copies_.size() == 1)
	{
		copies_[0]->assignerPositionRelative(pointDansLeMonde_);
	}

	// Si la structure contient plusieurs objets, trouver le centre de selection
	else if (copies_.size() > 1)
	{
		double centreX = (maxX - minX) / 2.0;
		double centreY = (maxY - minY) / 2.0;
	}



	return true;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurDuplication::traiter(NoeudAbstrait* noeud)
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
bool VisiteurDuplication::traiter(NoeudAbstrait* noeud)
{
	if (noeud->estSelectionne())
	{
		NoeudAbstrait* copie = new NoeudAbstrait();
		copie->assignerRotation(noeud->obtenirRotation());
		copie->assignerEchelle(noeud->obtenirAgrandissement());
		copie->assignerPositionRelative(noeud->obtenirPositionRelative());

		if (maxX < noeud->obtenirPositionRelative().x)
			maxX = noeud->obtenirPositionRelative().x;

		if (minX > noeud->obtenirPositionRelative().x)
			minX = noeud->obtenirPositionRelative().x;

		if (maxY < noeud->obtenirPositionRelative().y)
			maxY = noeud->obtenirPositionRelative().y;

		if (minY > noeud->obtenirPositionRelative().y)
			minY = noeud->obtenirPositionRelative().y;

		copies_.push_back(copie);
	}

	return true;

}