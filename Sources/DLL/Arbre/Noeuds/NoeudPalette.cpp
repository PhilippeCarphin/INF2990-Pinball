#include "NoeudPalette.h"
#include "Utilitaire.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_Storage/ModeleStorage_Liste.h"



NoeudPalette::NoeudPalette(const std::string& typeNoeud)
	: NoeudComposite{ typeNoeud }
{
}

NoeudPalette::~NoeudPalette()
{
}

void NoeudPalette::afficherConcret() const
{
	NoeudComposite::afficherConcret();
	// Sauvegarde de la matrice.
	glPushMatrix();
	// Affichage du mod�le.
	liste_->dessiner();
	// Restauration de la matrice.
	glPopMatrix();
}

void NoeudPalette::animer(float temps)
{
}

bool NoeudPalette::accepterVisiteur(VisiteurAbstrait* vis)
{
	bool reussi = false;

	if (vis->traiter(*this))
		reussi = true;

	return reussi;
}