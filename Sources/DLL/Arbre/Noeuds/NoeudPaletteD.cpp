///////////////////////////////////////////////////////////////////////////
/// @file NoeudPaletteD.cpp
/// @author Yonni Chen
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////

#include "NoeudPaletteD.h"
#include "Utilitaire.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_Storage/ModeleStorage_Liste.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudPaletteD::NoeudPaletteD(const std::string& typeNoeud)
///
/// @param[in] typeNoeud :  le type du noeud � cr�er.
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par d�faut aux variables membres.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudPaletteD::NoeudPaletteD(const std::string& typeNoeud)
	: NoeudComposite{ typeNoeud }
{
	ajustable_ = false;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudPaletteD::~NoeudPaletteD()
///
/// Ce destructeur d�sallouee la liste d'affichage du noeud.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudPaletteD::~NoeudPaletteD()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudPaletteD::afficherConcret() const
///
/// Cette fonction effectue le v�ritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudPaletteD::afficherConcret() const
{
	NoeudComposite::afficherConcret();
	// Sauvegarde de la matrice.
	glPushMatrix();
	// Affichage du mod�le.
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	if (colorShift_){
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
	}
	if (selectionne_ && transparent_){
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
	}
	else if (selectionne_)
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD);
	liste_->dessiner();
	glPopAttrib();
	// Restauration de la matrice.
	glPopMatrix();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudPaletteD::animer(float temps)
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps. Pas d'animation pour ce type de noeud.
///
/// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudPaletteD::animer(float temps)
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudPaletteD::accepterVisiteur(VisiteurAbstrait* vis)
///
/// Cette fonction appelle la m�thode traiter du visiteur.
///
/// @return reussi (TRUE)
///
////////////////////////////////////////////////////////////////////////
bool NoeudPaletteD::accepterVisiteur(VisiteurAbstrait* vis)
{
	bool reussi = false;

	if (vis->traiter(this))
		reussi = true;

	return reussi;
}