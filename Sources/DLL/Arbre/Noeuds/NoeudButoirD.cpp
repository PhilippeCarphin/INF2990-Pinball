///////////////////////////////////////////////////////////////////////////
/// @file NoeudButoirD.cpp
/// @author The Ballers
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////

#include "../../Eclairage/ControleurNuanceurs.h"
#include "NoeudButoirD.h"
#include "Utilitaire.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>
#include "../../Global/SingletonGlobal.h"

#include "Modele3D.h"
#include "OpenGL_Storage/ModeleStorage_Liste.h"

std::vector<glm::dvec3> NoeudButoirD::boiteEnglobanteModele_{
	{ 15.65, 45.30, 0.0 },
	{ -27.36, -21.86, 0.0 },
	{ -24.81, -26.14, 0.0 },
	{ 15.14, -24.41, 0.0 },
	{ 18.71, -21.35, 0.0 },
	{ 20.65, 44.18, 0.0 }
};


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudButoirD::NoeudButoirD(const std::string& typeNoeud)
///
/// @param[in] typeNoeud :  le type du noeud a creer.
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par defaut aux variables membres.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudButoirD::NoeudButoirD(const std::string& typeNoeud)
	: NoeudComposite{ typeNoeud }
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudButoirD::~NoeudButoirD()
///
/// Ce destructeur desallouee la liste d'affichage du noeud.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudButoirD::~NoeudButoirD()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudButoirD::afficherConcret() const
///
/// Cette fonction effectue le veritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudButoirD::afficherConcret() const
{
	NoeudComposite::afficherConcret();
	// Sauvegarde de la matrice.
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	NoeudAbstrait::appliquerAfficher();
	if (illumine_)
	{
		ControleurNuanceurs::obtenirInstance()->assignerEtatNoeud(NOEUD_ILLUMINE);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	}
	liste_->dessiner();
	glPopAttrib();
	glPopMatrix();
	// Restauration de la matrice.
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudButoirD::animer(float temps)
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps. Pas d'animation pour ce type de noeud.
///
/// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudButoirD::animer(float temps)
{
	NoeudComposite::animer(temps);
	illumine_ = false;
	if (!animer_)
		return;

	if (compteurIllumination_ < TEMPS_ILLUMINATION_NOEUD_BUTOIR)
	{
		compteurIllumination_ += temps;
		illumine_ = true;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudButoirD::accepterVisiteur(VisiteurAbstrait* vis)
///
/// @brief Cette fonction appelle la methode traiter du visiteur.
///
/// @param[in] vis Pointeur sur le visiteur a accepter
///
/// @return reussi (TRUE)
///
////////////////////////////////////////////////////////////////////////
bool NoeudButoirD::accepterVisiteur(VisiteurAbstrait* vis)
{
	bool reussi = false;

	if (vis->traiter(this))
		reussi = true;

	return reussi;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudButoirD::obtenirVecteursBoite(glm::dvec3 &v1, glm::dvec3 &v2, glm::dvec3 &v3, glm::dvec3 &v4)
///
/// @brief Faire une boite speciale pour le NoeudButoirD.
///
/// @param[out] v1 : Vecteur 1.
/// @param[out] v2 : Vecteur 2.
/// @param[out] v3 : Vecteur 3.
/// @param[out] v4 : Vecteur 4.
///
/// @return reussi (TRUE)
///
////////////////////////////////////////////////////////////////////////
void NoeudButoirD::obtenirVecteursBoite(glm::dvec3 &v1, glm::dvec3 &v2, glm::dvec3 &v3, glm::dvec3 &v4)
{
	NoeudAbstrait::obtenirVecteursBoite(v1, v2, v3, v4);
	v2 = v3;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn aidecollision::DetailsCollision NoeudAbstrait::detecterCollisions(NoeudAbstrait* bille)
///
/// @brief Cette fonction retourne un objet detail collision pour la 
/// collision de la bille sur l'objet courant.
///
/// @param[in] bille Objet avec le noeud se compare pour trouver une collision.
///
/// @return details contient l'information sur la collision de la bille avec *this.
///
////////////////////////////////////////////////////////////////////////
aidecollision::DetailsCollision NoeudButoirD::detecterCollisions(NoeudAbstrait* bille)
{
	std::vector<glm::dvec3> boite = obtenirVecteursEnglobants();
	double rayonBille = bille->obtenirVecteursEnglobants()[0].x;
	aidecollision::DetailsCollision details;

	for (unsigned int i = 0; i < boite.size(); i++)
		boite[i] += obtenirPositionRelative();
	// Considerer tous les segments boite[i] --- boite[i+1 % size] 
	aidecollision::DetailsCollision detailsRetour;
	detailsRetour.type = aidecollision::COLLISION_AUCUNE;
	for (unsigned int i = 0; i < boite.size(); i++)
	{
		// On veut calculer la collision en 2D et caster les parametres en glm::dvec2 "oublie" leur composante en Z et choisi la bonne surcharge de calculerCollisionSegment.
		details = aidecollision::calculerCollisionSegment((glm::dvec2)boite[i], (glm::dvec2)boite[(i + 1) % boite.size()], (glm::dvec2)bille->obtenirPositionRelative(), rayonBille, true);
		if (details.type != aidecollision::COLLISION_AUCUNE)
		{
			// Donner priorite aux collision sur les segments plutot que sur les points.
			if (details.type == aidecollision::COLLISION_SEGMENT)
			{
				if (i == 0) // collision sur le long segment.
				{
					details.longSegmentButoir = true;
				}
				return details;
			}
			else
				detailsRetour = details;
		}
	}
	return details;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudButoirD::traiterCollisions(aidecollision::DetailsCollision details, NoeudAbstrait* bille, float facteurRebond)
///
/// @brief Cette fonction effectue la reaction a la collision de la bille sur 
/// l'objet courant. La collision est plus forte sur le long segment si le mode force supplementaire est actif.
///
/// @param[in] details Objet contenant les details de la collision a traiter
/// @param bille Objet modifie par la collision
/// @param[in] facteurRebond Facteur par lequel la vitesse normale de la bille sera multipliee
///
/// @return details contient l'information sur la collision de la bille avec *this.
///
////////////////////////////////////////////////////////////////////////
void NoeudButoirD::traiterCollisions(aidecollision::DetailsCollision details, NoeudAbstrait* bille, float facteurRebond)
{
	if (details.longSegmentButoir)
	{
		SingletonGlobal::obtenirInstance()->collisionButoirTriangulaire();
		compteurIllumination_ = 0;
		if (FacadeModele::obtenirInstance()->obtenirModeForceRebond())
			facteurRebond = FACTEUR_REBOND_BUTOIRE;
	}
	NoeudAbstrait::traiterCollisions(details, bille, facteurRebond);
	SoundControl->jouerSon("butoir");
}

////////////////////////////////////////////////////////////////////////
///
/// @fn std::vector<glm::dvec3> NoeudButoirD::obtenirVecteursEnglobants()
///
/// @brief Retourne la boite englobante de l'objet sous forme d'un vector de vecteurs
///
/// @remark Pour avoir les points de la boite englobante, il faut additionner la position de l'objet.
///
/// @return boiteEnglobanteObjet Vecteur contenant les vecteurs de la boite de l'objet
///
////////////////////////////////////////////////////////////////////////
std::vector<glm::dvec3> NoeudButoirD::obtenirVecteursEnglobants()
{
	std::vector<glm::dvec3> boiteEnglobanteObjet;

	glm::dmat3 echelle = glm::dmat3{ glm::dvec3{ scale_.x, 0, 0.0 },
		glm::dvec3{ 0, scale_.y, 0.0f },
		glm::dvec3{ 0.0, 0.0, scale_.z } };

	double angleEnRadian = -rotation_[2] * utilitaire::PI_180;
	glm::dmat3 transform = glm::dmat3{ glm::dvec3{ cos(angleEnRadian), -sin(angleEnRadian), 0.0 },
		glm::dvec3{ sin(angleEnRadian), cos(angleEnRadian), 0.0f },
		glm::dvec3{ 0.0, 0.0, 1.0 } };

	for (glm::dvec3 vecteur : boiteEnglobanteModele_)
	{
		boiteEnglobanteObjet.push_back(transform * (echelle * vecteur));
	}

	return boiteEnglobanteObjet;
}