#ifndef __ARBRES_NOEUDS_NOEUDBILLE_H__
#define __ARBRES_NOEUDS_NOEUDBILLE_H__

#include "NoeudComposite.h"
#include "Gl/gl.h"

class NoeudBille : public NoeudComposite
{
public:
	// Constructeur
	NoeudBille(const std::string& typeNoeud);
	// Destructeur 
	~NoeudBille();

	// Surchage de la m�thode qui affiche l'objet
	virtual void afficherConcret() const;
	// Surchage de la m�thode qui anime l'objet
	virtual void animer(float temps);

	virtual bool accepterVisiteur(VisiteurAbstrait* vis);

private:
	// TODO(Emilio): Ins�rer les attributs propres � chaque type d'objet

};

#endif // __ARBRE_NOEUDS_NOEUDGENERATEURBILLE_H__