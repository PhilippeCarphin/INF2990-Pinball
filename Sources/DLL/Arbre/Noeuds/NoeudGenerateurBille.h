#ifndef __ARBRES_NOEUDS_NOEUDGENERATEURBILLE_H__
#define __ARBRES_NOEUDS_NOEUDGENERATEURBILLE_H__

#include "NoeudComposite.h"
#include "Gl/gl.h"

class NoeudGenerateurBille : public NoeudComposite
{
public:
	// Constructeur
	NoeudGenerateurBille(const std::string& typeNoeud);
	// Destructeur 
	~NoeudGenerateurBille();

	// Surchage de la m�thode qui affiche l'objet
	virtual void afficherConcret() const;
	// Surchage de la m�thode qui anime l'objet
	virtual void animer(float temps);

private:
	// TODO(Emilio): Ins�rer les attributs propres � chaque type d'objet

};

#endif // __ARBRE_NOEUDS_NOEUDGENERATEURBILLE_H__