////////////////////////////////////////////////
/// @file   VisiteurSelectionInverse.cpp
/// @author The Ballers
/// @date   2015-02-01
///
/// @ingroup Visiteur
////////////////////////////////////////////////
#include "VisiteurSelectionInverse.h"
#include "../Arbre/ArbreRenduINF2990.h"
#include "../Arbre/Noeuds/NoeudTable.h"
#include "../Arbre/Noeuds/NoeudPortail.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSelectionInverse::VisiteurSelectionInverse()
///
/// Constructeur par defaut (vide).
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurSelectionInverse::VisiteurSelectionInverse()
{

}


//////////////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSelectionInverse::VisiteurSelectionInverse(glm::dvec3 pointDansLeMonde, int valeurStencil, bool gaucheEnfonce, bool sourisSurSelection)
///
/// Constructeur qui initialise les variables membres de la classe.
///
/// @param[in] pointDansLeMonde : Le point de l'espace
/// @param[in] valeurStencil : La valeur du stencil
/// @param[in] gaucheEnfonce : Click gauche
/// @param[in] sourisSurSelection : Souris a selectionner le bon item
///
/// @return Aucune (constructeur).
///
//////////////////////////////////////////////////////////////////////////////////
VisiteurSelectionInverse::VisiteurSelectionInverse(glm::dvec3 pointDansLeMonde, int valeurStencil, bool gaucheEnfonce, bool sourisSurSelection)
:nbObjetsSelectionne_{ 0 }
{
	pointDansLeMonde_ = pointDansLeMonde;
	valeurStencil_ = valeurStencil;
	gaucheEnfonce_ = gaucheEnfonce;
	sourisSurSelection_ = sourisSurSelection;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSelectionInverse::~VisiteurSelectionInverse()
///
/// Destructeur vide 
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurSelectionInverse::~VisiteurSelectionInverse()
{

}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurSelectionInverse::traiter(ArbreRenduINF2990* arbre)
/// @brief Cette fonction traite l'arbre de rendu pour selectionner ses enfants.
///
/// Cette fonction retourne true pour dire que l'operation s'est
/// fait correctement.
///
/// @param[in] arbre : L'arbre de rendu a traiter.
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool VisiteurSelectionInverse::traiter(ArbreRenduINF2990* arbre)
{
	// Traiter les enfants de l'arbre de rendu
	for (unsigned int i = 0; i < arbre->obtenirNombreEnfants(); i++)
	{
		arbre->getEnfant(i)->accepterVisiteur(this);
	}

	return true;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurSelectionInverse::traiter(NoeudTable* table)
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
bool VisiteurSelectionInverse::traiter(NoeudTable* table)
{
	// Traiter les enfants selectionnes de la table
	for (unsigned int i = 0; i < table->obtenirNombreEnfants(); i++)
	{
		table->getEnfant(i)->accepterVisiteur(this);
	}

	return true;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurSelectionInverse::traiter(NoeudAbstrait* noeud)
///
/// Cette fonction traite un noeud de l'arbre de rendu. Si ses enfants ont 
/// des enfants ils seront aussi traites. Cette fonction retourne true pour dire que 
/// l'operation s'est faite correctement.
///
/// @param[in] noeud : Noeud de l'arbre a traiter.
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool VisiteurSelectionInverse::traiter(NoeudAbstrait* noeud)
{
	if (!gaucheEnfonce_ && valeurStencil_ == noeud->getNumero() && noeud->estSelectionnable() /*&& noeud->estModifiable()*/)
	{
		if (noeud->estSelectionne())
			noeud->assignerSelection(false);
		else
			noeud->assignerSelection(true);
	}

	if (noeud->estSelectionne())
		nbObjetsSelectionne_++;

	return true;
}

bool VisiteurSelectionInverse::traiter(NoeudPortail* noeud)
{
	// Stencil -1 si le tore etait dessine 
	if (!gaucheEnfonce_ && valeurStencil_ == noeud->getNumero() && noeud->estSelectionnable() /*&& noeud->estModifiable()*/)
	{

		if (noeud->estSelectionne())
			noeud->assignerSelection(false);

		else
			noeud->assignerSelection(true);
	}

	if (noeud->estSelectionne())
		nbObjetsSelectionne_++;

	return true;

}