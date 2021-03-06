///////////////////////////////////////////////////////////////////////////
/// @file NoeudTable.cpp
/// @author The Ballers
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////
#include "../../Eclairage/ControleurNuanceurs.h"
#include "NoeudTable.h"
#include "Utilitaire.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_Storage/ModeleStorage_Liste.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudTable::NoeudTable(const std::string& typeNoeud)
///
/// @param[in] typeNoeud :  le type du noeud a creer.
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par defaut aux variables membres.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudTable::NoeudTable(const std::string& typeNoeud)
	: NoeudComposite{ typeNoeud }
{
	assignerSelection(false);
	selectionnable_ = false;
	modifiable_ = false;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudTable::~NoeudTable()
///
/// Ce destructeur desallouee la liste d'affichage du noeud.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudTable::~NoeudTable()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTable::afficherConcret() const
///
/// Cette fonction effectue le veritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudTable::afficherConcret() const
{
	NoeudComposite::afficherConcret();
	// Sauvegarde de la matrice.
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glTranslatef(TRANSLATE_X_NOEUD_TABLE, TRANSLATE_Y_NOEUD_TABLE, 0);
	NoeudAbstrait::appliquerAfficher();
	glStencilFunc(GL_ALWAYS, 0, (GLuint)-1);
	ControleurNuanceurs::obtenirInstance()->assignerEstTable(1);
	liste_->dessiner();
	ControleurNuanceurs::obtenirInstance()->assignerEstTable(0);
	glPopAttrib();
	glPopMatrix();
	// Restauration de la matrice.
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTable::animer(float temps)
///
/// @brief Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps.
///
/// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudTable::animer(float temps)
{
	glm::dvec3 positionRelative = positionRelative_;
	NoeudComposite::animer(temps);
	positionRelative_ = positionRelative;
	if (!animer_)
		return;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudTable::accepterVisiteur(VisiteurAbstrait* vis)
///
/// @brief Cette fonction appelle la methode traiter du visiteur.
///
/// @param[in] vis Pointeur sur le visiteur a accepter
///
/// @return reussi (TRUE)
///
////////////////////////////////////////////////////////////////////////
bool NoeudTable::accepterVisiteur(VisiteurAbstrait* vis)
{
	bool reussi = false;

	if (vis->traiter(this))
		reussi = true;

	return reussi;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn aidecollision::DetailsCollision NoeudTable::detecterCollisions(NoeudAbstrait* bille)
///
/// @brief Reimplementation de detecterCollisions pour la des limites de la table.
/// 
/// @param[in] bille Objet avec le noeud se compare pour trouver une collision.
///
/// @return details contient l'information sur la collision de la bille avec *this.
/// 
////////////////////////////////////////////////////////////////////////
aidecollision::DetailsCollision NoeudTable::detecterCollisions(NoeudAbstrait* bille)
{
	aidecollision::DetailsCollision detailsAucune;
	detailsAucune.type = aidecollision::COLLISION_AUCUNE;

	std::vector<glm::dvec3> boite;
	boite.push_back({ interieurGaucheTableX, interieurGaucheTableY, 0 });
	boite.push_back({ interieurDroitTableX, interieurGaucheTableY, 0 });
	boite.push_back({ interieurDroitTableX, interieurDroitTableY, 0 });
	boite.push_back({ interieurGaucheTableX, interieurDroitTableY, 0 });
	// Considerer tous les segments boite[i] --- boite[i+1 % size] 
	aidecollision::DetailsCollision details;
	double rayonBille = bille->obtenirVecteursEnglobants()[0].x;
	for (unsigned int i = 0; i < boite.size(); i++)
	{
		// Considerer tous les segments boite[i] --- boite[i+1 % size] 
		for (unsigned int i = 0; i < boite.size(); i++)
		{
			// On veut calculer la collision en 2D et caster les parametres en glm::dvec2 "oublie" leur composante en Z et choisi la bonne surcharge de calculerCollisionSegment.
			details = aidecollision::calculerCollisionSegment((glm::dvec2)boite[i], (glm::dvec2)boite[(i + 1) % boite.size()], (glm::dvec2)bille->obtenirPositionRelative(), rayonBille, true);
			if (details.type != aidecollision::COLLISION_AUCUNE)
			{
				return details;
			}
		}
	}

	// Si la bille sort de la table, la teleporter sur un trou pour qu'elle soit enlevee 
	// en bonne et due forme.
	// if (!FacadeModele::obtenirInstance()->estDansTable(bille->obtenirPositionRelative()) || bille->obtenirPositionRelative().z > 30 || bille->obtenirPositionRelative().z < -30)
	if (!FacadeModele::obtenirInstance()->estDansTable(bille->obtenirPositionRelative()))
	{
		for (NoeudAbstrait* noeud : enfants_)
		{
			if (noeud->obtenirType() == "trou")
			{
				bille->assignerPositionRelative(noeud->obtenirPositionRelative());
				break;
			}
			bille->assignerPositionRelative(glm::dvec3{ 160, 0, 0 });
		}
	}



	return detailsAucune;
}

void NoeudTable::traiterCollisions(aidecollision::DetailsCollision details, NoeudAbstrait* bille, float)
{
	NoeudAbstrait::traiterCollisions(details,bille);
	if (glm::length(bille->obtenirVitesse()) > 10)
		SoundControl->jouerSon("table");
}
