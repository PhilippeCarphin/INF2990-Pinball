///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurDuplication.h
/// @author The Ballers
/// @date 2015-02-01
/// @version 1.0
///
/// @ingroup Visiteur
///////////////////////////////////////////////////////////////////////////////
#ifndef __VISITEURS_VISITEURDUPLICATION_H__
#define __VISITEURS_VISITEURDUPLICATION_H__

#include "NoeudAbstrait.h"
#include "VisiteurAbstrait.h"
#include <vector>

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurDuplication
/// @brief Classe pour dupliquer les objets selectionn�s de l'arbre de rendu
///
///        Instancier cette classe. Ensuite, appeler la m�thode accepterVisiteur() 
///		   de l'arbre de rendu et lui fournir CE visiteur en param�tre
///
/// @author The Ballers
/// @date 2015-02-02
/// @ingroup Visiteur
///////////////////////////////////////////////////////////////////////////
class VisiteurDuplication : public VisiteurAbstrait
{
public:

	/// Constructeur par d�faut
	VisiteurDuplication();	

	/// Destructeur
	~VisiteurDuplication();

	/// Traiter une op�ration sur l'arbre de rendu et ses enfants
	virtual bool traiter(ArbreRenduINF2990* arbre);
	virtual bool traiter(NoeudAbstrait* noeud);
	virtual bool traiter(NoeudTable* table);

private:

	std::vector<NoeudAbstrait*> copies_;	///< Contient les copies des objets selectionn�s
	ArbreRenduINF2990* arbreTemp;			///< Pointeur vers l'arbre de rendu original
};

#endif //__VISITEURS_VISITEURDUPLICATION_H__