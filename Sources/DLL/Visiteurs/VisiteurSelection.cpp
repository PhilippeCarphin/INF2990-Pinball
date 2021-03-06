////////////////////////////////////////////////
/// @file   VisiteurSelection.cpp
/// @author The Ballers
/// @date   2015-02-01
///
/// @ingroup Visiteur
////////////////////////////////////////////////
#include "VisiteurSelection.h"
#include "../Arbre/ArbreRenduINF2990.h"
#include "../Arbre/Noeuds/NoeudTable.h"
#include "../Arbre/Noeuds/NoeudPortail.h"
#include <iostream>


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSelection::VisiteurSelection()
///
/// Constructeur par defaut (vide).
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurSelection::VisiteurSelection()
{

}


//////////////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSelection::VisiteurSelection(glm::dvec3 pointDansLeMonde, int valeurStencil, bool gaucheEnfonce, bool sourisSurSelection)
///
/// Constructeur qui initialise les variables membres de la classe.
///
/// @param[in] pointDansLeMonde : Le vecteur de points
/// @param[in] valeurStencil : La valeur de la selection
/// @param[in] gaucheEnfonce : Click gauche
/// @param[in] sourisSurSelection : Souris a selectionner le bon item
///
/// @return Aucune (constructeur).
///
//////////////////////////////////////////////////////////////////////////////////
VisiteurSelection::VisiteurSelection(glm::dvec3 pointDansLeMonde, int valeurStencil, bool gaucheEnfonce, bool sourisSurSelection)
:nbObjetsSelectionne_{ 0 }
{
	pointDansLeMonde_ = pointDansLeMonde;
	valeurStencil_ = valeurStencil;
	gaucheEnfonce_ = gaucheEnfonce;
	sourisSurSelection_ = sourisSurSelection;
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
VisiteurSelection::~VisiteurSelection()
{

}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurSelection::traiter(ArbreRenduINF2990* arbre)
/// @brief Cette fonction traite l'arbre de rendu pour visiter ses enfants.
///
/// Cette fonction retourne true pour dire que l'operation s'est
/// fait correctement.
///
/// @param[in] arbre : L'arbre de rendu a traiter.
///
/// @return Retourne toujours true.
///
////////////////////////////////////////////////////////////////////////
bool VisiteurSelection::traiter(ArbreRenduINF2990* arbre)
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
/// Cette fonction retourne true pour dire que l'operation s'est
/// fait correctement.
///
/// @param[in] table : Le noeud de type Table a traiter.
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool VisiteurSelection::traiter(NoeudTable* table)
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
/// Cette fonction retourne true pour dire que l'operation s'est
/// faite correctement.
///
/// @param[in] noeud : Noeud de l'arbre a traiter.
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool VisiteurSelection::traiter(NoeudAbstrait* noeud)
{
	// Merci de laisser le cout pour que je puisse le decommenter au besoin
	//std::cout << "Visite d'un noeud de type " << noeud->getType()
		//<< " avec numero " << noeud->getNumero() << std::endl;
	if (valeurStencil_ == noeud->getNumero() && noeud->estSelectionnable())
		noeud->assignerSelection(true);
	else if (!sourisSurSelection_ || gaucheEnfonce_ == false)
		noeud->assignerSelection(false);

	if (noeud->estSelectionne()) 
		nbObjetsSelectionne_++;

	// Utilise par Phil pour faire des boites englobantes custom
	/*
	if (noeud->obtenirType() == "butoirg")
		{
			glm::dvec3 vecteur = pointDansLeMonde_ - noeud->obtenirPositionRelative();
			std::cout << "{ " << vecteur.x << " , " << vecteur.y << " , 0.0 }," << std::endl;
		}
	*/
	return true;
}


bool VisiteurSelection::traiter(NoeudPortail* noeud)
{
	// Merci de laisser le cout pour que je puisse le decommenter au besoin
	//std::cout << "Visite d'un noeudPortail de type " << noeud->getType()
		//<< " avec numero " << noeud->getNumero() << std::endl;
	// Stencil - 1 si le tore etait dessine
	if (valeurStencil_ == noeud->getNumero() && noeud->estSelectionnable())
		noeud->assignerSelection(true);
	else if (!sourisSurSelection_)
		noeud->assignerSelection(false);

	if (noeud->estSelectionne())
		nbObjetsSelectionne_++;

	return true;
}
