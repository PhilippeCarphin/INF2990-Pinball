///////////////////////////////////////////////////////////////////////////////
/// @file NoeudAraignee.cpp
/// @author Julien Gascon-Samson
/// @date 2011-05-19
/// @version 1.0
///
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////////
#include "NoeudAraignee.h"
#include "Utilitaire.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_Storage/ModeleStorage_Liste.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAraignee::NoeudAraignee(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par d�faut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudAraignee::NoeudAraignee(const std::string& typeNoeud)
: NoeudComposite{ typeNoeud }
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAraignee::~NoeudAraignee()
///
/// Ce destructeur d�sallouee la liste d'affichage de l'araign�e.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudAraignee::~NoeudAraignee()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAraignee::afficherConcret() const
///
/// Cette fonction effectue le v�ritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAraignee::afficherConcret() const
{
	// Appel � la version de la classe de base pour l'affichage des enfants.
	NoeudComposite::afficherConcret();

	// Sauvegarde de la matrice.
	glPushMatrix();
	// R�volution autour du centre.
	glRotatef(35, sqrtf(2), sqrtf(2), 0);
	/*
	// Ligne pour tester le redimensionnement :
	glScalef(8, 8, 1);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(100, 100, 100);
	glVertex3f(200, 200, 200);
	glVertex3f(300, 300, 300);
	glVertex3f(400, 400, 400);
	glEnd();
	*/
	// Affichage du mod�le.
	liste_->dessiner();
	// Restauration de la matrice.
	glPopMatrix();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAraignee::animer(float temps)
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps.
///
/// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAraignee::animer(float temps)
{
	// Appel � la version de la classe de base pour l'animation des enfants.
	// Seulement si utile (si on as des enfants)
	for (NoeudAbstrait * enfant : enfants_) {
		enfant->animer(temps);
	}
	/* Animation ici */

	// L'araign�e oscille selon une p�riode de 4 secondes.
	angle_ = fmod(angle_ + temps / 4.0f * 360.0f, 360.0f);
	positionRelative_[0] = 5 * cos(utilitaire::DEG_TO_RAD(angle_));
	positionRelative_[1] = 40 * sin(utilitaire::DEG_TO_RAD(angle_));
}

bool NoeudAraignee::accepterVisiteur(VisiteurAbstrait* vis)
{
	bool reussi = false;

	if (vis->traiter(this))
		reussi = true;

	return reussi;
}