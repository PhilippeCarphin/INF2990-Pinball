///////////////////////////////////////////////////////////////////////////
/// @file NoeudPortail.cpp
/// @author The Ballers
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////

#include "NoeudPortail.h"
#include "NoeudPortailTorus.h"
#include "Utilitaire.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_Storage/ModeleStorage_Liste.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudPortail::NoeudPortail(const std::string& typeNoeud)
///
/// @param[in] typeNoeud :  le type du noeud a creer.
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par defaut aux variables membres.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudPortail::NoeudPortail(const std::string& typeNoeud)
	: NoeudComposite{ typeNoeud }
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudPortail::~NoeudPortail()
///
/// Ce destructeur desallouee la liste d'affichage du noeud.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudPortail::~NoeudPortail()
{
	twin_ = nullptr;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudPortail::afficherConcret() const
///
/// Cette fonction effectue le veritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudPortail::afficherConcret() const
{
	NoeudComposite::afficherConcret();
	// Sauvegarde de la matrice.
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	NoeudAbstrait::appliquerAfficher();
	liste_->dessiner();
	glPopAttrib();
	glPopMatrix();
	// Restauration de la matrice.
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudPortail::animer(float temps)
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps. Pas d'animation pour ce type de noeud.
///
/// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudPortail::animer(float temps)
{
	NoeudComposite::animer(temps);

	if (enfants_.size() == 0)
		return;

	enfants_[0]->assignerAffiche(debug_);
	enfants_[0]->setTransparent(transparent_);
	enfants_[0]->assignerSelection(selectionne_);

	if (!animer_)
		return;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudPortail::accepterVisiteur(VisiteurAbstrait* vis)
///
/// @brief Cette fonction appelle la methode traiter du visiteur.
///
/// @param[in] vis Pointeur sur le visiteur a accepter
///
/// @return reussi (TRUE)
///
////////////////////////////////////////////////////////////////////////
bool NoeudPortail::accepterVisiteur(VisiteurAbstrait* vis)
{
	bool reussi = false;

	if (vis->traiter(this))
		reussi = true;

	return reussi;

}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudPortail::setDebug(bool debug)
///
/// @brief Cette fonction change al valeur du mode debug
///
/// @param[in] debug Valeur a assigner
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void NoeudPortail::setDebug(bool debug)
{
	debug_ = debug;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn std::vector<glm::dvec3> NoeudPortail::obtenirVecteursEnglobants()
///
/// La boite englobante d'un butoir circulaire, c'est un rayon.
/// Pour etre conforme avec les boites englobantes des autres noeuds, 
/// on retourne quand meme un vector<glm::dvec3> mais avec un seul element
/// dont le x contient le rayon.
///
/// @return Un vecteur<glm::dvec3> dont le seul element a le rayon de l'objet
/// comme premiere coordonnee.
/// 
////////////////////////////////////////////////////////////////////////
std::vector<glm::dvec3> NoeudPortail::obtenirVecteursEnglobants()
{
	double rayonModele = abs(boite_.coinMin.y);
	return{ glm::dvec3{ rayonModele * scale_.x, 0, 0 } };
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudPortail::traiterCollisions(aidecollision::DetailsCollision, NoeudAbstrait* bille, float)
///
/// @brief Cette fonction effectue la reaction a la collision de la bille sur 
/// l'objet un portail.  C'est a dire de teleporter la bille au jumeau
/// de l'objet courant.  De plus, la bille va se rappeler du portail d'ou
/// elle est sortie pour ne pas rester pris dedans.
/// 
/// @param[in] bille Objet modifie par la collision
/// @param[in] facteurRebond Valeur du facteur de rebondissement
/// 
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void NoeudPortail::traiterCollisions(aidecollision::DetailsCollision, NoeudAbstrait* bille, float)
{
	if (bille->obtenirPortailDorigine() != this)
	{
		SoundControl->jouerSon("portal");
		bille->assignerPositionRelative(this->getTwin()->obtenirPositionRelative());
		bille->assignerPortailDorigine(this->getTwin());
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn aidecollision::DetailsCollision NoeudPortail::detecterCollisions(NoeudAbstrait* bille)
///
/// @brief Reimplementation de detecterCollisions pour un objet circulaire.  De plus,
/// pour le portail, on utilise rayonPortail/4 plutot que le rayonPortail parce
/// qu'on veut que la bille soit plus proche du centre pour etre teleportee
/// 
/// @param[in] bille Objet avec le noeud se compare pour trouver une collision.
/// 
/// @return details contient l'information sur la collision de la bille avec *this.
/// 
////////////////////////////////////////////////////////////////////////
aidecollision::DetailsCollision NoeudPortail::detecterCollisions(NoeudAbstrait* bille)
{
	double rayonPortail = obtenirVecteursEnglobants()[0].x;
	double rayonBille = bille->obtenirVecteursEnglobants()[0].x;
	aidecollision::DetailsCollision details = aidecollision::calculerCollisionCercle((glm::dvec2)obtenirPositionRelative(), rayonPortail/4, (glm::dvec2)bille->obtenirPositionRelative(), rayonBille);
	return details;
}