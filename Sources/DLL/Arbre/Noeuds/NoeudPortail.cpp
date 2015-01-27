#include "NoeudPortail.h"
#include "Utilitaire.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_Storage/ModeleStorage_Liste.h"



NoeudPortail::NoeudPortail(const std::string& typeNoeud)
	: NoeudComposite{ typeNoeud }
{
}

NoeudPortail::~NoeudPortail()
{
}

void NoeudPortail::afficherConcret() const
{
}

void NoeudPortail::animer(float temps)
{
}

bool NoeudPortail::accepterVisiteur(VisiteurAbstrait* vis)
{
	bool reussi = false;

	if (vis->traiter(*this))
		reussi = true;

	return reussi;

}

