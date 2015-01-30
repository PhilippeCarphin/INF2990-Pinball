#include "VisiteurAgrandissement.h"
#include "../Arbre/Noeuds/NoeudButoir.h"
#include "../Arbre/Noeuds/NoeudCible.h"
#include "../Arbre/Noeuds/NoeudGenerateurBille.h"
#include "../Arbre/Noeuds/NoeudMur.h"
#include "../Arbre/Noeuds/NoeudPalette.h"
#include "../Arbre/Noeuds/NoeudPortail.h"
#include "../Arbre/Noeuds/NoeudRessort.h"
#include "../Arbre/Noeuds/NoeudTrou.h"

VisiteurAgrandissement::VisiteurAgrandissement()
{
	// Aucun agrandissement par d�faut
	homothetie_[0] = 1.0;
	homothetie_[1] = 1.0;
	homothetie_[2] = 1.0;
}

VisiteurAgrandissement::VisiteurAgrandissement(glm::dvec3 homothethie)
{
	homothetie_ = homothethie;
}

VisiteurAgrandissement::~VisiteurAgrandissement()
{

}

bool VisiteurAgrandissement::traiter(NoeudAbstrait& noeud)
{
	noeud.assignerEchelle(homothetie_);
	return true;
}

bool VisiteurAgrandissement::traiter(NoeudButoir& noeud)
{
	noeud.assignerEchelle(homothetie_);
	return true;
}

bool VisiteurAgrandissement::traiter(NoeudCible& noeud)
{
	noeud.assignerEchelle(homothetie_);
	return true;
}

bool VisiteurAgrandissement::traiter(NoeudGenerateurBille& noeud)
{
	noeud.assignerEchelle(homothetie_);
	return true;
}

bool VisiteurAgrandissement::traiter(NoeudMur& noeud)
{
	noeud.assignerEchelle(homothetie_);
	return true;
}

bool VisiteurAgrandissement::traiter(NoeudPalette& noeud)
{
	noeud.assignerEchelle(homothetie_);
	return true;
}

bool VisiteurAgrandissement::traiter(NoeudPortail& noeud)
{
	noeud.assignerEchelle(homothetie_);
	return true;
}

bool VisiteurAgrandissement::traiter(NoeudRessort& noeud)
{
	noeud.assignerEchelle(homothetie_);;
	return true;
}

bool VisiteurAgrandissement::traiter(NoeudTrou& noeud)
{
	noeud.assignerEchelle(homothetie_);
	return true;
}

bool VisiteurAgrandissement::traiter(NoeudTable& noeud)
{
	return false;
}