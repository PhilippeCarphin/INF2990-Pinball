#ifndef __ARBRE_USINES_USINENOEUDBUTOIR_H__
#define __ARBRE_USINES_USINENOEUDBUTOIR_H__

#include "UsineNoeud.h"
class UsineNoeudButoir : public UsineNoeud
{
public:
	// Contrusteur par param�tre
	inline UsineNoeudButoir(const std::string& nom);
	
	/// Fonction � surcharger pour la cr�ation d'un noeud.
	inline virtual NoeudAbstrait* creerNoeud() const;
	
	
	
	~UsineNoeudButoir();
};

#endif // __ARBRE_USINES_USINENOEUDBUTOIR_H__