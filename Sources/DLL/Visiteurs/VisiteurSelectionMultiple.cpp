////////////////////////////////////////////////
/// @file   VisiteurSelection.cpp
/// @author The Ballers
/// @date   2015-02-01
///
/// @ingroup Visiteur
////////////////////////////////////////////////
#include "VisiteurSelectionMultiple.h"
#include "../Arbre/ArbreRenduINF2990.h"
#include "../Arbre/Noeuds/NoeudTable.h"
#include <iostream>
#include "Utilitaire.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSelection::VisiteurSelection()
///
/// Constructeur par d�faut (vide).
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurSelectionMultiple::VisiteurSelectionMultiple()
{

}


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSelectionMultiple::VisiteurSelectionMultiple(glm::dvec3 selectionBasGauche, glm::dvec3 selectionHautDroit)
///
/// Constructeur qui initialise les variables membres de la classe.
///
/// @param[in] selectionBasGauche : Le vecteur de s�lection
/// @param[in] selectionHautDroit : Le vecteur de s�lection
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurSelectionMultiple::VisiteurSelectionMultiple(glm::dvec3 selectionBasGauche, glm::dvec3 selectionHautDroit)
:nbObjetsSelectionne_{ 0 }
{
	selectionBasGauche_ = selectionBasGauche;
	selectionHautDroit_ = selectionHautDroit;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSelection::~VisiteurSelection()
///
/// Destructeur vide.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurSelectionMultiple::~VisiteurSelectionMultiple()
{

}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurSelectionMultiple::traiter(ArbreRenduINF2990* arbre)
/// @brief Cette fonction traite l'arbre de rendu pour selectionner ses enfants.
///
/// Cette fonction retourne true pour dire que l'op�ration s'est
/// fait correctement.
///
/// @return Retourne toujours true.
///
////////////////////////////////////////////////////////////////////////
bool VisiteurSelectionMultiple::traiter(ArbreRenduINF2990* arbre)
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
/// @fn bool VisiteurSelectionMultiple::traiter(NoeudTable* table)
/// @brief Cette fonction traite la table de l'arbre de rendu.
///
/// Cette fonction retourne true pour dire que l'op�ration s'est
/// fait correctement.
///
/// @param[in] table : Le noeud de type Table � traiter.
///
/// @return Retourne toujours true.
///
////////////////////////////////////////////////////////////////////////
bool VisiteurSelectionMultiple::traiter(NoeudTable* table)
{;
	// Traiter les enfants selectionn�s de la table
	for (unsigned int i = 0; i < table->obtenirNombreEnfants(); i++)
	{
		table->getEnfant(i)->accepterVisiteur(this);
	}

	return true;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurSelectionMultiple::traiter(NoeudAbstrait* noeud)
///
///	Cette fonction traite les enfants de l'arbre de rendu. Si ses enfants 
/// ont des enfants, ils seront aussi trait�s. Cette fonction retourne true 
/// si l'op�ration s'est faite correctement.
///
/// @param[in] noeud : Noeud de l'arbre � traiter.
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool VisiteurSelectionMultiple::traiter(NoeudAbstrait* noeud)
{
	glm::dvec3 origine = noeud->obtenirPositionRelative();

	utilitaire::BoiteEnglobante boite = utilitaire::calculerBoiteEnglobante(*noeud->obtenirModele());

	std::cout << selectionBasGauche_.x << " " << selectionBasGauche_.y << " " << selectionHautDroit_.x << " " << selectionHautDroit_.y << std::endl;

	if ((utilitaire::DANS_LIMITESXY(boite.coinMin.x + origine.x, selectionBasGauche_.x, selectionHautDroit_.x,
		                           boite.coinMin.y + origine.y, selectionBasGauche_.y, selectionHautDroit_.y) ||
		utilitaire::DANS_LIMITESXY(boite.coinMax.x + origine.x, selectionBasGauche_.x, selectionHautDroit_.x,
		                           boite.coinMin.y + origine.y, selectionBasGauche_.y, selectionHautDroit_.y) ||
		utilitaire::DANS_LIMITESXY(boite.coinMin.x + origine.x, selectionBasGauche_.x, selectionHautDroit_.x,
								   boite.coinMax.y + origine.y, selectionBasGauche_.y, selectionHautDroit_.y) ||
		utilitaire::DANS_LIMITESXY(boite.coinMax.x + origine.x, selectionBasGauche_.x, selectionHautDroit_.x,
								   boite.coinMax.y + origine.y, selectionBasGauche_.y, selectionHautDroit_.y)) &&
		noeud->estSelectionnable())
	{
		std::cout << "Noeud de type " << noeud->getType() << " selectionne " << std::endl;
		noeud->assignerSelection(true);
	}
	else
	{
		noeud->assignerSelection(false);
	}

	if (noeud->estSelectionne())
	{
		nbObjetsSelectionne_++;
	}

	return true;
}