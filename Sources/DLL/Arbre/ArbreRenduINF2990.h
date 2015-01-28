///////////////////////////////////////////////////////////////////////////
/// @file ArbreRenduINF2990.h
/// @author Martin Bisson
/// @date 2007-03-23
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_ARBRERENDUINF2990_H__
#define __ARBRE_ARBRERENDUINF2990_H__


#include "ArbreRendu.h"

#include <map>
#include <string>


///////////////////////////////////////////////////////////////////////////
/// @class ArbreRenduINF2990
/// @brief Classe qui repr�sente l'arbre de rendu sp�cifique au projet de
///        INF2990.
///
///        Cette classe s'occupe de configurer les usines des noeuds qui
///        seront utilis�s par le projet.
///
/// @author Martin Bisson
/// @date 2007-03-23
///////////////////////////////////////////////////////////////////////////
class ArbreRenduINF2990 : public ArbreRendu
{
public:
   /// Constructeur par d�faut.
   ArbreRenduINF2990();
   /// Destructeur.
   virtual ~ArbreRenduINF2990();

   /// Initialise l'arbre de rendu � son �tat initial.
   void initialiser();


	/// La cha�ne repr�sentant led typrs
   static const std::string NOM_ARAIGNEE;
   static const std::string NOM_BUTOIR;
   static const std::string NOM_CIBLE;
   static const std::string NOM_CONECUBE;
   static const std::string NOM_GENERATEURBILLE;
   static const std::string NOM_MUR;
   static const std::string NOM_PALETTE;
   static const std::string NOM_PORTAIL;
   static const std::string NOM_RESSORT;
   static const std::string NOM_TROU;	
   static const std::string NOM_VIDE;
};


#endif // __ARBRE_ARBRERENDUINF2990_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
